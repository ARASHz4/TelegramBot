#-------------------------------------------------
#
# Project created by ARASHz4 2016-10-29T23:14:29
#
#-------------------------------------------------

QT += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TelegramBot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sendmessage.cpp \
    bot.cpp \
    getupdate.cpp \
    slsettings.cpp

HEADERS  += mainwindow.h \
    sendmessage.h \
    bot.h \
    getupdate.h \
    slsettings.h

FORMS    += mainwindow.ui \
    sendmessage.ui \
    getupdate.ui
