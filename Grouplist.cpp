#include "Grouplist.h"

#include"Socket.h"
#include <QLabel>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonArray>
#include <QDebug>


Grouplist::Grouplist(QWidget *parent,QString data) : QListWidget(parent), m_parent(parent)
{
    setFriendList(data);
    displayFriendList();
     connect(Socket::GetInstance(),&Socket::GROUP_CHAT_MSG_ACK,this,&Grouplist::GROUP_CHAT_MSG_ACK_);
}

Grouplist::~Grouplist()
{
    qDebug() << "FriendList::~FriendList()";
    for (int i=0; i<m_groupList.count(); i++) {
        delete m_groupList[i];
    }

    m_groupList.clear();
}


void Grouplist::addGroup(Group_group *group)
{
    if (NULL == group) {
        return;
    }

    m_groupList.append(group);
}


void Grouplist::setFriendList(QString& data)       // 获取群组列表
{
    this->group_data=data;
}



void Grouplist::displayFriendList()
{
    qDebug()<<group_data;

    QJsonDocument jsondoucment=QJsonDocument::fromJson(group_data.toUtf8());
    auto friendarray=jsondoucment.array();
    Group_group* group_friend = new Group_group(0, "群组");
         connect(this,&Grouplist::GROUP_CHAT_MSG_ACK,group_friend,&Group_group::GROUP_CHAT_MSG_ACK_Select);//连接槽函数

    for (const QJsonValue& friendValue : friendarray) {
        QJsonObject friendObject = friendValue.toObject();
        QString Username = friendObject.value("GroupName").toString();
        QString PersonalSignature = friendObject.value("Description").toString();
        QString GroupMember=   QJsonDocument(friendObject.value("GroupMember").toArray()).toJson();
                                      //qDebug()<<GroupMember<<"会不会有一天";
        int id_=friendObject.value("GroupID").toInt();
          Buddy_group* buddy = new Buddy_group(id_,Username, PersonalSignature,GroupMember);
           group_friend->addBuddy_group(buddy);
    }

    addGroup(group_friend);

    Group_group* group1 = new Group_group(1, "Friends");
    connect(this,&Grouplist::GROUP_CHAT_MSG_ACK,group1,&Group_group::GROUP_CHAT_MSG_ACK_Select);//连接槽函数

  //  Buddy* buddy2 = new Buddy(2, "路人甲");
   // group1->addBuddy(buddy2);
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


void Grouplist::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "void FriendList::mousePressEvent(QMouseEvent *event)";
    QListWidget::mousePressEvent(event);

    mousePree(event);
}


void Grouplist::mouseDoubleClickEvent(QMouseEvent *event)
{
    //qDebug() << "void FriendList::mouseDoubleClickEvent(QMouseEvent *event)";
    QListWidget::mousePressEvent(event);
    mousePree(event);
}

void Grouplist::mousePree(QMouseEvent *event)
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
void Grouplist::GROUP_CHAT_MSG_ACK_(QString& data){
      emit GROUP_CHAT_MSG_ACK(data);
}
