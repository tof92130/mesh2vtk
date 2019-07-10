# Liste de tous les sources
# -------------------------

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES
	${PROJECT_SOURCE_DIR}/src/*.c
	${PROJECT_SOURCE_DIR}/src/*.cpp
)



add_executable(Mesh2VTK ${SOURCES})

#set_target_properties(Mesh2VTK PROPERTIES LINKER_LANGUAGE Fortran)

target_include_directories(Mesh2VTK
	INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
	PRIVATE   ${CMAKE_CURRENT_BINARY_DIR}
	PRIVATE   ${CMAKE_BINARY_DIR}
	PUBLIC    ${CMAKE_CURRENT_SOURCE_DIR}
)

#if (BLAS_FOUND)
#	target_include_directories(Mesh2VTK PRIVATE ${BLAS_INCLUDE_DIRS})
#	target_link_libraries(Mesh2VTK ${BLAS_LIBRARIES})
#endif (BLAS_FOUND)


if (VTK_FOUND)
   target_include_directories(Mesh2VTK PRIVATE ${VTK_INCLUDE_DIRS})
   target_link_libraries     (Mesh2VTK         ${VTK_LIBRARIES})
endif (VTK_FOUND)


if (LIBMESH_FOUND)
   #message("\n\n\n")
   message("    LIBMESH_FOUND        ${LIBMESH_FOUND}")
   message("    LIBMESH_INCLUDE_DIR  ${LIBMESH_INCLUDE_DIR}")
   message("    LIBMESH_LIBRARIES    ${LIBMESH_LIBRARIES}")
   #message("\n\n\n")
   
   target_include_directories(Mesh2VTK PRIVATE ${LIBMESH_INCLUDE_DIR})
   target_link_libraries     (Mesh2VTK         ${LIBMESH_LIBRARIES})
endif (LIBMESH_FOUND)


install(TARGETS Mesh2VTK RUNTIME DESTINATION .)



