add_executable(ghost ghost.cc)

target_link_libraries(
	ghost
	${OPENGL_LIBRARIES}
	${SDL_LIBRARY}
	${POLYCODE_LIBRARIES})

add_custom_command(TARGET ghost POST_BUILD
	COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/resources
		${CMAKE_CURRENT_BINARY_DIR}/resources)
