#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T21:26:03
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TalkClient
TEMPLATE = app

SOURCES += main.cpp\
    Grouplist.cpp \
        LoginDialog.cpp \
    MainWindowUI.cpp \
    MainWindowData.cpp \
    FriendList.cpp \
    Buddy.cpp \
    Group.cpp \
    RegisterWidget.cpp \
    TalkDialogUI.cpp \
    TalkDialogData.cpp \
    Socket.cpp \
    Message.cpp \
    gloabal.cpp \
    ui/addgroup.cpp \
    ui/addui.cpp

HEADERS  += LoginDialog.h \
    Grouplist.h \
    MainWindow.h \
    FriendList.h \
    Buddy.h \
    Group.h \
    RegisterWidget.h \
    TalkDialog.h \
    Socket.h \
    Message.h \
    ui/addgroup.h \
    gloabal.h \
    ui/addui.h

RESOURCES += \
    resources.qrc

FORMS += \
    ui/addgroup.ui \
    ui/addui.ui

