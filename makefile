#     ------------------------------------------------------------------
#
#     makefile pour fortran IBM
#
#     Auteur : Christophe Peyret christophe.peyret@onera.fr
#     Copyright (c) 2003 ONERA/DSNA. All rights reserved.
#
#     ------------------------------------------------------------------


TARGET = spaceVTK


# Mac - Intel

LD  = /usr/bin/g++
CC  = /usr/bin/gcc
CXX = /usr/bin/g++

LD  = icpc
CC  = icc
CXX = icpc


SRCDIR   = ./src
OBJDIR   = ./obj
#DIREXE   = ./space_vtk.app/Contents/MacOS/
DIREXE   = ./
LIBDIR   = /usr/local/lib

VTK      =-I$(VTK_DIR)/include/vtk-8.1


#CCFLAGS  = -Wno-deprecated -no-cpp-precomp -mlong-branch $(VTK) -c -I./
#CXXFLAGS = -Wno-deprecated -no-cpp-precomp -mlong-branch $(VTK) -c -I./

CCFLAGS  =  $(VTK) -c -I./ -std=c++11
CXXFLAGS =  $(VTK) -c -I./ -std=c++11

#LDFLAGS = -cxxlib -fPIC -static-intel


#LIBFLAGS = -framework Cocoa -framework Carbon -framework AppKit -framework OpenGL -framework AGL\

#LIBFLAGS = -framework Cocoa  -framework AppKit -framework OpenGL -framework AGL\
LIBFLAGS = -framework Cocoa  -framework OpenGL \

LIBFLAGS = -L$(VTK_DIR)/lib/ \
#             -lvtkDICOMParser\
             -lvtkFiltering\
             -lvtkGenericFiltering\
             -lvtkGraphics\
             -lvtkHybrid \
             -lvtkIO\
             -lvtkImaging\
             -lvtkNetCDF\
             -lvtkRendering\
             -lvtkVolumeRendering\
             -lvtkWidgets\
             -lvtkexoIIc\
             -lvtkexpat\
             -lvtkfreetype\
             -lvtkftgl\
             -lvtkjpeg\
             -lvtkpng\
             -lvtksys\
             -lvtktiff

# Building


OBJS = \
       $(OBJDIR)/unstructuredGridWriter.o \
       $(OBJDIR)/unstructuredJPEGWriter.o \
       $(OBJDIR)/libmesh5.o \
       $(OBJDIR)/inriaMesh.o \
       $(OBJDIR)/mesh2vtk.o


$(TARGET) : $(OBJS) compil_date
	$(LD) $(LDFLAGS) $(OBJS) -o $(DIREXE)$(TARGET) $(LIBFLAGS)
	@echo  ----------- ${TARGET} created ----------- 


compil_date :
	touch src/mesh2vtk.cpp
	echo "#define COMPIL_DATE \""`date`"\""    >  compil.h
	echo "#define COMPIL_COMP \""`uname -n`"\"" >> compil.h
	echo "cout << '------------------------------------------------------------------------' << endl;" >  compil_date.h 
	echo "cout << 'space_vtk++ 2009 - Convert meshb/solb formats to vtk'                     << endl;" >> compil_date.h
	echo "cout << 'Copyright (c) ONERA, 1995-2009. All rights reserved'                      << endl;" >> compil_date.h
	echo "cout << 'Developped by Christophe Peyret'                                          << endl;" >> compil_date.h
	echo "cout << '                                                                        ' << endl;" >> compil_date.h 
	echo "cout << 'Compiled on" `date` "with" `uname -n`"'                                   << endl;" >> compil_date.h
	echo "cout << '------------------------------------------------------------------------' << endl;" >> compil_date.h 


# Compilation


$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo "*"
	@echo Compilation de $<
	@echo "*"
	$(CXX) $(CXXFLAGS) -o $@  $< 

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo Compilation de $<
	$(CC) $(CCFLAGS) -o $@  $< 

$(OBJDIR)/mesh2vtk.o : $(SRCDIR)/mesh2vtk.cpp compil_date
	@echo Compilation de mesh2vtk.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/mesh2vtk.o $(SRCDIR)/mesh2vtk.cpp


clean :
	\rm $(OBJS) $(DIREXE)$(TARGET)
