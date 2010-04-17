include(../ut_common.pri)

TARGET = ut_kkjgridcoordinate
CONFIG += \
    mobility
MOBILITY = location
SOURCES += ut_kkjgridcoordinate.cpp \
    $$SRCDIR/kkjgridcoordinate.cpp
HEADERS += \
    $$SRCDIR/kkjgridcoordinate.h

include(../gmock.pri)
include(../check.pri)
