include(../ut_common.pri)

TARGET = ut_kkj
QT += testlib
QT -= gui
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
OBJECTS_DIR = .obj
MOC_DIR = .moc
SOURCES += ut_kkj.cpp \
    $$SRCDIR/kkj.cpp
HEADERS += \
    $$SRCDIR/kkj.h

include(../gmock.pri)
include(../check.pri)
