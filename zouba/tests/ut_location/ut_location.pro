CONFIG += \
  qt \
  debug \

QT += \
  testlib \

INCLUDEPATH += \
  ../.. \

TEMPLATE = app

SOURCES  = \
  ut_location.cpp \
  ../../location_p.cpp \

HEADERS += \
  ut_location.h \
  ../../location_p.h \

