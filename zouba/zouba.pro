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

SOURCES += \
    main.cpp \
    route.cpp \
    route_p.cpp \
    uicontroller.cpp \
    location.cpp \
    location_p.cpp \
    locations.cpp \
    gpscontroller.cpp \
    ui.cpp \
    messagetable.cpp \
    messagehandler.cpp \

HEADERS += \
    route.h \
    route_p.h \
    uicontroller.h \
    location.h \
    location_p.h \
    locations.h \
    ytv.h \
    gpscontroller.h \
    ui.h \
    messagetable.h \
    messagehandler.h \

