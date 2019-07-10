
#include <iostream>
#include <strstream>
#include <streambuf>
#include <sstream>
#include <string>

#include "vtkFloatArray.h" 
#include "vtkCellArray.h" 
#include "vtkPoints.h" 
#include "vtkPointData.h"
#include "vtkDataSet.h"
#include "vtkUnstructuredGrid.h"

#include "unstructuredGrid.h"

using namespace std;


void setUnstructuredGrid(spaceMesh myMesh, vtkUnstructuredGrid * vtkMesh) {

  cout << "--- setUnstructuredGrid ---" << endl;

  vtkPoints *points;

  if( myMesh.geo==2 )
    cout << "WARNING this program is not compatible with 2D geometries (yet)" << endl;

  cout << "\tgeometry: " << myMesh.geo << "D" << endl;

  //---------------------------------------------------------------------


  if( myMesh.nVert!=0 ) {
    cout << "\tNumber of vertices=   " << myMesh.nVert   << endl;
    int n=0;
    points  = vtkPoints    ::New();
      points->SetNumberOfPoints(myMesh.nVert);
      for( int j=0 ; j<myMesh.nVert ; j++ ){
        float xyz[3] ;
        if( myMesh.geo==2 ) xyz[2]=0;
        for( int i=0 ; i<myMesh.geo ; i++) {
          xyz[i]=myMesh.vertx[n];
          n++;
        }
        points ->InsertPoint(j,xyz);
      }
      vtkMesh->SetPoints(points);
      points->Delete();
    }


  //---------------------------------------------------------------------


  if( myMesh.nH6!=0 ) {
    cout << "\tNumber of hexahedra= " << myMesh.nH6 << endl;
    int n=0;
    for(int i=0 ; i<myMesh.nH6 ; i++) {
      int ijk[8];
      for( int j=0 ; j<8 ; j++) {
        ijk[j]=myMesh.hexas[n]-1;
        n++;
      }
      n++;
      vtkMesh->InsertNextCell(VTK_HEXAHEDRON, 8, ijk);
    }
  }


  //---------------------------------------------------------------------


  if( myMesh.nT4!=0 ) {
    cout << "\tNumber of tetrahedra= " << myMesh.nT4 << endl;
    int n=0;
    for(int i=0 ; i<myMesh.nT4 ; i++) {
      int ijk[4];
      for( int j=0 ; j<4 ; j++) {
        ijk[j]=myMesh.tetra[n]-1;
        n++;
      }
      n++;
      vtkMesh->InsertNextCell(VTK_TETRA, 4, ijk);
    }
  }

  //---------------------------------------------------------------------


  if( myMesh.nQ4!=0 ) {
    cout << "\tNumber of quadrangles= " << myMesh.nQ4 << endl;
    int n=0;
    for(int i=0 ; i<myMesh.nQ4 ; i++) {
      int ijk[4];
      for( int j=0 ; j<4 ; j++) {
        ijk[j]=myMesh.quadr[n]-1;
        n++;
      }
      n++;
      vtkMesh->InsertNextCell(VTK_QUAD, 4, ijk);
    }
  }

  //---------------------------------------------------------------------


  if( myMesh.nT3!=0 ) {
    cout << "\tNumber of triangles=  " << myMesh.nT3     << endl;
    int n=0;
    for (int i=0 ; i<myMesh.nT3 ; i++) {
      int ijk[3]={0,0,0};
      for( int j=0 ; j<3 ; j++) {
        ijk[j]=myMesh.trian[n]-1;
        n++;
      }
      n++; // jump one int
      vtkMesh->InsertNextCell(VTK_TRIANGLE, 3, ijk);
    }
  }

  //---------------------------------------------------------------------

  if( myMesh.nL2!=0 ) {
    cout << "\tNumber of edges=      " << myMesh.nL2     << endl;
    int n=0;
    for (int i=0 ; i<myMesh.nL2 ; i++) {
      int ijk[2];
      for( int j=0 ; j<2 ; j++) {
        ijk[j]=myMesh.edges[n]-1;
        n++;
      }
      n++;
      vtkMesh->InsertNextCell(VTK_LINE, 2, ijk);
    }
  }

  //---------------------------------------------------------------------
 
  if( myMesh.nField!=0 ) {
    cout << "\tNumber of fields=     " << myMesh.nField << endl;
    int m=0;
    for(int i=0 ; i<myMesh.nField ; i++ ) {
      switch(myMesh.kind[i]) {
      case 1:
        m+=1;
        break;
      case 2:
        m+=3;
        break;
      }
    }


    vtkFloatArray *field[myMesh.nField];
    for(int i=0 ; i<myMesh.nField ; i++ ) {
      field[i]=vtkFloatArray::New();
      ostringstream oss;
      string str;
      oss.str("");
      switch(myMesh.kind[i]) {
      case 1:
        oss << "scalar_field" << i;
        str = oss.str();
        cout << "\t\t" << oss.str() << endl;
        field[i]->SetName(str.c_str());
        field[i]->SetNumberOfTuples(myMesh.nVert);
        field[i]->SetNumberOfComponents(1);
        for (int j=0 ; j<myMesh.nVert ; j++) {
          float sca;
          sca=myMesh.solu[j*m+i];
          field[i]->InsertTuple1(j,sca);
        }
        break;
      case 2:
        oss << "vector_field" << i;
        str = oss.str();
        cout << "\t\t" << oss.str() << endl;
        field[i]->SetName(str.c_str());
        field[i]->SetNumberOfTuples(myMesh.nVert);
        field[i]->SetNumberOfComponents(3);
        for (int j=0 ; j<myMesh.nVert ; j++) {
          float vec[3];
          int l=j*m+i;
          vec[0]=myMesh.solu[  l];
          vec[1]=myMesh.solu[++l];
          vec[2]=myMesh.solu[++l];
          field[i]->InsertTuple(j,vec);
        }
        break;
      }
      vtkMesh->GetPointData()->SetScalars(field[i]);
    }

    vtkMesh->GetPointData()->SetScalars(field[0]);
    for(int i=0 ; i<myMesh.nField ; i++) {
      vtkMesh->GetPointData()->AddArray(field[i]);
      field[i]->Delete();
    }

  }
  cout << "--- setUnstructuredGrid ---" << endl << endl;
  return;
}

