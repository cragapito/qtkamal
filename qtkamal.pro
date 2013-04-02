#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T22:19:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kamal
TEMPLATE = app


SOURCES += main.cpp\
    point.cpp \
    src/base/Point.cpp \
    src/base/Straight.cpp \
    src/Geo/Coordinate.cpp \
    src/Geo/Beam.cpp \
    gbcoordinates.cpp \
    qtkamal.cpp

HEADERS  += \
    point.h \
    src/base/Straight.h \
    src/base/Point.h \
    src/Geo/Coordinate.h \
    src/Geo/Beam.h \
    gbcoordinates.h \
    qtkamal.h

FORMS    += \
    point.ui \
    gbcoordinates.ui \
    qtkamal.ui

RESOURCES += \
    res.qrc
