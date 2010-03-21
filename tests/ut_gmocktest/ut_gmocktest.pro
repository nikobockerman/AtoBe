TARGET = ut_gmocktest
QT += testlib
QT -= gui
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
OBJECTS_DIR = .obj
MOC_DIR = .moc
SOURCES += ut_gmocktest.cpp \
    painter.cpp
HEADERS += \
    turtle.h \
    mock_turtle.h \
    painter.h

include(../gmock.pri)
