# - Try to find DDSolv
# Once done this will define
#
#  DDSolv_FOUND        - system has DDSolv
#  DDSolv_LIBRARY      - libraries for DDSolv
#  DDSolv_INCLUDE_DIR  - includes   for DDSolv
#=============================================================================

set(DDSolv_FOUND FALSE)

message(">> FindDDSolv: DDSolv_DIR= $ENV{DDSolv_DIR}")


find_library(DDSolv_LIBRARY  DDSolv 
     HINTS ${DDSolv_DIR}/lib $ENV{DDSolv_DIR}/lib
     NO_DEFAULT_PATH
     DOC "Directory where the DDSolv library is located"
     ) 


     
find_path(DDSolv_INCLUDE_DIR io_param.mod 
	HINTS ${DDSolv_DIR}/modules  $ENV{DDSolv_DIR}/modules
    NO_DEFAULT_PATH
    DOC "Directory where the DDSolv modules are located"
	)


if(DDSolv_LIBRARY)
  # Set flags for building test program
  #set(CMAKE_REQUIRED_LIBRARIES ${DDSolv_LIBRARY} ${MPI_C_LIBRARIES})
  #set(CMAKE_REQUIRED_FLAGS     ${CMAKE_REQUIRED_FLAGS} ${MPI_C_COMPILE_FLAGS})
  set(CMAKE_REQUIRED_LIBRARIES ${DDSolv_LIBRARY})
  set(CMAKE_REQUIRED_FLAGS     ${CMAKE_REQUIRED_FLAGS})
endif()

find_package_handle_standard_args(DDSolv
                                  "DDSolv could not be found. Be sure to set DDSolv_DIR."
                                  DDSolv_LIBRARY)

if(DDSolv_FOUND)
   if (NOT DDSolv_FIND_QUIETLY OR DDSolv_FIND_DEBUG)
      message(STATUS
             "DDSolv was found:\n"
             "   DDSolv_LIBRARY: ${DDSolv_LIBRARY}"
        )
    endif()
else()
    if(DDSolv_FIND_REQUIRED)
        message(SEND_ERROR "DDSolv could not be found.")
    else()
        message(STATUS "DDSolv could not be found.")
    endif()
endif(DDSolv_FOUND)

mark_as_advanced(DDSolv_LIBRARY)

message("   FindDDSolv: DDSolv_FOUND=        ${DDSolv_FOUND}")
message("   FindDDSolv: DDSolv_LIBRARY=      ${DDSolv_LIBRARY}")
message("   FindDDSolv: DDSolv_INCLUDE_DIR=  ${DDSolv_INCLUDE_DIR}")
message("<< FindDDSolv\n")