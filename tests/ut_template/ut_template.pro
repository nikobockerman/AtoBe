include(../ut_common.pri)

TARGET = ut_template
QT += testlib
SOURCES += ut_template.cpp \
    $$SRCDIR/template.cpp
HEADERS += ut_template.h \
    $$SRCDIR/template.h

include(../check.pri)
