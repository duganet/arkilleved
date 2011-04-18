cmake_minimum_required(VERSION 2.6)
project(arkilleved)

IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0011 NEW)
ENDIF(COMMAND CMAKE_POLICY)


find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(Freetype REQUIRED)

set(BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(DATADIR ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME})

set(ARKILLEVED_INCLUDE_DIR src)
set(GLFTFONT_INCLUDE_DIR extern/glftfont)
set(LIBIO_INCLUDE_DIR src/io)

add_definitions(-DDATADIR="${DATADIR}")
add_definitions(-DPACKAGE="${PROJECT_NAME}")
if(DEBUG)
	add_definitions(-DDEBUG)
	set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(
	${OPENGL_INCLUDE_DIR}
	${SDL_INCLUDE_DIR}
	${SDLIMAGE_INCLUDE_DIR}
	${SDLTTF_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIRS}
	${GLFTFONT_INCLUDE_DIR}
	${ARKILLEVED_INCLUDE_DIR}
	${LIBIO_INCLUDE_DIR}
)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(data)
