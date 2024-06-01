#ifndef BUDDY_GROUP_H
#define BUDDY_GROUP_H


#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QListWidgetItem>

#include"ui/talkdialog_group.h"

class Buddy_group : public QWidget
{
    Q_OBJECT
private:
    QLabel* m_headLabel;
    QLabel* m_nicknameLabel;
    QLabel* m_signatureLabel;

    QVBoxLayout* m_vlayout;
    QHBoxLayout* mainLayout;

    QListWidgetItem* m_item;
    talkdialog_group* m_talkDialog;


protected:

    bool state;  //是否在线标识
    QImage m_headIcon;      // 头像

    //群组界面数据
     int  GroupID_;
     QString GroupName_;
     QString Description_;
     QString GroupMember_;

    void mousePressEvent(QMouseEvent *);//鼠标点击事件
    void mouseDoubleClickEvent(QMouseEvent *);
public:

     explicit Buddy_group(int GroupID=0 ,QString GroupName="", QString Description="",QString GroupMember="");//群组界面数据

    virtual ~Buddy_group();

    QString GroupName();
    QString Description();
    QImage headIcon();
    int getID();

    QListWidgetItem* item();

    void setListwidgetItem(QListWidgetItem* item);


signals:

     void   GROUP_CHAT_MSG_ACK(QString&);//群组界面传输数据
public slots:

      void GROUP_CHAT_MSG_ACK_(QString& data);
};

#endif // BUDDY_GROUP_H
