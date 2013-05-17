#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T22:19:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtkamal
TEMPLATE = app

#IF DEFINED (WITH_TRIANG)
DEFINES += MIN_TRIANG_ANGLE=10
INCLUDEPATH += /usr/local/include
LIBS += -L /usr/local/lib -lgsl -lgslcblas
#ENDIF

SOURCES += main.cpp\
    src/base/Point.cpp \
    src/base/Straight.cpp \
    src/Geo/Coordinate.cpp \
    src/Geo/Beam.cpp \
    qtkamal.cpp \
    gbcoordinates.cpp \
    utils/qtpointitem.cpp \
    utils/kml.cpp \
    utils/qxmlputget.cpp \
    utils/networkicon.cpp \
    utils/stylefold.cpp \
    dialogs/beamdialog.cpp \
    dialogs/circledialog.cpp \
    dialogs/aboutdialog.cpp \
    dialogs/pointdialog.cpp \
    utils/qtbeamitem.cpp \
    utils/qtcircleitem.cpp \
    kamaltree.cpp \
#IF DEFINED(WITH_TRIANG)
    src/Calc/LinearSolver.cpp
#ENDIF


HEADERS  += \
    src/base/Straight.h \
    src/base/Point.h \
    src/Geo/Coordinate.h \
    src/Geo/Beam.h \
    qtkamal.h \
    utils/qtpointitem.h \
    gbcoordinates.h \
    utils/kml.h \
    utils/qxmlputget.h \
    utils/networkicon.h \
    utils/stylefold.h \
    dialogs/beamdialog.h \
    dialogs/circledialog.h \
    dialogs/aboutdialog.h \
    dialogs/pointdialog.h \
    utils/qtbeamitem.h \
    utils/qtcircleitem.h \
    kamaltree.h \
#IF DEFINED(WITH_TRIANG)
    src/Calc/LinearSolver.h
#ENDIF

FORMS    += \
    qtkamal.ui \
    gbcoordinates.ui \
    dialogs/beamdialog.ui \
    dialogs/circledialog.ui \
    dialogs/aboutdialog.ui \
    dialogs/pointdialog.ui

RESOURCES += \
    res.qrc

QT += xml \
    network
