#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T22:19:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtkamal
TEMPLATE = app


SOURCES += main.cpp\
    src/base/Point.cpp \
    src/base/Straight.cpp \
    src/Geo/Coordinate.cpp \
    src/Geo/Beam.cpp \
    qtkamal.cpp \
    utils/qtpointitem.cpp \
    widgets/gbcoordinates.cpp \
    dialogs/point.cpp

HEADERS  += \
    src/base/Straight.h \
    src/base/Point.h \
    src/Geo/Coordinate.h \
    src/Geo/Beam.h \
    qtkamal.h \
    utils/qtpointitem.h \
    widgets/gbcoordinates.h \
    dialog/point.h \
    dialogs/point.h

FORMS    += \
    qtkamal.ui \
    widgets/gbcoordinates.ui \
    dialogs/point.ui

RESOURCES += \
    res.qrc
