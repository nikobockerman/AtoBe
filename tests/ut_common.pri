QT -= gui
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
OBJECTS_DIR = .obj
MOC_DIR = .moc
SRCDIR = ../../src
MOCKSDIR = ../mocks
INCLUDEPATH += ../util \
    $$SRCDIR \
    $$MOCKSDIR
