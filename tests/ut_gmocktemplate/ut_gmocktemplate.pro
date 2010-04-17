include(../ut_common.pri)

TARGET = ut_gmocktemplate
QT += testlib
QT -= gui
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
OBJECTS_DIR = .obj
MOC_DIR = .moc
SOURCES += ut_gmocktemplate.cpp
HEADERS +=

include(../gmock.pri)
include(../check.pri)
