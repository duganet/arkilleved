add_subdirectory(io)

set(arkilleved_SRCS
	Brick.cpp
	Button.cpp
	Frame.cpp
	main.cpp
	SDLUtils.cpp
	Texture.cpp
	Timer.cpp
)

set(arkilleved_LIBS
	arkilloid_io
	glftfont
	${OPENGL_LIBRARIES}
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
	${SDLTTF_LIBRARY}
	${FREETYPE_LIBRARY}
)

include_directories(
	${LIBIO_INCLUDE_DIR}
)
add_executable(arkilleved ${arkilleved_SRCS})
target_link_libraries(arkilleved ${arkilleved_LIBS})
#install(TARGETS arkilleved RUNTIME DESTINATION ${BINDIR})
install(TARGETS arkilleved RUNTIME DESTINATION bin)
