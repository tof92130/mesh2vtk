# - Try to find ParMETIS
# Once done this will define
#
#  PARMETIS_FOUND        - system has ParMETIS
#  PARMETIS_INCLUDE_DIRS - include directories for ParMETIS
#  PARMETIS_LIBRARIES    - libraries for ParMETIS
#  PARMETIS_VERSION      - version for ParMETIS
#=============================================================================

set(PARMETIS_FOUND FALSE)

message("\n>> FindParMETIS: PARMETIS_DIR= $ENV{PARMETIS_DIR}")


find_path(PARMETIS_INCLUDE_DIRS parmetis.h
     HINTS ${PARMETIS_DIR}/include $ENV{PARMETIS_DIR}/include
     NO_DEFAULT_PATH
     "Directory where the ParMETIS header is located"
    )

find_path(PARMETIS_INCLUDE_DIRS parmetis.h
     "Directory where the ParMETIS header is located"
     )

mark_as_advanced(PARMETIS_INCLUDE_DIRS)

message("   FindParMETIS: PARMETIS_INCLUDE_DIRS= ${PARMETIS_INCLUDE_DIRS}")

find_library(PARMETIS_LIBRARY   parmetis 
     HINTS ${PARMETIS_DIR}/lib $ENV{PARMETIS_DIR}/lib
     NO_DEFAULT_PATH
     DOC "The ParMETIS library"
     ) 
find_library(PARMETIS_LIBRARY   parmetis 
     DOC "The ParMETIS library"
     ) 
message("   FindParMETIS: PARMETIS_LIBRARY= ${PARMETIS_LIBRARY}")


find_library(METIS_LIBRARY   metis 
     HINTS ${PARMETIS_DIR}/lib $ENV{PARMETIS_DIR}/lib
     NO_DEFAULT_PATH
     DOC "The ParMETIS library"
     ) 
find_library(METIS_LIBRARY   metis 
     DOC "The ParMETIS library"
     )
message("   FindParMETIS: METIS_LIBRARY= ${METIS_LIBRARY}")


set(PARMETIS_LIBRARIES ${PARMETIS_LIBRARY} ${METIS_LIBRARY} CACHE STRING "ParMETIS libraries")
mark_as_advanced(PARMETIS_LIBRARIES)

message("   FindParMETIS: PARMETIS_LIBRARIES= ${PARMETIS_LIBRARIES}")



