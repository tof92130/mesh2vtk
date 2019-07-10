# - Try to find TECIO
# Once done this will define
#
#  TECIO_FOUND        - system has TECIO
#  TECIO_LIBRARY      - libraries for TECIO
#=============================================================================

set(TECIO_FOUND FALSE)

#message(">> FindTECIO: TECIO_DIR= $ENV{TECIO_DIR}")


find_library(TECIO_LIBRARY  tecio 
     HINTS ${TECIO_DIR} $ENV{TECIO_DIR}
     NO_DEFAULT_PATH
     DOC "The TECIO library"
     ) 
message("   FindTECIO: TECIO_LIBRARY= ${TECIO_LIBRARY}")


if( TECIO_LIBRARY )
  # Set flags for building test program
  #set(CMAKE_REQUIRED_LIBRARIES ${TECIO_LIBRARY} ${MPI_C_LIBRARIES})
  #set(CMAKE_REQUIRED_FLAGS     ${CMAKE_REQUIRED_FLAGS} ${MPI_C_COMPILE_FLAGS})
  set(CMAKE_REQUIRED_LIBRARIES ${TECIO_LIBRARY})
  set(CMAKE_REQUIRED_FLAGS     ${CMAKE_REQUIRED_FLAGS})
endif()

find_package_handle_standard_args(TECIO
                                  "TECIO could not be found. Be sure to set TECIO_DIR."
                                  TECIO_LIBRARY)

if (TECIO_FOUND)
    if (NOT TECIO_FIND_QUIETLY OR TECIO_FIND_DEBUG)
        message(STATUS
            "TECIO was found:\n"
            "   TECIO_LIBRARY: ${TECIO_LIBRARY}"
        )
    endif()
else()
    if (TECIO_FIND_REQUIRED)
        message(SEND_ERROR "TECIO could not be found.")
    else()
        message(STATUS "TECIO could not be found.")
    endif()
endif()



mark_as_advanced(TECIO_LIBRARY)


#message("   FindTECIO: TECIO_FOUND=      ${TECIO_FOUND}")
#message("   FindTECIO: TECIO_LIBRARY=    ${TECIO_LIBRARY}")
#message("<< FindTECIO\n")

