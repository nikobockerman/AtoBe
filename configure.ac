AC_PREREQ(2.61)
AC_INIT([hildon-timeout-desktop-widget-example], [0.1])
AC_CONFIG_SRCDIR([lib-timeout-home-widget.c])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADER([config.h])

AC_PROG_CC
AC_HEADER_STDC
AC_PROG_INSTALL
AM_PROG_LIBTOOL

PKG_CHECK_MODULES(EXAMPLE, hildon-1 libhildondesktop-1 gtk+-2.0 liblocation)
AC_SUBST(EXAMPLE_CFLAGS)
AC_SUBST(EXAMPLE_LIBS)

# Discover where to install the .desktop file:
HILDON_HOME_DESKTOP_DIR=`pkg-config libhildondesktop-1 --variable=hildonhomedesktopentrydir`
AC_SUBST(HILDON_HOME_DESKTOP_DIR)

# Discover where to install the status widget's lib file:
HILDON_DESKTOP_LIB_DIR=`pkg-config libhildondesktop-1 --variable=hildondesktoplibdir`
AC_SUBST(HILDON_DESKTOP_LIB_DIR) 


AC_OUTPUT(Makefile)
AC_OUTPUT(timeout-home-widget.desktop)
