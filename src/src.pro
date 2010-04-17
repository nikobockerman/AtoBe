TEMPLATE = lib
TARGET = ptascommon
OBJECTS_DIR = .obj
MOC_DIR = .moc

INSTALL_HEADERS = \
    coordinatesystemtransformer.h \
    kkjgridcoordinate.h \

PRIVATE_HEADERS = \
    kkjgridcoordinate_p.h
HEADERS += \
    $$INSTALL_HEADERS \
    $$PRIVATE_HEADERS
SOURCES += \
    coordinatesystemtransformer.cpp \
    kkjgridcoordinate.cpp
