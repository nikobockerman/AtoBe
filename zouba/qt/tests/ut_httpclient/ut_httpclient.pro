CONFIG += \
  qt \
  debug \

QT += \
  testlib \

INCLUDEPATH += \
  ../.. \

TEMPLATE = app

SOURCES  = \
  ut_httpclient.cpp \
  ../../httpclient_p.cpp \

HEADERS += \
  ut_httpclient.h \
  ../../httpclient_p.h \

