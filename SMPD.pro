#-------------------------------------------------
#
# Project created by QtCreator 2017-02-14T15:53:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMPD
TEMPLATE = app

INCLUDEPATH += C:\boost_1_65_1\boost_1_65_1
LIBS += "-LC:\boost_1_65_1\boost_1_65_1\libs"
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    object.cpp \
    combination.cpp \
    ficherelement.cpp \
    object_model.cpp \
    fischer.cpp \
    matrixutil.cpp

HEADERS  += mainwindow.h \
    database.h \
    object.h \
    combination.h \
    ficherelement.h \
    object_model.h \
    fischer.h \
    matrixutil.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
