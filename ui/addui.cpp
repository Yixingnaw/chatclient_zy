#include "addui.h"
#include"gloabal.h"
#include"Socket.h"
#include "ui_addui.h"
#include<QJsonObject>
#include<QJsonDocument>
#include"LoginDialog.h"
#include<qmessagebox.h>
Addui::Addui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Addui)
{
    ui->setupUi(this);
   connect(Socket::GetInstance(),&Socket::ADD_FRIEND_MSG_ACK,this,&Addui::ADD_FRIEND_MSG_ACK);
}

Addui::~Addui()
{
    delete ui;
}

void  Addui::setData(QString &x){
    friendID =x;
    ui->lineEdit->setText(friendID);
}

void Addui::on_pushButton_clicked()
{
    friendID=ui->lineEdit->text();
    QString friendRemark=ui->lineEdit_2->text();
    if(friendRemark==QString("")||friendID==QString("")){
         QMessageBox::warning(this, "警告", "用户名或备注不能为空！");
    }
    auto m_socket=Socket::GetInstance();
    if (NULL != m_socket) {
        QJsonObject message;
        message["msg_id"]=static_cast<int>(ServerMessage::ADD_FRIEND_MSG);
        QJsonObject message_value;
        message_value["UserID"]=  ::curUserInfo.id.toInt();
        message_value["FriendID"]= friendID.toInt();
        if(::curUserInfo.id.toInt()== friendID.toInt()){
             QMessageBox::warning(this, "警告", "请不要输入自己的账号");
             return;
        }
        message_value["FriendRemark"]= friendRemark;
        message["msg_value"]=message_value;
        QJsonDocument personDocument(message);
        QString jsonstring = personDocument.toJson();
       m_socket->sendMsg(jsonstring);
    }
}
void Addui::ADD_FRIEND_MSG_ACK(QString&ADD_FRIEND_MSG_ACK_data){
    auto jsonobject=QJsonDocument::fromJson(ADD_FRIEND_MSG_ACK_data.toUtf8());
    if(jsonobject["value"]==QString("添加好友成功")){
          QMessageBox::warning(this, "恭喜", "成功添加好友"+ui->lineEdit_2->text());
         return;
    }
    if(jsonobject["value"]==QString("添加好友失败")){
          QMessageBox::warning(this, "警告", "没有这个好友"+ui->lineEdit_2->text()+"或者成功添加请重新登录刷新界面");
        return;
   }
}
