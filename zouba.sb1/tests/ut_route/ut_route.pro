CONFIG += \
  qt \
  debug \
  mobility \

MOBILITY = \
   location \
   bearer \

QT += \
  testlib \
  network \

INCLUDEPATH += \
  ../.. \

DEPENDPATH += $INCLUDEPATH

TEMPLATE = app

LIBS += \
   /usr/lib/libQtLocation.so \

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

