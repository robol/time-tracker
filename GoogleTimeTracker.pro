#-------------------------------------------------
#
# Project created by QtCreator 2012-10-08T15:39:37
#
#-------------------------------------------------


# Hint: To compile this project against a local version of
# libgcal, say, a compiled version put in a folder named "dependencies",
# simply use the following statements in this project file.
#
# LIBS += -L"$$_PRO_FILE_PWD_/dependencies/libgcal-0.9.6/.libs" -lgcal
# INCLUDEPATH += "$$_PRO_FILE_PWD_/dependencies/libgcal-0.9.6/inc"#

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoogleTimeTracker
TEMPLATE = app

LIBS += -lgcal
INCLUDEPATH += /usr/include/libgcal

SOURCES += main.cpp\
        mainwindow.cpp \
    calendarclient.cpp \
    eventlistmodel.cpp

HEADERS  += mainwindow.h \
    calendarclient.h \
    eventlistmodel.h

FORMS    += mainwindow.ui
