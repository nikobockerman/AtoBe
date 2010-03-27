TEMPLATE = lib
TARGET = ptascommon

INSTALL_HEADERS = \
    kkj.h
PRIVATE_HEADERS = \
    kkj_p.h
HEADERS += \
    $$INSTALL_HEADERS \
    $$PRIVATE_HEADERS
SOURCES += \
    kkj.cpp
