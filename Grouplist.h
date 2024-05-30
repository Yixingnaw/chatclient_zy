#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QMouseEvent>
#include <QList>
#include <QHBoxLayout>

#include "Buddy.h"
#include "Group.h"


class Grouplist : public QListWidget
{
    Q_OBJECT
private:
    QWidget* m_parent;
    QList<Group*> m_groupList;    // 分组列表

    QString group_data;
protected:
    void mousePressEvent(QMouseEvent *event);//鼠标点击事件
    void mouseDoubleClickEvent(QMouseEvent *event);

public:
    explicit Grouplist(QWidget *parent=nullptr,QString data_="");
    ~Grouplist();

    void addGroup(Group* group);

    void setFriendList(QString&);       // 获取群组列表
    void displayFriendList();   // 将群组列表显示到界面
    void mousePree(QMouseEvent *event);


};


#endif // GROUPLIST_H
