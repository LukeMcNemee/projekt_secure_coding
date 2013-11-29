TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    coordinate.cpp \
    parser.cpp \
    exceptions.cpp

HEADERS += \
    coordinate.h \
    parser.h \
    exceptions.h

