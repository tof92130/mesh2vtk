# - Find the MAGMA library
#
# Usage:
#   find_package(MAGMA [REQUIRED] [QUIET] )
#
# It sets the following variables:
#   MAGMA_FOUND               ... true if magma is found on the system
#   MAGMA_LIBRARY_DIRS        ... full path to magma library
#   MAGMA_INCLUDE_DIRS        ... magma include directory
#   MAGMA_LIBRARIES           ... magma libraries
#   MAGMA_SPARSE_LIBRARIES    ... magma_sparse libraries
#
# The following variables will be checked by the function
#   MAGMA_USE_STATIC_LIBS     ... if true, only static libraries are found
#   MAGMA_ROOT                ... if set, the libraries are exclusively searched
#                                 under this path

message("\n>> FindMAGMA: MAGMA_ROOT= $ENV{MAGMA_ROOT}")


#If environment variable MAGMA_ROOT is specified, it has same effect as MAGMA_ROOT
if( NOT MAGMA_ROOT AND NOT $ENV{MAGMA_ROOT} STREQUAL "" )
    set( MAGMA_ROOT $ENV{MAGMA_ROOT} )
    # set include directories
    set(MAGMA_INCLUDE_DIRS ${MAGMA_ROOT}/include)
    # set library directories
    set(MAGMA_LIBRARY_DIRS ${MAGMA_ROOT}/lib)
    
    # set libraries magma
    find_library(
        MAGMA_LIBRARIES
        HINTS ${MAGMA_LIBRARY_DIRS}/lib $ENV{MAGMA_LIBRARY_DIRS}/lib
        NAMES "magma"
        PATHS ${MAGMA_ROOT}/lib
        NO_DEFAULT_PATH
        DOC "The MAGMA library"
    )

    # set libraries magma_sparse
    find_library(
        MAGMA_SPARSE_LIBRARIES
        HINTS ${MAGMA_LIBRARY_DIRS}/lib $ENV{MAGMA_LIBRARY_DIRS}/lib
        NAMES "magma_sparse"
        PATHS ${MAGMA_ROOT}/lib
        NO_DEFAULT_PATH
        DOC "The MAGMA library"
    )
    
    set(MAGMA_FOUND TRUE)
else()
    set(MAGMA_FOUND FALSE)
endif()


message("   FindMAGMA: MAGMA_FOUND=            ${MAGMA_FOUND}")
message("   FindMAGMA: MAGMA_INCLUDE_DIRS=     ${MAGMA_INCLUDE_DIRS}")
message("   FindMAGMA: MAGMA_LIBRARY_DIRS=     ${MAGMA_LIBRARY_DIRS}")
message("   FindMAGMA: MAGMA_LIBRARIES=        ${MAGMA_LIBRARIES}")
message("   FindMAGMA: MAGMA_SPARSE_LIBRARIES= ${MAGMA_SPARSE_LIBRARIES}")

message("<< FindMAGMA\n")