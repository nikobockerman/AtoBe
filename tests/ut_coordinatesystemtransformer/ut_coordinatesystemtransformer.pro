include(../ut_common.pri)

TARGET = ut_coordinatesystemtransformer
CONFIG += \
    mobility
MOBILITY = location
SOURCES += \
    ut_coordinatesystemtransformer.cpp \
    $$SRCDIR/coordinatesystemtransformer.cpp \
    $$SRCDIR/kkjgridcoordinate.cpp
HEADERS += \
    $$SRCDIR/coordinatesystemtransformer.h \
    $$SRCDIR/kkjgridcoordinate.h

include(../gmock.pri)
include(../check.pri)
