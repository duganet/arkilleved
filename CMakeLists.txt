CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT (arkilloid-leveledit)

SET (HEADERS
	src/Brick.h
	src/Button.h
	src/CMakeCache.txt
	src/Constants.h
	src/Frame.h
	src/SDLUtils.h
	src/Timer.h
	)

SET (SOURCES
	src/main.cpp
	src/Brick.cpp
	src/Button.cpp
	src/Frame.cpp
	src/SDLUtils.cpp
	src/Timer.cpp
	)

SET (BINARY_NAME
	arkilloid-leveledit
	)

SET (RES_IMAGES
	data/images/bg.bmp
	data/images/brick.png
	data/images/button_open.png
	data/images/brick_beton.png
	data/images/brick_strong.png
	data/images/button_save.png
	)

SET (RELEASE_DIR
	arkilloid-leveledit
	)

ADD_EXECUTABLE (${BINARY_NAME} ${SOURCES})

TARGET_LINK_LIBRARIES (${BINARY_NAME}
	SDL
	SDL_image
	SDL_mixer
	SDL_ttf
	)

INSTALL (TARGETS ${BINARY_NAME} DESTINATION "bin")
INSTALL (FILES "${RES_IMAGES}" DESTINATION "share/images")
