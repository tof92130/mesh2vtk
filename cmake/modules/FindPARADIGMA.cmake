# - Try to find PARADIGMA    
# Once done this will define
#
#  PARADIGMA_FOUND        - system has found PARADIGMA
#  PARADIGMA_INCLUDE_DIR  - include directories for PARADIGMA
#  PARADIGMA_LIBRARIES    - libraries for PARADIGMA
#  PARADIGMA_VERSION      - version for PARADIGMA
#

set(PARADIGMA_FOUND FALSE)

message(">> FindPARADIGMA: PARADIGMA_DIR= $ENV{PARADIGMA_DIR}")

# Check for header files

find_path(PARADIGMA_INCLUDE_DIR mod_pdm_io.mod pdm_config.h pdm_io_tab.h pdm_part.h pdm_timer.h mod_cedre_io.mod pdm_config_f.h pdm_mpi.h pdm_part_dcube.h pdm_writer.h mod_pdm_writer.mod pdm_io.h pdm_mpi_node_first_rank.h pdm_partf.h
  HINTS ${PARADIGMA_DIR}/include $ENV{PARADIGMA_DIR}/include
  DOC "Directory where the PARADIGMA header is located"
)



# Check for lib directory

find_path(PARADIGMA_LIBRARY_DIRS libpdmaf.a libpdma.a libpdmf.a libpdm.a
  DOC "Directory where the PARADIGMA lib is located"
  HINTS ${PARADIGMA_DIR}/lib $ENV{PARADIGMA_DIR}/lib
)


# Check for lib files
find_library(PARADIGMA_LIBRARIES
  NAMES pdmaf pdma pdmf pdm 
  HINTS ${PARADIGMA_LIBRARY_DIRS}   #${PARADIGMA_DIR}/lib $ENV{PARADIGMA_DIR}/lib
  NO_DEFAULT_PATH
  DOC "The PARADIGMA library"
  )
  find_library(PARADIGMA_LIBRARIES
  NAMES pdmaf pdma pdmf pdm 
  DOC "The PARADIGMA library"
  )





message("   FindPARADIGMA: PARADIGMA_LIBRARIES  = ${PARADIGMA_LIBRARIES}"  )



#unset(PARADIGMAF_LIBRARY CACHE)
#unset(PARADIGMA_LIBRARY  CACHE)
#unset(PARADIGMF_LIBRARY  CACHE)
#unset(PARADIGM_LIBRARY   CACHE)



# Standard package handling
find_package_handle_standard_args(PARADIGMA
                                 "PARADIGMA could not be found. Be sure to set PARADIGMA_DIR."
                                  PARADIGMA_INCLUDE_DIR
                                  PARADIGMA_LIBRARIES
                                  )



if (PARADIGMA_FOUND)
    if (NOT PARADIGMA_FIND_QUIETLY OR PARADIGMA_FIND_DEBUG)
        message(STATUS
            "PARADIGMA was found:\n"
            "   PARADIGMA_INCLUDE_DIR: ${PARADIGMA_INCLUDE_DIR}\n"
            "   PARADIGMA_LIBRARY_DIR: ${PARADIGMA_LIBRARY_DIRS}\n"
            "   PARADIGMA_LIBRARIES:   ${PARADIGMA_LIBRARIES}"
        )
    endif()
else()
    if (PARADIGMA_FIND_REQUIRED)
        message(SEND_ERROR "PARADIGMA could not be found.")
    else()
        message(STATUS "PARADIGMA could not be found.")
    endif()
endif()


mark_as_advanced(PARADIGMA_LIBRARIES
                 PARADIGMA_INCLUDE_DIR
                 PARADIGMA_CONFIG_EXE
                 PARADIGMA_VERSION
                 PARADIGMA_VERSION_OK)

#mark_as_advanced(PARADIGMA_LIBRARIES
#                 PARADIGMA_INCLUDE_DIR
#                 PARADIGMA_CONFIG_EXE)

                 

message("   FindPARADIGMA: PARADIGMA_FOUND=       ${PARADIGMA_FOUND}")
message("   FindPARADIGMA: PARADIGMA_INCLUDE_DIR= ${PARADIGMA_INCLUDE_DIR}")
message("   FindPARADIGMA: PARADIGMA_LIBRARIES=   ${PARADIGMA_LIBRARIES}")
#message("   FindPARADIGMA: PARADIGMA_VERSION=    ${PARADIGMA_VERSION}")

message("<< FindPARADIGMA\n")
