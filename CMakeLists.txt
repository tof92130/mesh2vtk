# Top level CMakeLists.txt file for PTK

# Require CMake 2.8
cmake_minimum_required(VERSION 2.8)

project(MESH2VTK C CXX Fortran)

message("Source du projet:      ${MESH2VTK_SOURCE_DIR}")
message("Compilation du projet: ${MESH2VTK_BINARY_DIR}")

#------------------------------------------------------------------------------
# Definition de la version MESH2VTK
#------------------------------------------------------------------------------
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE)

# Defintion de la version pour le futur
# CMake pilotera l'ensemble via la generation de fichier de configuration
# Ces fichiers seront ensuite inclus dans les sources de MESH2VTK
set(MESH2VTK_VERSION_MAJOR "2019")
set(MESH2VTK_VERSION_MINOR "7")
set(MESH2VTK_VERSION_MICRO "9")
set(MESH2VTK_VERSION "${MESH2VTK_VERSION_MAJOR}.${MESH2VTK_VERSION_MINOR}.${MESH2VTK_VERSION_MICRO}")

message("Version du projet: ${MESH2VTK_VERSION}")

#------------------------------------------------------------------------------
# Utilisation des flags de compilation par dÈfaut du projet
# (Flags par dÈfaut sont dÈfinis plus bas dans le fichier) 
#------------------------------------------------------------------------------

option(MESH2VTK_ENABLE_DEFAULT_FLAGS "Enable default flags" ON)


#------------------------------------------------------------------------------
# Localisation des fonctions cmake du projet
#------------------------------------------------------------------------------

set(MESH2VTK_CMAKE_DIR "${MESH2VTK_SOURCE_DIR}/cmake" CACHE INTERNAL "")
set(CMAKE_MODULE_PATH "${MESH2VTK_CMAKE_DIR}/modules")

#------------------------------------------------------------------------------
# Activation des langages Fortran C et C++
#------------------------------------------------------------------------------

enable_language(Fortran)
enable_language(C)
enable_language(CXX)

get_filename_component (Fortran_COMPILER_NAME ${CMAKE_Fortran_COMPILER} NAME)
get_filename_component (C_COMPILER_NAME       ${CMAKE_C_COMPILER}       NAME)
get_filename_component (CXX_COMPILER_NAME     ${CMAKE_CXX_COMPILER}     NAME)

#message("   Fortran ${CMAKE_Fortran_COMPILER}")
#message("   C       ${CMAKE_C_COMPILER}"      )
#message("   C++     ${CMAKE_CXX_COMPILER}"    )




#------------------------------------------------------------------------------
# Construction par defaut : mode release
#------------------------------------------------------------------------------

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug MinSizeRel Release RelWithDebInfo." FORCE)
endif()


#------------------------------------------------------------------------------
# Flags de compilation Fortran par defaut suivant le compilateur
#------------------------------------------------------------------------------

include(${CMAKE_MODULE_PATH}/default_flags.cmake)




#------------------------------------------------------------------------------
# LIBMESH (INRIA) https://github.com/LoicMarechal/libMeshb.git
#------------------------------------------------------------------------------

find_package(LIBMESH  REQUIRED)

#------------------------------------------------------------------------------
# BLAS LAPACK
#------------------------------------------------------------------------------

#find_package(BLAS)
#find_package(LAPACK)

#------------------------------------------------------------------------------
# VTK
#------------------------------------------------------------------------------

find_package(VTK REQUIRED)   # decommenter pour activer VTK
if( VTK_FOUND )
  if("${VTK_VERSION}" VERSION_LESS 5.8)
    message("   Your VTK version is too old! Must be greater than ${VTK_VERSION}")
    message("   SPACE_ENABLE_VTK          OFF")
    set(__SPACE_VTK__ 0)
    set(VTK_FOUND FALSE)
  else()
    message("   Valid VTK version (${VTK_VERSION}).")
    #message("   VTK_LIBRARIES: ${VTK_LIBRARIES}")
  endif()
endif()


#------------------------------------------------------------------------------
# Ajout des sources de tous les elements du projet
# En fonction des top_targets a installer
#------------------------------------------------------------------------------

add_subdirectory(src)

#------------------------------------------------------------------------------
# Print summary of found and not found optional packages
#------------------------------------------------------------------------------

include(FeatureSummary)
FEATURE_SUMMARY(WHAT ALL)


