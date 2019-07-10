#include <iostream>
#include <string.h>

#include "vtkUnstructuredGrid.h"
#include "inriaMesh.h"
#include "unstructuredGridDisplay.h"
#include "unstructuredGridWriter.h"
#include "unstructuredJPEGWriter.h"


extern "C" {
#include "libmeshb7.h"
}

//#include "compil.h"


using namespace std;


int main(int argc, char *argv[]) {   


	cout << "------------------------------------------------------------------------" << endl;
	cout <<                                                                               endl;
	cout << "space_vtk++ 2017 - Convert meshb/solb formats to vtk"                     << endl;
	cout <<                                                                               endl;
	cout << "Copyright (c) ONERA, 1995-2017. All rights reserved"                      << endl;
	cout << "Developped by Christophe Peyret"                                          << endl;
//	cout << "Compiled on " << COMPIL_DATE << " with " << COMPIL_COMP                   << endl;
	cout <<                                                                               endl;
	cout << "------------------------------------------------------------------------" << endl << endl;
    
	inriaMesh toto;
	
	string meshName;
	string soluName;
    
	switch(argc){
		case 1:{
			exit(1);
		}break;
		case 2:{
			meshName = *++argv;
			cout << "Mesh to Read " << meshName << endl;
			toto.setMeshName(meshName);
		}break;
		case 3:{
			cout << "Mesh to Read " << meshName << endl;
			cout << "Solu to Read " << soluName << endl;
			meshName = *++argv;
			soluName = *++argv;
			toto.setMeshName(meshName);
			toto.setSoluName(soluName);
		}break;
	}
	
//	toto.display();
    
    cout << "argc: " << argc << endl;
	toto.inriaMeshReader();
	toto.inriaSoluReader();
    
	vtkUnstructuredGrid *mesh;
	mesh=toto.getMesh();
    
	// saving vtkUnstructuredGrid to vtk format
	writeVtkUnstructuredGrid(mesh,meshName);
    
	// saving vtkUnstructuredGrid to plot3D format
	//writePlot3DUnstructuredGrid(mesh,meshName);

	// saving vtkUnstructuredGrid to JPG format
	writePngUnstructured(mesh,meshName);

	
	return 0;
}
