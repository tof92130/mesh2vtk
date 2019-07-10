# - Try to find FOX
# Once done this will define
#
#  FOX_FOUND        - system has FOX
#  FOX_INCLUDE_DIRS - include directories for FOX
#  FOX_LIBRARIES    - libraries for FOX
#=============================================================================

set(FOX_FOUND FALSE)

message("\n>> FindFOX: FOX_DIR= $ENV{FOX_DIR}")



find_path(FOX_INCLUDE_DIRS
	NAMES fox_common.mod 
	HINTS ${FOX_DIR}/modules  $ENV{FOX_DIR}/modules
    NO_DEFAULT_PATH
    "Directory where the FOX modules are located"
	)
#message("   FindFOX: FOX_INCLUDE_DIRS= ${FOX_INCLUDE_DIRS}")


    
#mark_as_advanced(FOX_INCLUDE_DIRS)

message("   FindFOX: FOX_INCLUDE_DIRS= ${FOX_INCLUDE_DIRS}")

find_library(FOX_LIBRARIES
	NAMES   FoX_wxml
	HINTS ${FOX_DIR}/lib $ENV{FOX_DIR}/lib
	NO_DEFAULT_PATH
	DOC "The FOX library"
	)
	 
message("   FindFOX: FOX_LIBRARIES= ${FOX_LIBRARIES}")


#set(FOX_LIBRARIES ${FOX_LIBRARY} CACHE STRING "FOX libraries")
#mark_as_advanced(FOX_LIBRARIES)


find_package_handle_standard_args(FOX
	"FOX could not be found. Be sure to set FOX_DIR."
	FOX_LIBRARIES)


if( FOX_INCLUDE_DIRS AND FOX_LIBRARIES )

  mark_as_advanced(FOX_INCLUDE_DIRS FOX_LIBRARIES)

endif()

message("   FindFOX: FOX_FOUND=        ${FOX_FOUND}")
message("   FindFOX: FOX_INCLUDE_DIRS= ${FOX_INCLUDE_DIRS}")
message("   FindFOX: FOX_LIBRARIES=    ${FOX_LIBRARIES}")
message("<< FindFOX\n")