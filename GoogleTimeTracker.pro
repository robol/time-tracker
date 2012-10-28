#-------------------------------------------------
#
# Project created by QtCreator 2012-10-08T15:39:37
#
#-------------------------------------------------


# Hint: To compile this project against a local version of
# libgcal, say, a compiled version put in a folder named "dependencies",
# simply use the following statements in this project file.
#
# LIBS += -L"$$_PRO_FILE_PWD_/dependencies/libgcal-x.y.z/.libs" -lgcal
# INCLUDEPATH += "$$_PRO_FILE_PWD_/dependencies/libgcal-x.y.z/inc"

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoogleTimeTracker
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += libgdata gobject-2.0

SOURCES += time-tracker/main.cpp\
        time-tracker/mainwindow.cpp \
    time-tracker/calendarclient.cpp \
    time-tracker/eventlistmodel.cpp \
    time-tracker/calendarevent.cpp \
    time-tracker/calendarlistmodel.cpp

HEADERS  += time-tracker/mainwindow.h \
    time-tracker/calendarclient.h \
    time-tracker/eventlistmodel.h \
    time-tracker/calendarevent.h \
    time-tracker/calendarlistmodel.h

FORMS    += time-tracker/mainwindow.ui
