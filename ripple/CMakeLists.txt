add_executable(ripple main.cc)

target_link_libraries(
	ripple
	${OPENGL_LIBRARIES}
	${SDL_LIBRARY}
	${POLYCODE_LIBRARIES})

add_custom_command(TARGET ripple POST_BUILD
	COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/resources
		${CMAKE_CURRENT_BINARY_DIR}/resources)
