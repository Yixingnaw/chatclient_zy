#include "Buddy_group.h"
#include <QDebug>


Buddy_group::Buddy_group(int GroupID,QString GroupName, QString Description,QString GroupMember){
     // qDebug()<<GroupName<<"  dkjasdhas k hdaskdhaskj dhas dhasld jaslkdj lak   "<<GroupMember;
         m_talkDialog = NULL;
    GroupID_=GroupID;
    GroupName_=GroupName;
    Description_=Description;
   GroupMember_=GroupMember;
      // qDebug()<<GroupName_<<"  dkjasdhas k hdaskdhaskj dhas dhasld jaslkdj lak   "<<GroupMember_;
      m_headLabel = new QLabel(this);
      m_nicknameLabel = new QLabel(this);
      m_signatureLabel = new QLabel(this);

      m_headLabel->setFixedSize(36, 40);
      m_headLabel->setToolTip(QString::number(GroupID_));
      m_headLabel->setPixmap(QPixmap("://img/headIcon.jpg").scaled(m_headLabel->width(), m_headLabel->height()));
      m_nicknameLabel->setText(GroupName_);
      m_signatureLabel->setText(Description_);

      //设置个性签名字体为灰色
      QPalette color;
      color.setColor(QPalette::Text,Qt::gray);
      m_signatureLabel->setPalette(color);

      m_vlayout = new QVBoxLayout();
      m_vlayout->addWidget(m_nicknameLabel);
      m_vlayout->addWidget(m_signatureLabel);

      //mainLayout->setSpacing(10);
      mainLayout = new QHBoxLayout();
      mainLayout->addWidget(m_headLabel);
      mainLayout->addLayout(m_vlayout);

      setLayout(mainLayout);
}

Buddy_group::~Buddy_group()
{
    delete m_talkDialog;
}
QString Buddy_group::GroupName(){
    return  GroupName_;
}


QString Buddy_group::Description()
{
    return Description_;
}

QImage Buddy_group::headIcon()
{
    return m_headIcon;
}

QListWidgetItem* Buddy_group::item()
{
    return m_item;
}

void Buddy_group::setListwidgetItem(QListWidgetItem* item)
{
    if (NULL != item) {
        m_item = item;
    }
}

void Buddy_group::mousePressEvent(QMouseEvent *) //鼠标点击事件
{
    //qDebug() << "void Buddy::mousePressEvent(QMouseEvent *event)";
}

void Buddy_group::mouseDoubleClickEvent(QMouseEvent *)
{
    //qDebug() << "void Buddy::mouseDoubleClickEvent(QMouseEvent *event)";
    if (NULL == m_talkDialog) {
        m_talkDialog = new talkdialog_group(GroupID_,GroupName_,Description_,GroupMember_);
        m_talkDialog->setWindowTitle(GroupName_);
      connect(this,&Buddy_group::GROUP_CHAT_MSG_ACK,m_talkDialog,&talkdialog_group::GROUP_CHAT_MSG_ACK_);
    }
    m_talkDialog->show();
}


void  Buddy_group::GROUP_CHAT_MSG_ACK_(QString& data){

    if (NULL == m_talkDialog) {
        //界面类第一次加载
          qDebug()<<"初次加载"<<data;
         m_talkDialog = new talkdialog_group(GroupID_,GroupName_,Description_,GroupMember_);

        m_talkDialog->setWindowTitle(GroupName_);
       connect(this,&Buddy_group::GROUP_CHAT_MSG_ACK,m_talkDialog,&talkdialog_group::GROUP_CHAT_MSG_ACK_);
       //！！！！！可以在主界面显示出来提示的消息
    }else {
        //界面类已经加载
         qDebug()<<"已经加载界面。m_talkDialog指针已经初始化"<<data;
   }
    emit GROUP_CHAT_MSG_ACK(data);
}
int Buddy_group::getID(){
    return  GroupID_;
}
