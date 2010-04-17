include(../ut_common.pri)

TARGET = ut_kkjgridcoordinate
QT += testlib
QT -= gui
CONFIG += console \
    mobility
CONFIG -= app_bundle
MOBILITY = location
TEMPLATE = app
OBJECTS_DIR = .obj
MOC_DIR = .moc
SOURCES += ut_kkjgridcoordinate.cpp \
    $$SRCDIR/kkjgridcoordinate.cpp
HEADERS += \
    $$SRCDIR/kkjgridcoordinate.h

include(../gmock.pri)
include(../check.pri)
