CONFIG += \
  qt \
  debug \

QT += \
  testlib \

INCLUDEPATH += \
  ../.. \

TEMPLATE = app

SOURCES  = \
  ut_route.cpp \
  ../../route_p.cpp \

HEADERS += \
  ut_route.h \
  ../../route_p.h \

