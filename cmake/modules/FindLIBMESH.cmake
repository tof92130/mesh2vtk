# - Try to find LIBMESH
# Once done this will define
#
#  LIBMESH_FOUND        - system has found LIBMESH
#  LIBMESH_INCLUDE_DIR  - include directories for LIBMESH
#  LIBMESH_LIBRARIES    - libraries for LIBMESH
#

set(LIBMESH_FOUND FALSE)

message("\n>> FindLIBMESH: LIBMESH_DIR= $ENV{LIBMESH_DIR}")

#>>>>>>
# Check for header file
find_path(LIBMESH_INCLUDE_DIR libmeshb7.h libmeshb7.ins libmeshb7_mod.mod
  HINTS ${LIBMESH_DIR}/include $ENV{LIBMESH_DIR}/include
  DOC "Directory where the LIBMESH header is located"
)

message("   FindLIBMESH: LIBMESH_INCLUDE_DIR: ${LIBMESH_INCLUDE_DIR}")
#<<<<<<

#>>>>>>
# Check for libMeshbf.7.a
find_library(LIBMESHF
  NAMES Meshbf.7 
  DOC "The LIBMESH library"
)

message("   FindLIBMESH: LIBMESHF: ${LIBMESHF}")
#<<<<<<

#>>>>>>
# Check for LIBMESH
find_library(LIBMESH
  NAMES Meshb.7
  DOC "The LIBMESH library"
  )

message("   FindLIBMESH: LIBMESH : ${LIBMESH}")
#<<<<<<

#>>>>>>
#set(LIBMESH_LIBRARIES ${LIBMESHF} ${LIBMESH} CACHE STRING "LIBMESH libraries")
set(LIBMESH_LIBRARIES ${LIBMESH} CACHE STRING "LIBMESH libraries")
message("   FindLIBMESH: LIBMESH_LIBRARIES=${LIBMESH_LIBRARIES}")
#<<<<<<

#>>>>>>
unset(LIBMESHF CACHE)
unset(LIBMESH  CACHE)

# Standard package handling
#find_package_handle_standard_args(LIBMESH
#                                  "LIBMESH could not be found. Be sure to set LIBMESH_DIR."
#                                  LIBMESH_LIBRARIES
#                                  LIBMESH_INCLUDE_DIR)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBMESH
  FOUND_VAR     LIBMESH_FOUND
  REQUIRED_VARS LIBMESH_LIBRARIES
  REQUIRED_VARS LIBMESH_INCLUDE_DIR
  FAIL_MESSAGE "LIBMESH could not be found. Be sure to set LIBMESH_DIR."
  )

if (LIBMESH_FOUND)
    if (NOT LIBMESH_FIND_QUIETLY OR LIBMESH_FIND_DEBUG)
        message(STATUS
            "LIBMESH was found:\n"
            "   LIBMESH_INCLUDE_DIR: ${LIBMESH_INCLUDE_DIR}\n"
            "   LIBMESH_LIBRARIES:    ${LIBMESH_LIBRARIES}"
        )
    endif()
else()
    if (LIBMESH_FIND_REQUIRED)
        message(SEND_ERROR "LIBMESH could not be found.")
    else()
        message(STATUS "LIBMESH could not be found.")
    endif()
endif()

mark_as_advanced(LIBMESH_LIBRARIES
                 LIBMESH_INCLUDE_DIR)


message("   FindLIBMESH: LIBMESH_FOUND=       ${LIBMESH_FOUND}")
message("   FindLIBMESH: LIBMESH_INCLUDE_DIR= ${LIBMESH_INCLUDE_DIR}")
message("   FindLIBMESH: LIBMESH_LIBRARIES=   ${LIBMESH_LIBRARIES}")

message("<< FindLIBMESH\n")