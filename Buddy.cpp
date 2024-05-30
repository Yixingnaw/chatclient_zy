#include "Buddy.h"

#include <QDebug>


Buddy::Buddy(bool state_,int id, QString nickname, QString signature)
{
    m_talkDialog = NULL;

    state=state_;
    m_id = id;
    m_nickname = nickname;
    m_signature = signature;

    m_headLabel = new QLabel(this);
    m_nicknameLabel = new QLabel(this);
    m_signatureLabel = new QLabel(this);

    m_headLabel->setFixedSize(36, 40);
    m_headLabel->setToolTip(QString::number(id));
    m_headLabel->setPixmap(QPixmap("://img/headIcon.jpg").scaled(m_headLabel->width(), m_headLabel->height()));
    m_nicknameLabel->setText(nickname);
    m_signatureLabel->setText(signature);

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
Buddy::Buddy(int GroupID,QString GroupName, QString Description,QString GroupMember){
         m_talkDialog = NULL;
    GroupID_=GroupID;
    GroupName_=GroupName;
    Description_=Description;
   GroupMember_=GroupMember;
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

Buddy::~Buddy()
{
    delete m_talkDialog;
}


int Buddy::id()
{
    return m_id;
}

QString Buddy::nickname()
{
    return m_nickname;
}

QString Buddy::signature()
{
    return m_signature;
}

QImage Buddy::headIcon()
{
    return m_headIcon;
}


QListWidgetItem* Buddy::item()
{
    return m_item;
}

void Buddy::setListwidgetItem(QListWidgetItem* item)
{
    if (NULL != item) {
        m_item = item;
    }
}

void Buddy::mousePressEvent(QMouseEvent *) //鼠标点击事件
{
    //qDebug() << "void Buddy::mousePressEvent(QMouseEvent *event)";
}

void Buddy::mouseDoubleClickEvent(QMouseEvent *)
{
    //qDebug() << "void Buddy::mouseDoubleClickEvent(QMouseEvent *event)";
    if (NULL == m_talkDialog) {
        m_talkDialog = new TalkDialog(this);
        m_talkDialog->setWindowTitle(m_nickname);
         connect(this,&Buddy::ONE_CHAT_MSG_ACK,m_talkDialog,&TalkDialog::ONE_CHAT_MSG_ACK_);
    }
    m_talkDialog->show();
}

void Buddy::ONE_CHAT_MSG_ACK_(QString& data){

    if (NULL == m_talkDialog) {
        //界面类第一次加载
          qDebug()<<"初次加载"<<data;
        m_talkDialog = new TalkDialog(this);
        m_talkDialog->setWindowTitle(m_nickname);
        connect(this,&Buddy::ONE_CHAT_MSG_ACK,m_talkDialog,&TalkDialog::ONE_CHAT_MSG_ACK_);
    }else {
        //界面类已经加载
         qDebug()<<"已经加载界面。m_talkDialog指针已经初始化"<<data;

}

     emit ONE_CHAT_MSG_ACK(data);
}
int Buddy::getID(){
    return  m_id;
}
