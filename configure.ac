##AC_INIT([src/main.cpp])
AC_INIT([Arkilloid Level Editor],[0.0.1],[http://arkilloid.duganet.ru/],[arkilloid-leveledit])
AM_INIT_AUTOMAKE([arkilloid-leveledit],[0.0.1])
AC_PROG_CXX
AC_PROG_MAKE_SET
##AM_CONFIG_HEADER([src/config.h])

AC_CHECK_LIB([SDL], [SDL_Init])
AC_CHECK_LIB([SDL_image], [IMG_LoadPNG_RW])
AC_CHECK_LIB([SDL_ttf], [TTF_Init])
AC_CHECK_LIB([freetype], [FT_Init_FreeType])

dnl Check for OpenGL (Original or Mesa) (or osX-framework)
AC_CHECK_HEADERS(GL/gl.h GL/glu.h,,
        [AC_CHECK_HEADERS(OpenGL/gl.h OpenGL/glu.h,,
          [echo "OpenGL is mandatory";exit 1])]
)

if test `uname -s` != Darwin;
then
AC_CHECK_LIB(GL, glInitNames,,
    AC_CHECK_LIB(MesaGL,glInitNames,,
           echo "OpenGL is mandatory";exit 1)
)

dnl Check for GLU (Original or Mesa)
AC_CHECK_LIB(GLU, gluLookAt, ,
    AC_CHECK_LIB(MesaGLU,gluLookAt,,
    echo "incomplete OpenGL (no GLU)";exit 1)
)
fi 

##PDATADIR="${PREFIX}/share/${PACKAGE}"
##AC_SUBST(PDATADIR)
##AC_DEFINE_UNQUOTED([PDATADIR], [${PDATADIR}], [Package data dir])

AC_OUTPUT([Makefile src/Makefile data/Makefile data/fonts/Makefile data/images/Makefile])
