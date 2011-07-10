# We invent desktoplib_LTLIBRARIES instead of the normal lib_LTLIBRARIES,
# so we can specify the non-standard installation directory.
desktoplib_LTLIBRARIES =  lib-timeout-home-widget.la
desktoplibdir = $(HILDON_DESKTOP_LIB_DIR)

lib_timeout_home_widget_la_SOURCES = lib-timeout-home-widget.c lib-timeout-home-widget.h location-provider.c location-provider.h coordinate-system.c coordinate-system.h
lib_timeout_home_widget_la_LIBADD = $(EXAMPLE_LIBS)

AM_CFLAGS = -Wall $(EXAMPLE_CFLAGS)

# .desktop file
desktopdir = $(HILDON_HOME_DESKTOP_DIR)
desktop_DATA = timeout-home-widget.desktop

DISTCLEANFILES = $(desktop_DATA)
