include( ../tests.pri )
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
  $$ZOUBASRC \

DEPENDPATH += $INCLUDEPATH

TEMPLATE = app

LIBS += \
   /usr/lib/libQtLocation.so \

SOURCES  = \
  ut_gpscontroller.cpp \
  $$ZOUBASRC/gpscontroller.cpp \
  $$ZOUBASRC/gpscontroller_p.cpp \
  $$ZOUBASRC/locations.cpp \
  $$ZOUBASRC/location.cpp \
  $$ZOUBASRC/location_p.cpp \

HEADERS += \
  ut_gpscontroller.h \
  $$ZOUBASRC/gpscontroller.h \
  $$ZOUBASRC/gpscontroller_p.h \
  $$ZOUBASRC/locations.h \
  $$ZOUBASRC/location.h \
  $$ZOUBASRC/location_p.h \

QMAKE_EXTRA_TARGETS += check
check.depends = $$TARGET
check.commands = ./$$TARGET
