TARGET      = zouba
SOURCES += \
    src/main.cpp \
    src/route.cpp \
    src/route_p.cpp \
    src/uicontroller.cpp \
    src/ui.cpp \
    src/locationbutton.cpp \
    src/addressdialog.cpp \
    src/logic/ytv.cpp \
    src/logic/routepointgenerator.cpp \
    src/logic/routepoint.cpp \
    src/logic/routenew.cpp \
    src/logic/routeleggenerator.cpp \
    src/logic/routeleg.cpp \
    src/logic/routefinder.cpp \
    src/logic/locations.cpp \
    src/logic/locationfinder.cpp \
    src/logic/location.cpp \
    src/gui/routelegwidget.cpp \
    src/gui/routeresultwidget.cpp \
    src/gui/searchdisplay.cpp \
    src/gui/routeoneitemwidget.cpp \
    src/gui/locationsdisplaywindow.cpp

HEADERS += \
    src/route.h \
    src/route_p.h \
    src/uicontroller.h \
    src/ui.h \
    src/locationbutton.h \
    src/addressdialog.h \
    src/logic/ytv.h \
    src/logic/routepointgenerator.h \
    src/logic/routepoint.h \
    src/logic/routenew.h \
    src/logic/routeleggenerator.h \
    src/logic/routeleg.h \
    src/logic/routefinder.h \
    src/logic/locations.h \
    src/logic/locationfinder.h \
    src/logic/location.h \
    src/gui/routelegwidget.h \
    src/gui/routeresultwidget.h \
    src/gui/searchdisplay.h \
    src/gui/routeoneitemwidget.h \
    src/gui/locationsdisplaywindow.h

FORMS       += \
    src/gui/locationsdisplaywindow.ui \
    src/gui/routelegwidget.ui \
    src/gui/routeresultwidget.ui \
    src/gui/searchdisplay.ui \
    src/gui/routeoneitemwidget.ui

LEXSOURCES  += #LEXS#
YACCSOURCES += #YACCS#

INCLUDEPATH += include
DEPENDSPATH += INCLUDEPATH
#QMAKE_LIBDIR_QT = qt4-maemo5/lib
#QMAKE_INCDIR_QT = qt4-maemo5/include
LIBS        += -Llib
#DEFINES     += Q_WS_MAEMO_5

# All generated files goes same directory
OBJECTS_DIR = build
MOC_DIR     = build
UI_DIR      = build

DESTDIR     = build
TEMPLATE    = app
DEPENDPATH  +=
VPATH       += src uis
CONFIG      -=
CONFIG      += debug qt
#MOBILITY    += location bearer
QT=core gui network

linux-g++-maemo5 {
SOURCES += \
    gpscontroller.cpp \
    src/gui/favoriteselectiondialog.cpp
HEADERS += \
    gpscontroller.h \
    src/gui/favoriteselectiondialog.h
FORMS += \
    src/gui/favoriteselectiondialog.ui

QT += maemo5
LIBS += -lQtBearer -lQtLocation
MOBILITY += location bearer
CONFIG += mobility
}

INSTALLS    += target
target.path  = /usr/bin/

INSTALLS    += desktop
desktop.path  = /usr/share/applications/hildon
desktop.files  = data/zouba.desktop

INSTALLS    += service
service.path  = /usr/share/dbus-1/services
service.files  = data/zouba.service

INSTALLS    += icon64
icon64.path  = /usr/share/icons/hicolor/64x64/apps
icon64.files  = data/64x64/zouba.png

#
# Targets for debian source and binary package creation
#
debian-src.commands = dpkg-buildpackage -S -r -us -uc -d
debian-bin.commands = dpkg-buildpackage -b -r -uc -d
debian-all.depends = debian-src debian-bin

#
# Clean all but Makefile
#
compiler_clean.commands = -$(DEL_FILE) $(TARGET)

QMAKE_EXTRA_TARGETS += debian-all debian-src debian-bin compiler_clean

OTHER_FILES += \
    data/TODO.txt

RESOURCES += \
    ReittiopasImages.qrc
