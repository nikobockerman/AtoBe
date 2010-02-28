CONFIG += qt \
    debug
QT += network
TEMPLATE = app
FORMS = zouba.ui
SOURCES = main.cpp \
    route.cpp \
    route_p.cpp \
    uicontroller.cpp \
    location.cpp \
    location_p.cpp
HEADERS += route.h \
    route_p.h \
    uicontroller.h \
    location.h \
    location_p.h \
    ytv.h
