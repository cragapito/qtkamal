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
    dialogs/point.cpp \
    gbcoordinates.cpp \
    utils/qtpointitem.cpp \
    utils/kml.cpp \
    utils/qxmlputget.cpp \
    utils/networkicon.cpp \
    utils/stylefold.cpp \
    dialogs/beamdialog.cpp \
    dialogs/circledialog.cpp \
    dialogs/aboutdialog.cpp \
    utils/qtbeamitem.cpp \
    utils/qtcircleitem.cpp

HEADERS  += \
    src/base/Straight.h \
    src/base/Point.h \
    src/Geo/Coordinate.h \
    src/Geo/Beam.h \
    qtkamal.h \
    utils/qtpointitem.h \
    dialog/point.h \
    dialogs/point.h \
    gbcoordinates.h \
    utils/kml.h \
    utils/qxmlputget.h \
    utils/networkicon.h \
    utils/stylefold.h \
    dialogs/beamdialog.h \
    dialogs/circledialog.h \
    dialogs/aboutdialog.h \
    utils/qtbeamitem.h \
    utils/qtcircleitem.h

FORMS    += \
    qtkamal.ui \
    dialogs/point.ui \
    gbcoordinates.ui \
    dialogs/beamdialog.ui \
    dialogs/circledialog.ui \
    dialogs/aboutdialog.ui

RESOURCES += \
    res.qrc

QT += xml \
    network
