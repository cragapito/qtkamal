
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
    kamaltree.cpp

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
    kamaltree.h

FORMS    += \
    qtkamal.ui \
    gbcoordinates.ui \
    dialogs/beamdialog.ui \
    dialogs/circledialog.ui \
    dialogs/aboutdialog.ui \
    dialogs/pointdialog.ui

RESOURCES += \
    res.qrc

!contains(DEFINES, WITHOUT_TRIANG) {
    INCLUDEPATH += /usr/local/include
    LIBS += -L /usr/local/lib -lgsl -lgslcblas
    DEFINES+=WITH_TRIANG
    HEADERS += src/Calc/LinearSolver.h
    SOURCES += src/Calc/LinearSolver.cpp
}

contains(DEFINES, win32) {
    CONFIG += static
    CONFIG += staticlib
    CONFIG += create_prl
    CONFIG += link_prl
    QMAKE_CFLAGS_RELEASE = -Os -momit-leaf-frame-pointer
    DEFINES += QT_STATIC_BUILD
    LIBS = -static
    LFLAGS = -static -static-libgcc
    LIBS += -L /usr/local/mingw32/lib/gsl/lib\
    -Xlinker -Bstatic -Wl /usr/local/mingw32/lib/gsl/lib/libgsl.a\
    -Xlinker -Bstatic -Wl /usr/local/mingw32/lib/gsl/lib/libgslcblas.a\
    -Xlinker -Bstatic -Wl /usr/local/qt4win32/lib/libQtCore4.a\
    -Xlinker -Bstatic -Wl /usr/local/qt4win32/lib/libQtGui4.a\
    -Xlinker -Bstatic -Wl /usr/local/qt4win32/lib/libQtNetwork4.a\
    -Xlinker -Bstatic -Wl /usr/local/qt4win32/lib/libQtXml4.a
    RC_FILE += qtkamal.rc
    QMAKE_LFLAGS += -static -static-libgcc
}

QT += xml \
    network

OTHER_FILES +=
