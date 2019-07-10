#include <iostream>
#include <string>

#include <math.h>

#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkWindowToImageFilter.h>
#include <vtkJPEGWriter.h>
#include <vtkTIFFWriter.h>
#include <vtkPNGWriter.h>
#include <vtkLookupTable.h>
#include <vtkScalarBarActor.h>
#include <vtkProperty2D.h>
#include <vtkTextProperty.h>
#include <vtkAxes.h>
#include <vtkTubeFilter.h>

#include <vtkContourFilter.h>
#include <vtkLODActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkDoubleArray.h>

//#include <vtkPolyDataNormals.h>
//#include <vtkStripper.h>

#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkPlane.h"
#include "vtkSphere.h"
#include "vtkCutter.h"
#include "vtkVolumeMapper.h"

#include "vtkCamera.h"

#include "unstructuredJPEGWriter.h"


using namespace std;


void writePngUnstructured(vtkUnstructuredGrid * mesh, string fileOut) {

	cout << "------------------------------------------------------------------------" << endl;

	int i=fileOut.length()-1;
	bool test=0;
	while (i>0 && test==0) {
		//cout << "i=" << i << "-" << fileOut.at(i)  << endl;
		if( fileOut.at(i)=='.' ) {
			test=1;
		}
		i--;
	}
  
	string name;
	name.append(fileOut,0,i+2);
	name+="png";

	cout << "Saving vtkUnstructuredGrid: "<< name << endl;

  
	double *extrema=mesh->GetScalarRange();

	float x;
	x=extrema[0];
	if( fabs(extrema[0])<fabs(extrema[1]) ){
		x=fabs(extrema[1]);
	}
	else {
		x=fabs(extrema[0]);
	}


	x=floor(5e-1*x);
	if( x==0. )x=1.;
  
	extrema[0]=-x;
	extrema[1]= x;

	extrema[0]=-1;
	extrema[1]= 1;



	cout << "\tSolu Scalar Range"    << endl;
	cout << "\t\tMin=" << extrema[0] << endl;
	cout << "\t\tMax=" << extrema[1] << endl;

	double x0=extrema[0];
	double x1=extrema[1];

/*
  double x0=5e-1*fabs(extrema[0]);
  double x1=5e-1*fabs(extrema[1]);

  if( x0<x1 ) {
    extrema[0]=-x0;
    extrema[1]= x0;
  }
  else {
    extrema[0]=-x1;
    extrema[1]= x1;
  }

  cout << "\tVisu Scalar Range" << endl;
  cout << "\t\tMin=" << extrema[0] << endl;
  cout << "\t\tMax=" << extrema[1] << endl;

*/


	// Palettes

	//rainbow
	vtkLookupTable *lutRB=vtkLookupTable::New();
	lutRB->SetNumberOfTableValues(1024);
	lutRB->SetHueRange(0.667, 0); 
	lutRB->SetSaturationRange(1,1);
    lutRB->SetValueRange (0, 1);
  //lutRB->SetRange(extrema);
    lutRB->Build();

	// blac and white
	vtkLookupTable *lutBW=vtkLookupTable::New();
	lutBW->SetNumberOfTableValues(1024);
	lutBW->SetTableRange (0, 2000);
	lutBW->SetSaturationRange (0, 0);
	lutBW->SetHueRange (0, 0);
	lutBW->SetValueRange (0, 1);
	//lutBW->SetAlphaRange(0.1,0.9); // Transparance
	lutBW->Build();


	// *** Field ***

	cout << "\tBuilding Field" << endl;

	vtkDataSetMapper *meshMapper=vtkDataSetMapper::New();
	meshMapper->SetLookupTable(lutRB);
	meshMapper->SetScalarRange(extrema);
  
#if VTK_MAJOR_VERSION <= 5
  meshMapper->SetInput(mesh);
#else
  meshMapper->SetInputData(mesh);
#endif

	vtkActor * meshActor;
	meshActor=vtkActor::New();
	meshActor->SetMapper(meshMapper);
	//meshActor->GetProperty()->SetRepresentationToWireframe();
	//meshActor->RotateX(90);
	//meshActor->RotateY(90);
	//meshActor->RotateZ(90);
	//meshActor->RotateX(45); meshActor->RotateY(45); meshActor->RotateZ(45);


/*
  vtkProperty*prop = meshActor->GetProperty(); 
    prop->SetDiffuseColor(0,0,1.0); 
    prop->SetSpecularColor(0.0,1.0,0.0); 
    prop->SetSpecular(1); 
    prop->SetSpecularPower(10); 
    prop->SetAmbientColor(1,0,0); 
    prop->SetAmbient(0.3);
*/


  // Volume Mapper

/*
  vtkPlane *plane0=vtkPlane::New(); 
    plane->SetOrigin( 0.5, 0.25, 0.25 ); 
    plane->SetNormal( -1.0, 0.0, 0.0 ); 

  vtkVolumeMapper *volumeMapper=vtkVolumeMapper::New();
    volumeMapper->AddClippingPlane(plane0); 

  plane0->Delete();
*/

	// Cut

	vtkSphere * sphere=vtkSphere::New(); 
	sphere->SetCenter(0.5, 0.25, 0.25);
	sphere->SetRadius(1.0); 

	// *** cut X ***

	cout << "\tBuilding cut xx'" << endl;
 
	vtkPlane *planeX=vtkPlane::New(); 
	planeX->SetOrigin(0.01, 0.00, 0.00); 
	planeX->SetNormal(1.00, 0.00, 0.00); 

	vtkCutter *cutX = vtkCutter::New(); 
  
#if VTK_MAJOR_VERSION <= 5
  cutX->SetInput(mesh);
#else
  cutX->SetInputData(mesh);
#endif
  
	cutX->SetCutFunction( planeX );

	vtkPolyDataMapper *cutXMapper = vtkPolyDataMapper::New();
	cutXMapper->SetInputConnection(cutX->GetOutputPort());
	cutXMapper->ScalarVisibilityOn();
	cutXMapper->SetScalarRange(extrema[0],extrema[1]);

	vtkActor *cutXActor = vtkLODActor::New();
	cutXActor->SetMapper(cutXMapper);
	cutXActor->RotateX(45);

	// *** cut Y ***

	cout << "\tBuilding cut yy'" << endl;

	vtkPlane *planeY=vtkPlane::New(); 
	planeY->SetOrigin(0.00, 0.00, 0.00); 
	planeY->SetNormal(0.00, 1.00, 0.00); 

	vtkCutter *cutY = vtkCutter::New();
  
#if VTK_MAJOR_VERSION <= 5
  cutY->SetInput(mesh);
#else
  cutY->SetInputData(mesh);
#endif
  
	cutY->SetCutFunction(planeY);  

	vtkPolyDataMapper *cutYMapper = vtkPolyDataMapper::New();
	cutYMapper->SetInputConnection(cutY->GetOutputPort());
	cutYMapper->ScalarVisibilityOn();
    cutYMapper->SetScalarRange(extrema[0],extrema[1]);

	vtkActor *cutYActor = vtkLODActor::New();
	cutYActor->SetMapper(cutYMapper);


	// *** cut Z ***

	cout << "\tBuilding vtkCutter -> cut zz'" << endl;

	vtkPlane *planeZ=vtkPlane::New(); 
	planeZ->SetOrigin(1.00, 0.00, 0.00); 
	planeZ->SetNormal(0.00, 0.00, 1.00);

	vtkCutter *cutZ = vtkCutter::New(); 
  
#if VTK_MAJOR_VERSION <= 5
  cutZ->SetInput(mesh);
#else
  cutZ->SetInputData(mesh);
#endif
  
	cutZ->SetCutFunction( planeZ );  

	vtkPolyDataMapper *cutZMapper = vtkPolyDataMapper::New();
	cutZMapper->SetInputConnection(cutZ->GetOutputPort());
	cutZMapper->ScalarVisibilityOn();
	cutZMapper->SetScalarRange(extrema[0],extrema[1]);

	vtkActor *cutZActor = vtkLODActor::New();
	cutZActor->SetMapper(cutZMapper);


	// *** Isosurface ***

	cout << "\tBuilding vtkContourFilter" << endl;

	vtkContourFilter *iso=vtkContourFilter::New();
	iso->SetValue(extrema[0],extrema[1]);
	iso->SetInputData(mesh);
	iso->SetNumberOfContours(5);
	iso->UseScalarTreeOn();
	iso->SetValue(x0,x1);

	vtkPolyDataMapper *isoMapper = vtkPolyDataMapper::New();
	isoMapper->SetInputConnection(iso->GetOutputPort());
	//isoMapper->ScalarVisibilityOff();
	isoMapper->ScalarVisibilityOn();
	isoMapper->SetScalarRange(extrema[0],extrema[1]);
	//isoMapper->SetScalarModeToUsePointFieldData();
    
	vtkLODActor *isoActor = vtkLODActor::New();
	isoActor->SetMapper(isoMapper);
	isoActor->SetNumberOfCloudPoints(1000);


	// *** Scalar Bar ***

	cout << "\tBuilding vtkScalarBarActor" << endl;

	vtkTextProperty *propertyText = vtkTextProperty::New();
	propertyText->SetFontFamilyToCourier();
	propertyText->SetColor(1,1,1); // white
	//propertyText->SetColor(0,0,0); // black
	propertyText->SetFontSize(18);
	//propertyText->SetShadow(2);

	vtkScalarBarActor *scalarBarActor = vtkScalarBarActor::New();
	scalarBarActor->SetLookupTable(lutRB);
	//scalarBarActor->SetProperty(property);
	//scalarBarActor->SetTitle("p1 (dB)");
	scalarBarActor->SetTitle("Re[p1] (Pa)");

	scalarBarActor->SetTitleTextProperty(propertyText);
	scalarBarActor->SetLabelTextProperty(propertyText);
	scalarBarActor->SetLabelFormat("%.2e");
	//scalarBarActor->GetLabelTextProperty()->SetFontSize(18);
	//scalarBarActor->GetLabelTextProperty()->SetColor(0,0,0); // black
	//scalarBarActor->GetLabelTextProperty()->SetColor(1,1,1); // white
	scalarBarActor->GetLabelTextProperty()->BoldOn();
	scalarBarActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
	//scalarBarActor->GetPositionCoordinate()->SetValue(0.0,0.1);
	//scalarBarActor->SetOrientationToVertical();
	//scalarBarActor->SetHeight(0.8);
	//scalarBarActor->SetWidth (0.1);
	scalarBarActor->GetPositionCoordinate()->SetValue(0.1,0.85);
	scalarBarActor->SetOrientationToHorizontal();
	scalarBarActor->SetHeight(0.1);
	scalarBarActor->SetWidth (0.8);


	// *** Axes ***

	cout << "\tBuilding Axes" << endl;

	vtkAxes *axes = vtkAxes::New();
	axes->SetOrigin(0,0,0);
	//axes->SetOrigin(0.6,0,0);
	axes->SetScaleFactor(1);
	axes->SetSymmetric(0);

	vtkTubeFilter *axesTubes = vtkTubeFilter::New();
	axesTubes->SetInputData((vtkPolyData *) axes->GetOutput());
	axesTubes->SetDefaultNormal(0,0,1);
	axesTubes->SetNumberOfSides(10); //calidad de las lines
	axesTubes->SetRadius(0.0152421);
	axesTubes->SetRadiusFactor(10);
	axesTubes->SetGenerateTCoords(0);
	axesTubes->SetVaryRadius(0);
	axesTubes->SetCapping(0);
	axesTubes->SetSidesShareVertices(1);
	axesTubes->SetUseDefaultNormal(0);

	vtkPolyDataMapper *axesMapper = vtkPolyDataMapper::New();
	axesMapper->SetInputData(axesTubes->GetOutput());

	vtkActor *axesActor = vtkActor::New();
	axesActor->SetMapper(axesMapper);
	axesActor->SetOrigin(0,0,0);
	axesActor->SetPosition(0,0,0);
	axesActor->SetScale(1,1,1);
	axesActor->SetPickable(1);
	axesActor->SetVisibility(1);
	//axesActor->GetProperty()->SetColor(1,0,0);


	// Visu

	// Create the Renderer and assign actors to it. A renderer is like a
	// viewport. It is part or all of a window on the screen and it is
	// responsible for drawing the actors it has.  We also set the background
	// color here.
	//

	cout << "\tBuilding vtkRenderer" << endl;
	vtkRenderer *ren1=vtkRenderer::New();
	ren1->AddActor(axesActor);
	ren1->AddActor(meshActor);
	//ren1->SetBackground(1  ,1  ,1  );// white
	ren1->SetBackground(0.1,0.2,0.4);// blue
	ren1->AddActor(scalarBarActor);
	//ren1->AddActor(cutXActor);
	//ren1->AddActor(cutYActor);
	//ren1->AddActor(cutZActor);
	//ren1->AddActor(isoActor);
	ren1->ResetCamera();


	cout << "\tBuilding vtkCamera" << endl;
	vtkCamera* cam = ren1->GetActiveCamera();
	//cam->SetPosition(25, 10, 10);
	//cam->SetFocalPoint(0, 0, 0);
	//cam->SetViewAngle(30);
	//cam->SetViewUp(-1, 0, 0);

	//
	// Finally we create the render window which will show up on the screen.
	// We put our renderer into the render window using AddRenderer. We also
	// set the size to be 300 pixels by 300.
	//

	vtkRenderWindow *renWin=vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	renWin->SetSize(800,800);

	// 
	// The vtkRenderWindowInteractor class watches for events (e.g., keypress,
	// mouse) in the vtkRenderWindow. These events are translated into
	// event invocations that VTK understands (see VTK/Common/vtkCommand.h
	// for all events that VTK processes). Then observers of these VTK
	// events can process them as appropriate.
	//

	vtkRenderWindowInteractor * iren=vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	//
	// By default the vtkRenderWindowInteractor instantiates an instance
	// of vtkInteractorStyle. vtkInteractorStyle translates a set of events
	// it observes into operations on the camera, actors, and/or properties
	// in the vtkRenderWindow associated with the vtkRenderWinodwInteractor. 
	// Here we specify a particular interactor style.
	//
	vtkInteractorStyleTrackballCamera *style=vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);

	// The usual rendering stuff.


	//
	// Start the event loop.
	//

	renWin->Render();

	//iren->Initialize();
	//iren->Start();



	cout<<"\tSaving File"<<endl;

	vtkWindowToImageFilter * w2i=vtkWindowToImageFilter::New();
	w2i->SetInput(renWin);

	/*
	// writing jpeg output
	cout<<"Saving render into msh2vtk.jpeg"<<endl;
	vtkJPEGWriter * jpegWriter =vtkJPEGWriter::New();
	jpegWriter->SetInput(w2i->GetOutput());
	jpegWriter->SetFileName("mesh2vtk.jpeg");
	jpegWriter->Write();
	jpegWriter->Delete();
	*/

	// writing png output
	vtkPNGWriter *pngWriter =vtkPNGWriter::New();
	pngWriter->SetInputData(w2i->GetOutput());
	pngWriter->SetFileName( name.c_str() );
	pngWriter->Write();
	pngWriter->Delete();


	meshMapper->Delete();
	meshActor->Delete();

	iso->Delete();
	isoMapper->Delete();
	isoActor->Delete();

	scalarBarActor->Delete();

	ren1->Delete();
	renWin->Delete();
	iren->Delete();

	cout << "------------------------------------------------------------------------" << endl<< endl;


}
