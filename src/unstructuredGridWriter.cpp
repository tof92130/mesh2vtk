
#include <iostream>
#include <string>

#include "vtkUnstructuredGrid.h"
#include "vtkUnstructuredGridWriter.h"

#include "unstructuredGridWriter.h"

using namespace std;


//void writeUnstructuredGrid(vtkUnstructuredGrid *mesh, char *fileOut, bool bin) {

void writeVtkUnstructuredGrid(vtkUnstructuredGrid *mesh, string fileOut) {

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
	name+="vtk";

	cout << "Saving vtkUnstructuredGrid: "<< name << endl;
    
	vtkUnstructuredGridWriter * writer;
	writer=vtkUnstructuredGridWriter::New();
	writer->SetFileName( name.c_str() );
	bool bin=0;
	if( bin ) writer->SetFileTypeToBinary();
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(mesh);
#else
  writer->SetInputData(mesh);
#endif
	writer->Write();
	writer->Delete(); 

	cout << "------------------------------------------------------------------------" << endl << endl;

	return;
}



void writePlot3DUnstructuredGrid(vtkUnstructuredGrid *mesh, string  fileOut) {

	cout << "------------------------------------------------------------------------" << endl;

	int i=0;
	bool test=0;
	while (i<fileOut.length() && test==0) {
		if( fileOut.at(i)=='.' ) {
			test=1;
		}
		i++;
	}
  
	string name;
	name.append(fileOut,0,i);
	name+="xyz";

	cout << "Saving plt3dUnstructuredGrid: "<< name << endl;


	vtkUnstructuredGridWriter * writer;
	writer = vtkUnstructuredGridWriter::New();
	writer->SetFileName( name.c_str() );
	//writer->SetFileTypeToBinary();
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(mesh);
#else
  writer->SetInputData(mesh);
#endif
	writer->Write();
	writer->Delete(); 

	cout << "------------------------------------------------------------------------" << endl << endl;

}
