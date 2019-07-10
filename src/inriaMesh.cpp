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

#include "inriaMesh.h"

extern "C" {
#include "libmeshb7.h"
}



inriaMesh::inriaMesh(){
	// Creation of Object vtkUnstructuredGrid
    mesh=vtkUnstructuredGrid::New();
}

inriaMesh::~inriaMesh(){
	// Destruction object vtkUnstructuredGrid
	mesh->Delete();
}


vtkUnstructuredGrid * inriaMesh::getMesh(){
	return mesh;
}


string inriaMesh::getMeshName(){
	return meshName;
}

void inriaMesh::setMeshName(string name){
	meshName=name;
}

string inriaMesh::getSoluName(){
	return soluName;
}

void inriaMesh::setSoluName(string name){
	soluName=name;
}


void inriaMesh::display(){
	cout << "meshName: " << meshName << endl;
	cout << "soluName: " << soluName << endl;
}


void inriaMesh::inriaMeshReader() {
    
	cout << "inriaMesh::inriaMeshReader" << endl;
	
	long long meshIdx;
	int       InpVer;
	
	char * name;
	name = new char [meshName.size()+1];
	strcpy (name, meshName.c_str());
    
	if(!(meshIdx=GmfOpenMesh(name, GmfRead, &InpVer, &geo))) {
		cout << "Cannot open file: " << name << endl;
		return;
	}
    
	nVer = GmfStatKwd(meshIdx, GmfVertices      );
	nHex = GmfStatKwd(meshIdx, GmfHexahedra     );
	nTet = GmfStatKwd(meshIdx, GmfTetrahedra    );
	nTet2= GmfStatKwd(meshIdx, GmfTetrahedraP2  );
	nQad = GmfStatKwd(meshIdx, GmfQuadrilaterals);
	nTri = GmfStatKwd(meshIdx, GmfTriangles     );
	nTri2= GmfStatKwd(meshIdx, GmfTrianglesP2   );
	nEdg = GmfStatKwd(meshIdx, GmfEdges         );
    
	cout << "------------------------------------------------------------------------" << endl;
	cout << "Reading File: " << meshName << endl;
	cout << "\tGeometry " <<  geo << "D" << endl;
	cout << "\tNumber of Vertices=       " << nVer << endl;
	if( nHex !=0 )cout << "\tNumber of Hexahedra=      " << nHex  << endl;
	if( nTet !=0 )cout << "\tNumber of Tetrahedra=     " << nTet  << endl;
	if( nTet2!=0 )cout << "\tNumber of TetrahedraP2=   " << nTet2 << endl;
	if( nQad !=0 )cout << "\tNumber of Quadrilaterals= " << nQad  << endl;
	if( nTri !=0 )cout << "\tNumber of Triangles=      " << nTri  << endl;
	if( nTri2!=0 )cout << "\tNumber of TrianglesP2=    " << nTri2 << endl;
	if( nEdg !=0 )cout << "\tNumber of Edges=          " << nEdg  << endl;


	// Reading GmfVertices
	if( nVer|=0 ) {
		vtkPoints * points;
		points=vtkPoints::New();
		points->SetNumberOfPoints(nVer);
		double xyz[3];
		int m;
		GmfGotoKwd(meshIdx, GmfVertices);
		for(int i=0 ; i<nVer ; i++){
			GmfGetLin(meshIdx,GmfVertices,&xyz[0],&xyz[1],&xyz[2],&m);
			points->InsertPoint(i,xyz);
		}
		mesh->SetPoints(points);
		points->Delete();
	}
    
	// Reading GmfHexahedra
	if( nHex|=0 ) {
		vtkIdType ijk[8],m;
		GmfGotoKwd(meshIdx, GmfHexahedra);
		for(int i=0 ; i<nHex ; i++){
			GmfGetLin(meshIdx,GmfHexahedra,&ijk[0],&ijk[1],&ijk[2],&ijk[3],&ijk[4],&ijk[5],&ijk[6],&ijk[7],&m);
			ijk[0]--;
			ijk[1]--;
			ijk[2]--;      
			ijk[3]--;
			ijk[4]--;
			ijk[5]--;
			ijk[6]--;
			ijk[7]--;
			mesh->InsertNextCell(VTK_HEXAHEDRON, 8, ijk);
		}
	}
	
	// Reading GmfTetrahedra
	if( nTet|=0 ) {
		vtkIdType ijk[4],m;
		GmfGotoKwd(meshIdx, GmfTetrahedra);
		for(int i=0 ; i<nTet ; i++){
			GmfGetLin(meshIdx,GmfTetrahedra,&ijk[0],&ijk[1],&ijk[2],&ijk[3],&m);
			ijk[0]--;
			ijk[1]--;
			ijk[2]--;      
			ijk[3]--;
			mesh->InsertNextCell(VTK_TETRA, 4, ijk);
		}
	}

	// Reading GmfTetrahedraP2
	if( nTet2|=0 ) {
		vtkIdType ijk[10],m;
		GmfGotoKwd(meshIdx, GmfTetrahedraP2);
		for(int i=0 ; i<nTet2 ; i++){
			GmfGetLin(meshIdx,GmfTetrahedraP2,&ijk[0],&ijk[1],&ijk[2],&ijk[3],&ijk[4],&ijk[5],&ijk[6],&ijk[7],&ijk[8],&ijk[9],&m);
			ijk[0]--;
			ijk[1]--;
			ijk[2]--;      
			ijk[3]--;
			ijk[4]--;
			ijk[5]--;
			ijk[6]--;
			ijk[7]--;
			ijk[8]--;
			ijk[9]--;
			mesh->InsertNextCell(VTK_QUADRATIC_TETRA, 10, ijk);
		}
	}

	// Reading GmfQuadrilaterals
	if( nQad|=0 ) {
		vtkIdType ijk[4],m;
		GmfGotoKwd(meshIdx, GmfQuadrilaterals);
		for(int i=0 ; i<nQad ; i++){
			GmfGetLin(meshIdx,GmfQuadrilaterals,&ijk[0],&ijk[1],&ijk[2],&ijk[3],&m);
			ijk[0]--;
			ijk[1]--;
			ijk[2]--;      
			ijk[3]--;
			mesh->InsertNextCell(VTK_QUAD, 4, ijk);
		}
	}

	// Reading GmfTriangles
	if( nTri|=0 ) {
		vtkIdType ijk[3],m;
		GmfGotoKwd(meshIdx, GmfTriangles);
		for(int i=0 ; i<nTri ; i++){
			GmfGetLin(meshIdx,GmfTriangles,&ijk[0],&ijk[1],&ijk[2],&m);
			ijk[0]--;
			ijk[1]--;
			ijk[2]--;      
			mesh->InsertNextCell(VTK_TRIANGLE, 3, ijk);
		}
	}

	// Reading GmfTrianglesP2
	if( nTri2|=0 ) {
		vtkIdType ijk[6],m;
		GmfGotoKwd(meshIdx, GmfTrianglesP2);
		for(int i=0 ; i<nTri2 ; i++){
			GmfGetLin(meshIdx,GmfTrianglesP2,&ijk[0],&ijk[1],&ijk[2],&ijk[3],&ijk[4],&ijk[5],&m);
			ijk[0]--;
			ijk[1]--;
			ijk[2]--;      
			ijk[3]--;      
			ijk[4]--;      
			ijk[5]--;      
			mesh->InsertNextCell(VTK_QUADRATIC_TRIANGLE, 6, ijk);
		}
	}

	// Reading GmfEdges
	if( nEdg|=0 ) {
		vtkIdType ijk[2],m;
		GmfGotoKwd(meshIdx, GmfEdges);
		for(int i=0 ; i<nEdg ; i++){
			GmfGetLin(meshIdx,GmfEdges,&ijk[0],&ijk[1],&m);
			ijk[0]--;
			ijk[1]--;
			mesh->InsertNextCell(VTK_LINE, 2, ijk);
		}
	}

	// Closing File
	GmfCloseMesh(meshIdx);
    
	cout << "------------------------------------------------------------------------" << endl<< endl;
	
    if( mesh->GetNumberOfPoints()!=0 ){
      for(int i=0;i<3;++i)
      cout << mesh->GetBounds()[2*i] << " / " << mesh->GetBounds()[2*i+1] << "    " ;
      cout << endl;
    }
	
	
	return;
}




