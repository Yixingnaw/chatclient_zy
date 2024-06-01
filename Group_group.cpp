#include "Group_group.h"


#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonArray>
#include <QDebug>

Group_group::Group_group(int id, QString name)
{
    m_isHide = true;
    m_id = id;
    m_name = name;
}

Group_group::~Group_group()
{
    qDebug() << "Group::~Group()";
    for (int i=0; i<m_groupList.count(); i++) {
        delete m_groupList[i];
    }

    m_groupList.clear();
}

int Group_group::id()
{
    return m_id;
}

QString Group_group::name()
{
    return m_name;
}

void Group_group::addBuddy_group(Buddy_group *buddy){

    if (NULL == buddy) {
        return;
    }

    m_groupList.append(buddy);
}

void Group_group::setListwidgetItem(QListWidgetItem* item)
{
    if (NULL != item) {
        m_item = item;
    }
}

void Group_group::displayGroup(QListWidget* listWidget)
{

    for (int i=0; i<m_groupList.count(); i++) {
        QListWidgetItem *newItem = new QListWidgetItem(listWidget);       //创建一个newItem
        newItem->setSizeHint(QSize(listWidget->width(), 50)); //设置宽度、高度
        listWidget->addItem(newItem);
        listWidget->setItemWidget(newItem, m_groupList[i]);
        newItem->setHidden(m_isHide);
        m_groupList[i]->setListwidgetItem(newItem);
    }
}

QListWidgetItem* Group_group::item()
{
    return m_item;
}

void Group_group::mousePress()
{
    //qDebug() << "void Group::mousePress()";

    if (m_isHide) {
        m_item->setIcon(QIcon("://img/openIcon.png"));
    } else {
        m_item->setIcon(QIcon("://img/hideIcon.png"));
    }
    m_isHide = !m_isHide;

    for (int i=0; i<m_groupList.count(); i++) {
        m_groupList[i]->item()->setHidden(m_isHide);
    }
}

void  Group_group::GROUP_CHAT_MSG_ACK_Select(QString& data){
    QJsonDocument jsondoucment=QJsonDocument::fromJson(data.toUtf8());
    auto jsondata=jsondoucment.object();
    int  groupid=jsondata.value("GroupID").toInt();
    for(auto x:m_groupList){
        //通过发送方主键id来识别唯一界面。
        if(groupid==x->getID()){

            x->GROUP_CHAT_MSG_ACK_(data);
            break;
        }
    }
}
