CONFIG += \
  qt \

QT += \
  network \

TEMPLATE = app
FORMS    = zouba.ui

SOURCES  = \
  main.cpp \
  httpclient.cpp \
  httpclient_p.cpp \

HEADERS += \
  httpclient.h \
  httpclient_p.h \

