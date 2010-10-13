TARGET      = zouba
SOURCES += \
    main.cpp \
    route.cpp \
    route_p.cpp \
    uicontroller.cpp \
    location.cpp \
    locations.cpp \
    ui.cpp \
    locationbutton.cpp \
    addressdialog.cpp \
    ytv.cpp \
    locationsdisplaywindow.cpp

HEADERS += \
    route.h \
    route_p.h \
    uicontroller.h \
    location.h \
    locations.h \
    ytv.h \
    ui.h \
    locationbutton.h \
    addressdialog.h \
    locationsdisplaywindow.h

FORMS       += \
    locationsdisplaywindow.ui
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
SOURCES += gpscontroller.cpp
HEADERS += gpscontroller.h
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
