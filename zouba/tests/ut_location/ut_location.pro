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

DEPENDPATH += $$INCLUDEPATH

LIBS += \
   /usr/lib/libQtLocation.so \

TEMPLATE = app

SOURCES  = \
  ut_location.cpp \
  ../../location.cpp \
  ../../location_p.cpp \

HEADERS += \
  ut_location.h \
  ../../location.h \
  ../../location_p.h \

