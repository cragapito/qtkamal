######################################################################
# Automatically generated by qmake (2.01a) ter ago 30 21:02:09 2016
######################################################################

QT += widgets
QT += webkit
QT += xml
QT += core

TEMPLATE = app
TARGET = qtkamal
DEPENDPATH += . dialogs utils src/base src/Calc src/Geo
INCLUDEPATH += . src/Geo src/base utils src/Calc dialogs

# Input
HEADERS += gbcoordinates.h \
           kamaltree.h \
           qtkamal.h \
           dialogs/aboutdialog.h \
           dialogs/beamdialog.h \
           dialogs/circledialog.h \
           dialogs/pointdialog.h \
           utils/config.h \
           utils/kml.h \
           utils/networkicon.h \
           utils/qtbeamitem.h \
           utils/qtcircleitem.h \
           utils/qtpointitem.h \
           utils/qxmlputget.h \
           utils/stylefold.h \
           src/base/Point.h \
           src/base/Straight.h \
           src/Calc/LinearSolver.h \
           src/Geo/Beam.h \
           src/Geo/Coordinate.h
FORMS += gbcoordinates.ui \
         qtkamal.ui \
         dialogs/aboutdialog.ui \
         dialogs/beamdialog.ui \
         dialogs/circledialog.ui \
         dialogs/pointdialog.ui
SOURCES += gbcoordinates.cpp \
           kamaltree.cpp \
           main.cpp \
           qtkamal.cpp \
           dialogs/aboutdialog.cpp \
           dialogs/beamdialog.cpp \
           dialogs/circledialog.cpp \
           dialogs/pointdialog.cpp \
           utils/config.cpp \
           utils/kml.cpp \
           utils/networkicon.cpp \
           utils/qtbeamitem.cpp \
           utils/qtcircleitem.cpp \
           utils/qtpointitem.cpp \
           utils/qxmlputget.cpp \
           utils/stylefold.cpp \
           src/base/Point.cpp \
           src/base/Straight.cpp \
           src/Calc/LinearSolver.cpp \
           src/Geo/Beam.cpp \
           src/Geo/Coordinate.cpp
RESOURCES += res.qrc

INCLUDEPATH += /usr/local/include
unix|win32: LIBS += -lgsl -lgslcblas
