TEMPLATE = lib
TARGET = ptascommon

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
