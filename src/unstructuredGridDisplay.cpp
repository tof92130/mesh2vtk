#include "vtkUnstructuredGrid.h"

#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkCommand.h"
#include "vtkBoxWidget.h"
#include "vtkTransform.h"

#include "vtkCamera.h"

#include "vtkInteractorStyleTrackballCamera.h"

#include "unstructuredGridDisplay.h"

//
// Similar to Cone2.cxx, we define a callback for interaction.
// 
class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New() 
    { return new vtkMyCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkTransform *t = vtkTransform::New();
      vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
      widget->GetTransform(t);
      widget->GetProp3D()->SetUserTransform(t);
      t->Delete();
    }
};


void displayUnstructuredGrid(vtkUnstructuredGrid *mesh ) {

  cout << "--- displayUnstructuredGrid ---" << endl;

  vtkDataSetMapper *dataMapper;
  dataMapper=vtkDataSetMapper::New();
  dataMapper->SetInputData(mesh);
  dataMapper->SetScalarRange(0,5);

  // 
  // Create an actor to represent the cone. The actor orchestrates rendering
  // of the mapper's graphics primitives. An actor also refers to properties
  // via a vtkProperty instance, and includes an internal transformation
  // matrix. We set this actor's mapper to be coneMapper which we created
  // above.
  //
  vtkActor * dataActor;
  dataActor=vtkActor::New();
  dataActor->SetMapper( dataMapper );

/*
  // The usual rendering stuff.
  vtkCamera *camera;
  camera=vtkCamera::New();
  camera->SetPosition(1,1,1);
  camera->SetFocalPoint(0,0,0);
*/

  //
  // Create the Renderer and assign actors to it. A renderer is like a
  // viewport. It is part or all of a window on the screen and it is
  // responsible for drawing the actors it has.  We also set the background
  // color here.
  //
  vtkRenderer *ren1;
  ren1=vtkRenderer::New();
  ren1->AddActor(dataActor);
//ren1->SetActiveCamera(camera);
//ren1->ResetCamera();
  ren1->SetBackground(0.1,0.2,0.4);

  //
  // Finally we create the render window which will show up on the screen.
  // We put our renderer into the render window using AddRenderer. We also
  // set the size to be 300 pixels by 300.
  //
  vtkRenderWindow *renWin;
  renWin=vtkRenderWindow::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(600,600);
  
  cout << "vtkRenderWindowInteractor"          << endl;
  cout << "-------------------------"          << endl << endl;
  cout << "Mouse bindings:"                    << endl;
  cout << "  camera: Button 1 - rotate"        << endl;
  cout << "  Button 2 - pan"                   << endl;
  cout << "  Button 3 - zoom"                  << endl;
  cout << "  Button 3 - zoom"                  << endl;
  cout << "  ctrl-Button 1 - spin"             << endl;
  cout << "  actor:  Button 1 - rotate"        << endl;
  cout << "          Button 2 - pan"           << endl;
  cout << "          Button 3 - uniform scale" << endl;
  cout << "     ctrl-Button 1 - spin"          << endl;
  cout << "     ctrl-Button 2 - dolly."        << endl;

  cout << "Keyboard bindings (upper or lower case):"              << endl;
  cout << "  j - joystick like mouse interactions"                << endl;
  cout << "  t - trackball like mouse interactions"               << endl;
  cout << "  o - object/ actor interaction"                       << endl;
  cout << "  c - camera interaction"                              << endl;
  cout << "  r - reset camera view"                               << endl;
  cout << "  w - turn all actors wireframe"                       << endl;
  cout << "  s - turn all actors surface"                         << endl;
  cout << "  u - execute user defined function"                   << endl;
  cout << "  p - pick actor under mouse pointer (if pickable)"    << endl;
  cout << "  3 - toggle in/out of 3D mode (if supported by ren1)" << endl;
  cout << "  e - exit"                                            << endl;
  cout << "  q - exit"                                            << endl;

  // 
  // The vtkRenderWindowInteractor class watches for events (e.g., keypress,
  // mouse) in the vtkRenderWindow. These events are translated into
  // event invocations that VTK understands (see VTK/Common/vtkCommand.h
  // for all events that VTK processes). Then observers of these VTK
  // events can process them as appropriate.
  //
  vtkRenderWindowInteractor * iren;
  iren=vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  //
  // By default the vtkRenderWindowInteractor instantiates an instance
  // of vtkInteractorStyle. vtkInteractorStyle translates a set of events
  // it observes into operations on the camera, actors, and/or properties
  // in the vtkRenderWindow associated with the vtkRenderWinodwInteractor. 
  // Here we specify a particular interactor style.
  //
  vtkInteractorStyleTrackballCamera *style; 
  style=vtkInteractorStyleTrackballCamera::New();
  iren->SetInteractorStyle(style);


  //
  // Here we use a vtkBoxWidget to transform the underlying coneActor (by
  // manipulating its transformation matrix). Many other types of widgets
  // are available for use, see the documentation for more details.
  //
  // The SetInteractor method is how 3D widgets are associated with the render
  // window interactor. Internally, SetInteractor sets up a bunch of callbacks
  // using the Command/Observer mechanism (AddObserver()). The place factor 
  // controls the initial size of the widget with respect to the bounding box
  // of the input to the widget.
  //
  vtkBoxWidget *boxWidget = vtkBoxWidget::New();
  boxWidget->SetInteractor(iren);
  boxWidget->SetPlaceFactor(1.25);

  //
  // Place the interactor initially. The input to a 3D widget is used to 
  // initially position and scale the widget. The EndInteractionEvent is
  // observed which invokes the SelectPolygons callback.
  //
  boxWidget->SetProp3D(dataActor);
  boxWidget->PlaceWidget();
  vtkMyCallback *callback = vtkMyCallback::New();
  boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

  //
  // Normally the user presses the "i" key to bring a 3D widget to life. Here
  // we will manually enable it so it appears with the cone. 
  //
  boxWidget->On();

  //
  // Start the event loop.
  //

//renWin->Render();
  iren->Initialize();
  iren->Start();

  dataMapper->Delete();
  dataActor->Delete();
//camera->Delete();
  ren1->Delete();
  renWin->Delete();
  iren->Delete();

  cout << "--- displayUnstructuredGrid ---" << endl << endl;

}
