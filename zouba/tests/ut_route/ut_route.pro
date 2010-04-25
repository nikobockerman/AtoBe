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
  maemo5 \

INCLUDEPATH += \
  $$ZOUBASRC \

DEPENDPATH += $INCLUDEPATH

TEMPLATE = app

LIBS += \
   /usr/lib/libQtLocation.so \

SOURCES  = \
  ut_route.cpp \
  $$ZOUBASRC/route_p.cpp \
  $$ZOUBASRC/location.cpp \
  $$ZOUBASRC/location_p.cpp \

HEADERS += \
  ut_route.h \
  $$ZOUBASRC/route_p.h \
  $$ZOUBASRC/location.h \
  $$ZOUBASRC/location_p.h \

QMAKE_EXTRA_TARGETS += check
check.depends = $$TARGET
check.commands = ./$$TARGET
