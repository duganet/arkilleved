##AC_INIT([src/main.cpp])
AC_INIT([Arkilloid Level Editor],[0.0.1],[http://arkilloid.duganet.ru/],[arkilloid-leveledit])
AM_INIT_AUTOMAKE([0.0.1])
AC_PROG_CXX

PKG_NAME="arkilloid-leveledit"
AC_SUBST([PKG_NAME])

AC_CHECK_LIB([SDL], [SDL_Init])
AC_CHECK_LIB([SDL_image], [IMG_LoadPNG_RW])
AC_CHECK_LIB([SDL_ttf], [TTF_Init])

AC_OUTPUT([Makefile src/Makefile data/Makefile data/images/Makefile])
