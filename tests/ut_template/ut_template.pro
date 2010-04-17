include(../ut_common.pri)

TARGET = ut_template
QT += testlib
QT -= gui
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
OBJECTS_DIR = .obj
MOC_DIR = .moc
SOURCES += ut_template.cpp
HEADERS += ut_template.h

include(../check.pri)
