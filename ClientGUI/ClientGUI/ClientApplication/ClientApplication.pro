#-------------------------------------------------
#
# Project created by QtCreator 2019-06-12T08:18:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientApplication
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        actionswindow.cpp \
        bitconverter.cpp \
        connector.cpp \
        genericlinkedlist.cpp \
        genericnode.cpp \
        imagepackage.cpp \
        imgtable.cpp \
        keyvalue.cpp \
        main.cpp \
        mainwindow.cpp \
        metadb.cpp \
        netpackage.cpp \
        registrationscreen.cpp \
        selectionwindow.cpp \
        sqlmanagementwindow.cpp

HEADERS += \
        actionswindow.h \
        bitconverter.h \
        connector.h \
        genericlinkedlist.h \
        genericnode.h \
        imagepackage.h \
        imgtable.h \
        keyvalue.h \
        mainwindow.h \
        metadb.h \
        netpackage.h \
        registrationscreen.h \
        selectionwindow.h \
        sqlmanagementwindow.h

FORMS += \
        actionswindow.ui \
        mainwindow.ui \
        registrationscreen.ui \
        selectionwindow.ui \
        sqlmanagementwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
