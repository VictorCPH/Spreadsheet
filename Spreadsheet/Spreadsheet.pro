#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T22:46:30
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spreadsheet
TEMPLATE = app

qtHaveModule(printsupport): QT += printsupport


SOURCES += main.cpp\
        mainwindow.cpp \
    gotocelldialog.cpp \
    finddialog.cpp \
    sortdialog.cpp \
    spreadsheet.cpp \
    cell.cpp \
    uploaddialog.cpp

HEADERS  += mainwindow.h \
    finddialog.h \
    sortdialog.h \
    spreadsheet.h \
    gotocelldialog.h \
    ui_gotocelldialog.h \
    ui_sortdialog.h \
    cell.h \
    uploaddialog.h

FORMS    += \
    uploaddialog.ui

RESOURCES += \
    image.qrc

DISTFILES += \
    qtdemo.rc
RC_FILE = \
    qtdemo.rc
