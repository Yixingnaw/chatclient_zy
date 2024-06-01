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
    Buddy_group.cpp \
    Group_group.cpp \
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
    ui/addui.cpp \
    ui/talkdialog_group.cpp

HEADERS  += LoginDialog.h \
    Buddy_group.h \
    Group_group.h \
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
    ui/addui.h \
    ui/talkdialog_group.h

RESOURCES += \
    resources.qrc

FORMS += \
    ui/addgroup.ui \
    ui/addui.ui \
    ui/talkdialog_group.ui

