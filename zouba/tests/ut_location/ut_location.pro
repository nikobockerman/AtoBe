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

DEPENDPATH += $$INCLUDEPATH

LIBS += \
   /usr/lib/libQtLocation.so \

TEMPLATE = app

SOURCES  = \
  ut_location.cpp \
  $$ZOUBASRC/location.cpp \
  $$ZOUBASRC/location_p.cpp \

HEADERS += \
  ut_location.h \
  $$ZOUBASRC/location.h \
  $$ZOUBASRC/location_p.h \

QMAKE_EXTRA_TARGETS += check
check.depends = $$TARGET
check.commands = ./$$TARGET
