#include "FriendList.h"
#include <QLabel>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonArray>
#include "Buddy.h"

#include <QDebug>


FriendList::FriendList(QWidget *parent,QString data) : QListWidget(parent), m_parent(parent)
{
    setFriendList(data);
    displayFriendList();
}

FriendList::~FriendList()
{
    qDebug() << "FriendList::~FriendList()";
    for (int i=0; i<m_groupList.count(); i++) {
        delete m_groupList[i];
    }

    m_groupList.clear();
}


void FriendList::addGroup(Group *group)
{
    if (NULL == group) {
        return;
    }

    m_groupList.append(group);
}


void FriendList::setFriendList(QString& data)       // 获取好友列表
{
    this->friend_data=data;
}



void FriendList::displayFriendList()   // 将好友列表显示到界面,这里传进来所有的好友用户。
{
    qDebug()<<friend_data;

    QJsonDocument jsondoucment=QJsonDocument::fromJson(friend_data.toUtf8());
    auto friendarray=jsondoucment.array();

    Group* group_friend = new Group(0, "好友");
    for (const QJsonValue& friendValue : friendarray) {
        QJsonObject friendObject = friendValue.toObject();
        QString Username = friendObject.value("Username").toString();
        QString PersonalSignature = friendObject.value("PersonalSignature").toString();
          Buddy* buddy = new Buddy(0, Username, PersonalSignature);
           group_friend->addBuddy(buddy);
    }

    addGroup(group_friend);

    Group* group1 = new Group(1, "Friends");
    Buddy* buddy2 = new Buddy(2, "路人甲");
    group1->addBuddy(buddy2);
    addGroup(group1);

    for (int i=0; i<m_groupList.count(); i++) {
        QIcon hideIcon("://img/hideIcon.png");
        QListWidgetItem *newItem = new QListWidgetItem(hideIcon, m_groupList[i]->name());   //创建一个newItem
        newItem->setSizeHint(QSize(m_parent->width(), 32)); //设置宽度、高度
        addItem(newItem);
        newItem->setHidden(false);
        m_groupList[i]->setListwidgetItem(newItem);
        m_groupList[i]->displayGroup(this);
    }
}


void FriendList::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "void FriendList::mousePressEvent(QMouseEvent *event)";
    QListWidget::mousePressEvent(event);

    mousePree(event);
}


void FriendList::mouseDoubleClickEvent(QMouseEvent *event)
{
    //qDebug() << "void FriendList::mouseDoubleClickEvent(QMouseEvent *event)";
    QListWidget::mousePressEvent(event);

    mousePree(event);
}

void FriendList::mousePree(QMouseEvent *event)
{
    QListWidgetItem *currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));//鼠标位置的Item，不管右键左键都获取

    if (event->button()==Qt::LeftButton && currentItem!=NULL) {
        for (int i=0; i<m_groupList.count(); i++) {
            if (currentItem == m_groupList[i]->item()) {
                m_groupList[i]->mousePress();
            }
        }
    }
}