if (PARMETIS_LIBRARIES AND PARMETIS_INCLUDE_DIRS)
  
  if (PARMETIS_LIBRARY)
    string(REGEX REPLACE "(^.*)/lib/libparmetis.*$" "\\1" PARMETIS_LIBRARY_PATH ${PARMETIS_LIBRARY} )
  endif (PARMETIS_LIBRARY)
  
  # Set flags for building test program
  set(CMAKE_REQUIRED_INCLUDES  ${PARMETIS_INCLUDE_DIRS} ${MPI_C_INCLUDE_PATH})
  set(CMAKE_REQUIRED_LIBRARIES ${PARMETIS_LIBRARIES}    ${MPI_C_LIBRARIES})
  set(CMAKE_REQUIRED_FLAGS     ${CMAKE_REQUIRED_FLAGS}  ${MPI_C_COMPILE_FLAGS})
  
  #message("   FindParMETIS: MPI_C_INCLUDE_PATH=  ${MPI_C_INCLUDE_PATH}")
  #message("   FindParMETIS: MPI_C_LIBRARIES=     ${MPI_C_LIBRARIES}")
  #message("   FindParMETIS: MPI_C_COMPILE_FLAGS= ${MPI_C_COMPILE_FLAGS}")
  
  # Check ParMETIS version
  message("   FindParMETIS: Check ParMETIS version")
  set(PARMETIS_CONFIG_TEST_VERSION_C "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/parmetis_config_test_version.c")
  
  message("   FindParMETIS: Writing ${PARMETIS_CONFIG_TEST_VERSION_C}")
  file(WRITE ${PARMETIS_CONFIG_TEST_VERSION_C} "
#include <stdio.h> 
#include \"parmetis.h\"

int main() {
#ifdef PARMETIS_SUBMINOR_VERSION
  printf(\"%i.%i.%i\\n\",
         PARMETIS_MAJOR_VERSION,
         PARMETIS_MINOR_VERSION,
         PARMETIS_SUBMINOR_VERSION);
#else
  printf(\"%i.%i\\n\",
         PARMETIS_MAJOR_VERSION,
         PARMETIS_MINOR_VERSION);
#endif
  return 0;
}
")
  
  
  message("   FindParMETIS: Execute parmetis_config_test_version.c")
  try_run(
     PARMETIS_CONFIG_TEST_VERSION_EXITCODE
     PARMETIS_CONFIG_TEST_VERSION_COMPILED
     ${CMAKE_CURRENT_BINARY_DIR}
     ${PARMETIS_CONFIG_TEST_VERSION_C}
     CMAKE_FLAGS
        "-DINCLUDE_DIRECTORIES:STRING=${CMAKE_REQUIRED_INCLUDES}"
        "-DLINK_LIBRARIES:STRING=${CMAKE_REQUIRED_LIBRARIES}"
     COMPILE_OUTPUT_VARIABLE PARMETIS_CONFIG_TEST_VERSION_COMPILE_OUTPUT
     RUN_OUTPUT_VARIABLE PARMETIS_CONFIG_TEST_VERSION_OUTPUT
  )
  
  ##message("   FindParMETIS: PARMETIS_CONFIG_TEST_VERSION_COMPILE_OUTPUT ${PARMETIS_CONFIG_TEST_VERSION_COMPILE_OUTPUT}")
  ##message("   FindParMETIS: PARMETIS_CONFIG_TEST_VERSION_OUTPUT ${PARMETIS_CONFIG_TEST_VERSION_OUTPUT}")
  
  message("   FindParMETIS: PARMETIS_CONFIG_TEST_VERSION_COMPILED ${PARMETIS_CONFIG_TEST_VERSION_COMPILED}")
  message("   FindParMETIS: PARMETIS_CONFIG_TEST_VERSION_EXITCODE ${PARMETIS_CONFIG_TEST_VERSION_EXITCODE}")
  
  
  if (   (NOT PARMETIS_CONFIG_TEST_VERSION_COMPILED)
      OR (NOT (PARMETIS_CONFIG_TEST_VERSION_EXITCODE EQUAL 0))) 
      
      message(WARNING "Unable to determine ParMETIS version")
      set(PARMETIS_VERSION_OK TRUE)
      set(PARMETIS_VERSION "??.??.??" CACHE TYPE STRING)
      
  else ()
      
      #message("   FindParMETIS: PARMETIS_VERSION ${PARMETIS_VERSION}")
      
      set(PARMETIS_VERSION ${PARMETIS_CONFIG_TEST_VERSION_OUTPUT} CACHE TYPE STRING)
      mark_as_advanced(PARMETIS_VERSION)
      message("   FindParMETIS: ParMETIS_FIND_VERSION ${ParMETIS_FIND_VERSION}")
      if (ParMETIS_FIND_VERSION)
        # Check if version found is >= required version
        if (NOT "${PARMETIS_VERSION}" VERSION_LESS "${ParMETIS_FIND_VERSION}") 
          set(PARMETIS_VERSION_OK TRUE)
        endif()
      else()
        # No specific version requested
          set(PARMETIS_VERSION_OK TRUE)
      endif()
  endif()
  mark_as_advanced(PARMETIS_VERSION_OK)
  
endif()


find_package_handle_standard_args(ParMETIS
                                  "ParMETIS could not be found/configured."
                                  PARMETIS_LIBRARIES
                                  PARMETIS_INCLUDE_DIRS
                                  PARMETIS_VERSION
                                  PARMETIS_VERSION_OK)

mark_as_advanced(PARMETIS_LIBRARIES
                 PARMETIS_INCLUDE_DIRS
                 PARMETIS_VERSION
                 PARMETIS_VERSION_OK)


#find_package_handle_standard_args(ParMETIS
#                                  "ParMETIS could not be found/configured."
#                                  PARMETIS_LIBRARIES
#                                  PARMETIS_INCLUDE_DIRS)

#mark_as_advanced(PARMETIS_LIBRARIES
#                 PARMETIS_INCLUDE_DIRS)


unset(PARMETIS_LIBRARY CACHE)
unset(METIS_LIBRARY    CACHE)


message("   FindParMETIS: PARMETIS_FOUND=        ${PARMETIS_FOUND}")
message("   FindParMETIS: PARMETIS_INCLUDE_DIRS= ${PARMETIS_INCLUDE_DIRS}")
message("   FindParMETIS: PARMETIS_LIBRARIES=    ${PARMETIS_LIBRARIES}")
message("   FindParMETIS: PARMETIS_VERSION=      ${PARMETIS_VERSION}")
message("<< FindParMETIS\n")