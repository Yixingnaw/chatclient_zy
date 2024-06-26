#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPoint>
#include <QPaintEvent>
#include <QLabel>
#include <QImage>
#include <QLineEdit>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QSystemTrayIcon>
#include "FriendList.h"
#include"Grouplist.h"
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(const QString& _ui_data="",QWidget *parent = 0);
    virtual ~MainWindow();

private:
    QLabel m_headLabel;
    QLabel m_idLabel;
    QLineEdit m_signEdit;
    QLabel* m_mainBackLabel;
    QLabel m_searchLabel;
    QLineEdit m_searchEdit;
    QLineEdit m_searchEdit1;
    QTabWidget m_displayArea;
    QPushButton* m_minisizeBtn;
    QPushButton* m_closeBtn;

    QImage m_headImg;
    QImage m_mainBackImg;
    QImage m_searchImg;

    QHBoxLayout *m_subHLayout0;
    QHBoxLayout *m_subHLayout1;
    QVBoxLayout *m_subVLayout;
    QHBoxLayout *m_subHLayout2;
    QVBoxLayout *m_submainLayout;

    QVBoxLayout m_mainLayout;

    bool m_pressFlag;
    QPoint m_lastPos;

    QListWidget* dialogListWidget;
    FriendList* friendList;
    Grouplist* groupChatListWidget;

    void loadResources();
    void constructUI();
    void connectSlots();
    void initDisplayArea();
private:
    int switch_case_;//根据值初始化群组界面或者好友界面
private:
    QString   user_data;//用户自己的信息
    QString   friend_ui_data;//好友界面显示数据。
    QString   group_ui_data;//群组界面显示数据
    QString   UnreadUserMessage;
private slots:
    void onMinisizeBtn();
    void onCloseBtn();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);


protected:
    void paintEvent(QPaintEvent *);

    // 鼠标支持
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
     void setUIdata(const QString& data);
};

#endif // MAINWINDOW_H
