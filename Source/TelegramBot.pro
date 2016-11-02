#-------------------------------------------------
#
# Project created by ARASHz4 2016-10-29T23:14:29
#
#-------------------------------------------------

QT += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Telegram Bot"
TEMPLATE = app

CONFIG += c++11

win32
{
    RC_FILE = Windows/TBWinRes.rc
    CONFIG -= embed_manifest_exe
}

mac
{
    QMAKE_INFO_PLIST = Mac/TBInfo.plist
    ICON = Mac/TBIcon.icns
}

SOURCES += main.cpp\
    sendmessage.cpp \
    bot.cpp \
    slsettings.cpp \
    getme.cpp \
    options.cpp \
    botwindow.cpp \
    about.cpp

HEADERS  += \
    sendmessage.h \
    bot.h \
    slsettings.h \
    getme.h \
    options.h \
    botwindow.h \
    about.h

FORMS    += \
    sendmessage.ui \
    getme.ui \
    options.ui \
    botwindow.ui \
    about.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    Linux/TelegramBot.desktop \
    Linux/TBIcon.png \
    Mac/TBInfo.plist \
    Mac/TBIcon.icns \
    Windows/TBIcon.ico \
    Windows/TBWinRes.rc \
    Windows/TBWinDetails.h \
    "Windows/Telegram Bot.exe.manifest"
