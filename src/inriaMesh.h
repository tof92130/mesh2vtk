# ifndef __INRIAMESH_H
# define __INRIAMESH_H


#include <string>
#include "vtkUnstructuredGrid.h"

using namespace std;


class inriaMesh{

private:
	int geo;
	string meshName;
	string soluName;
	vtkUnstructuredGrid * mesh;
	int nVer;
	int nHex;
	int nTet;
	int nTet2;
	int nQad;
	int nTri;
	int nTri2;
	int nEdg;
	int nFld;
	int nCpn;
	int nSol;
	int kind[20];

public:
     inriaMesh();
    ~inriaMesh();
    vtkUnstructuredGrid * getMesh();
    string getMeshName();
    void setMeshName(string);
    string getSoluName();
    void setSoluName(string);
    void display();
    void inriaMeshReader();
    void inriaSoluReader();
};


# endif