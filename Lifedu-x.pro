#-------------------------------------------------
#
# Project created by QtCreator 2021-05-22T16:36:20
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lifedu-x
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    home.cpp \
    login.cpp \
    about.cpp \
    kurs.cpp \
    dars.cpp \
    admin.cpp

HEADERS  += mainwindow.h \
    home.h \
    login.h \
    db.h \
    about.h \
    kurs.h \
    dars.h \
    admin.h

FORMS    += mainwindow.ui \
    home.ui \
    login.ui \
    about.ui \
    kurs.ui \
    dars.ui \
    admin.ui

DISTFILES += \
    ../../Desktop/l.png

RESOURCES += \
    assets/files.qrc
