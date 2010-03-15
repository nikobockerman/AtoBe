CONFIG += \
    qt \
    debug \
    mobility \

MOBILITY = \
   location \
   bearer \

LIBS += \
   /usr/lib/libQtLocation.so \

DEFINES+= Q_WS_MAEMO_5

QT += \
  network \

TEMPLATE = app

FORMS = zouba.ui

SOURCES += \
    main.cpp \
    route.cpp \
    route_p.cpp \
    uicontroller.cpp \
    location.cpp \
    location_p.cpp \
    gpscontroller.cpp \

HEADERS += \
    route.h \
    route_p.h \
    uicontroller.h \
    location.h \
    location_p.h \
    ytv.h \
    gpscontroller.h \

