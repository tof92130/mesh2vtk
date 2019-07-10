# - Try to find CWIPI
# Once done this will define
#
#  CWIPI_FOUND        - system has found CWIPI
#  CWIPI_INCLUDE_DIR  - include directories for CWIPI
#  CWIPI_LIBRARIES    - libraries for CWIPI
#  CWIPI_VERSION      - version for CWIPI
#

set(CWIPI_FOUND FALSE)

message(">> FindCWIPI: CWIPI_DIR= $ENV{CWIPI_DIR}")

# Check for header file
find_path(CWIPI_INCLUDE_DIR cwipi_config.h cwipi_configf.h cwipi.h  cwipi.mod
  HINTS ${CWIPI_DIR}/include $ENV{CWIPI_DIR}/include
  DOC "Directory where the CWIPI header is located"
)

message("   FindCWIPI: CWIPI_INCLUDE_DIR= ${CWIPI_INCLUDE_DIR}")

# Check for cwipi_f
find_library(CWIPIF_LIBRARY
  NAMES cwpf
  HINTS ${CWIPI_DIR}/lib $ENV{CWIPI_DIR}/lib
  NO_DEFAULT_PATH
  DOC "The CWIPI library"
)
find_library(CWIPIF_LIBRARY
  NAMES cwpf 
  DOC "The CWIPI library"
)

#message("   FindCWIPI: CWIPIF_LIBRARY= ${CWIPIF_LIBRARY}")


# Check for cwipi
find_library(CWIPI_LIBRARY
  NAMES cwp
  HINTS ${CWIPI_DIR}/lib $ENV{CWIPI_DIR}/lib
  NO_DEFAULT_PATH
  DOC "The CWIPI library"
  )
find_library(CWIPI_LIBRARY
  NAMES cwp
  DOC "The CWIPI library"
  )

#message("   FindCWIPI: CWIPI_LIBRARY= $ENV{CWIPI_LIBRARY}")


# Check for cwipi-config
#find_program(CWIPI_CONFIG_EXE
#  NAMES cwipi-config    
#  HINTS ${CWIPI_DIR}/bin $ENV{CWIPI_DIR}/bin
#  NO_DEFAULT_PATH
#  DOC "The CWIPI config executable"
#  )
#find_program(CWIPI_CONFIG_EXE
#  NAMES cwipi-config    
#  DOC "The CWIPI config executable"
#  )

#set(CWIPI_LIBRARIES ${CWIPIF_LIBRARY}                   CACHE STRING "CWIPI libraries")
#set(CWIPI_LIBRARIES ${CWIPI_LIBRARIES} ${CWIPI_LIBRARY} CACHE STRING "CWIPI libraries")
#set(CWIPI_LIBRARIES ${CWIPI_LIBRARIES} ${FVMC_LIBRARY}  CACHE STRING "CWIPI libraries")
#set(CWIPI_LIBRARIES ${CWIPI_LIBRARIES} ${BFTC_LIBRARY}  CACHE STRING "CWIPI libraries")


set(CWIPI_LIBRARIES ${CWIPIF_LIBRARY} ${CWIPI_LIBRARY} CACHE STRING "CWIPI libraries")

#message("   FindCWIPI: CWIPIF_LIBRARY= ${CWIPIF_LIBRARY}")
#message("   FindCWIPI: CWIPI_LIBRARY=  ${CWIPI_LIBRARY}")
#message("-> FindCWIPI: CWIPI_LIBRARIES=${CWIPI_LIBRARIES}")


unset(CWIPIF_LIBRARY CACHE)
unset(CWIPI_LIBRARY CACHE)



#if (CWIPI_INCLUDE_DIR AND CWIPI_LIBRARIES AND CWIPI_CONFIG_EXE)
#
#    execute_process(COMMAND ${CWIPI_CONFIG_EXE} --version
#                    OUTPUT_VARIABLE OUTPUT
#                    ERROR_VARIABLE ERROR_VAR)
#
#    if (OUTPUT)
#      set(CWIPI_VERSION ${OUTPUT} CACHE TYPE STRING)
#      mark_as_advanced(CWIPI_VERSION)
#    endif()
#
#    # Check if version found is >= required version
#
#    if (CWIPI_FIND_VERSION)
#     if (NOT "${CWIPI_VERSION}" VERSION_LESS "${CWIPI_FIND_VERSION}")
#        set(CWIPI_VERSION_OK TRUE)
#       endif()
#    else()
#   # No specific version requested
#      set(CWIPI_VERSION_OK TRUE)
#     endif()
#endif()

#set(CWIPI_VERSION_OK TRUE)

#mark_as_advanced(CWIPI_VERSION_OK)

# Standard package handling
find_package_handle_standard_args(CWIPI
                                  "CWIPI could not be found. Be sure to set CWIPI_DIR."
                                  CWIPI_LIBRARIES
                                  CWIPI_INCLUDE_DIR)


if (CWIPI_FOUND)
    if (NOT CWIPI_FIND_QUIETLY OR CWIPI_FIND_DEBUG)
        message(STATUS
            "CWIPI was found:\n"
            "   CWIPI_INCLUDE_DIRS: ${CWIPI_INCLUDE_DIRS}\n"
            "   CWIPI_LIBRARY_DIRS: ${CWIPI_LIBRARY_DIRS}\n"
            "   CWIPI_LIBRARIES:    ${CWIPI_LIBRARIES}"
        )
    endif()
else()
    if (CWIPI_FIND_REQUIRED)
        message(SEND_ERROR "CWIPI could not be found.")
    else()
        message(STATUS "CWIPI could not be found.")
    endif()
endif()

mark_as_advanced(CWIPI_LIBRARIES
                 CWIPI_INCLUDE_DIR)

#mark_as_advanced(CWIPI_LIBRARIES
#                 CWIPI_INCLUDE_DIR
#                 CWIPI_CONFIG_EXE)


unset(CWIPIF_LIBRARY CACHE)
unset(CWIPI_LIBRARY CACHE)

message("   FindCWIPI: CWIPI_FOUND=       ${CWIPI_FOUND}")
message("   FindCWIPI: CWIPI_INCLUDE_DIR= ${CWIPI_INCLUDE_DIR}")
message("   FindCWIPI: CWIPI_LIBRARIES=   ${CWIPI_LIBRARIES}")
#message("   FindCWIPI: CWIPI_VERSION=     ${CWIPI_VERSION}")

message("<< FindCWIPI\n")
