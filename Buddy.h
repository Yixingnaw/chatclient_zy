#ifndef BUDDY_H
#define BUDDY_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QListWidgetItem>

#include "TalkDialog.h"

class Buddy : public QWidget
{
    Q_OBJECT
private:
    QLabel* m_headLabel;
    QLabel* m_nicknameLabel;
    QLabel* m_signatureLabel;

    QVBoxLayout* m_vlayout;
    QHBoxLayout* mainLayout;

    QListWidgetItem* m_item;
    TalkDialog* m_talkDialog;


protected:
    //好友界面数据
    int m_id;               // 此ID作为一个用户的唯一标识
    QString m_nickname;     // 昵称/网名
    QString m_signature;    // 个性签名
    bool state;  //是否在线标识
    QImage m_headIcon;      // 头像


    void mousePressEvent(QMouseEvent *);//鼠标点击事件
    void mouseDoubleClickEvent(QMouseEvent *);
public:
    explicit Buddy(bool state_=false,int id=0, QString nickname="", QString signature="");//好友界面数据
    explicit Buddy(QWidget* parent);
    virtual ~Buddy();

    int id();
    QString nickname();
    QString signature();
    QImage headIcon();

    QListWidgetItem* item();

    void setListwidgetItem(QListWidgetItem* item);
    int getID();

signals:
     void ONE_CHAT_MSG_ACK(QString&);//继续向好友分组界面传输数据。

public slots:
      void ONE_CHAT_MSG_ACK_(QString& data);

};

#endif // BUDDY_H
