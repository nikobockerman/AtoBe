include(../ut_common.pri)

TARGET = ut_gmocktemplate
SOURCES += ut_gmocktemplate.cpp \
    $$SRCDIR/gmocktemplate.cpp
HEADERS += \
    $$SRCDIR/gmocktemplate.h

include(../gmock.pri)
include(../check.pri)
