CONFIG += \
  qt \
  debug \

QT += \
  testlib \
  network \

INCLUDEPATH += \
  ../.. \

TEMPLATE = app

SOURCES  = \
  ut_route.cpp \
  ../../route_p.cpp \
  ../../location.cpp \
  ../../location_p.cpp \

HEADERS += \
  ut_route.h \
  ../../route_p.h \
  ../../location.h \
  ../../location_p.h \

