#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QMouseEvent>
#include <QList>
#include <QHBoxLayout>

#include "Buddy.h"
#include "Group.h"


class FriendList : public QListWidget
{
    Q_OBJECT
private:
    QWidget* m_parent;
    QList<Group*> m_groupList;    // 分组列表

    QString friend_data;
protected:
    void mousePressEvent(QMouseEvent *event);//鼠标点击事件
    void mouseDoubleClickEvent(QMouseEvent *event);

public:
    explicit FriendList(QWidget *parent=nullptr,QString data_="");
    ~FriendList();

    void addGroup(Group* group);

    void setFriendList(QString&);       // 获取好友列表
    void displayFriendList();   // 将好友列表显示到界面
    void mousePree(QMouseEvent *event);

signals:
     void ONE_CHAT_MSG_ACK(QString&);//继续向分组界面传输数据。
public slots:
      void ONE_CHAT_MSG_ACK_(QString& data);
};

#endif // FRIENDLIST_H