void inriaMesh::inriaSoluReader(){

	cout << "------------------------------------------------------------------------" << endl;
	cout << "Reading File: " << soluName << endl;
	cout << "\tGeometry " <<  geo << "D" << endl;

	int soluIdx,InpVer;


	char * name;
	name = new char [soluName.size()+1];
	strcpy(name, soluName.c_str());

	if(!(soluIdx = GmfOpenMesh(name, GmfRead, &InpVer, &geo))) {
		cout << "Cannot open file: " << name << endl;
		return;
	}

	nSol=GmfStatKwd(soluIdx, GmfSolAtVertices, &nFld, &nCpn, kind);


	cout << "\tNumber of Solutions=      " << nSol << endl;
	cout << "\tNumber of Fields=         " << nFld << endl;


	// Lecture des infos sur les champs

	if( nSol|=0 ) {
		vtkFloatArray *field[nFld];
		for(int i=0 ; i<nFld ; i++) {
			field[i]=vtkFloatArray::New();
			//      
			ostringstream oss;
			string str;
			oss.str("");
			switch(kind[i]) {
			case 1:
				oss << "scalarField" << i;        
				str=oss.str();
				cout << "\t\t" << oss.str() << endl;
				field[i]->SetName(str.c_str());
				field[i]->SetNumberOfComponents(1);
				field[i]->SetNumberOfTuples(nSol);
				break;
			case 2:
				oss << "vectorField" << i;
				str=oss.str();
				cout << "\t\t" << oss.str() << endl;
				field[i]->SetName(str.c_str());
				field[i]->SetNumberOfComponents(3);
				field[i]->SetNumberOfTuples(nSol);
				break;
			}
		}

		GmfGotoKwd(soluIdx, GmfSolAtVertices);
		float solu[nCpn];
		for(int i=0 ; i<nSol ; i++){
			GmfGetLin(soluIdx, GmfSolAtVertices, solu);
			int m=0;
			for(int j=0 ; j<nFld ; j++){
				switch(kind[j]) {
				case 1:
					field[j]->InsertTuple1(i,solu[m++]);
					break;
				case 2:
					float vec[3];
					vec[0]=solu[m++];
					vec[1]=solu[m++];
					vec[2]=solu[m++];
					field[j]->InsertTuple(i,vec);
				}
			}
		}

		mesh->GetPointData()->SetScalars(field[0]);
		for(int i=0 ; i<nFld ; i++){
			mesh->GetPointData()->AddArray(field[i]);
			field[i]->Delete();
		}
	}


	cout << "------------------------------------------------------------------------" << endl<< endl;
	GmfCloseMesh(soluIdx);
	return;
}
