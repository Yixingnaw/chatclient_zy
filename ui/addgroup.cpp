#include "addgroup.h"
#include "ui_addgroup.h"
#include"gloabal.h"
#include"Socket.h"
#include<QJsonObject>
#include<QJsonDocument>
#include"LoginDialog.h"
#include<qmessagebox.h>
Addgroup::Addgroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addgroup)
{
    ui->setupUi(this);
     connect(Socket::GetInstance(),&Socket::ADD_GROUP_MSG_ACK,this,&Addgroup::ADD_GROUP_MSG_ACK);
     connect(Socket::GetInstance(),&Socket::CREATE_GROUP_MSG_ACK,this,&Addgroup::CREATE_GROUP_MSG_ACK);
}

Addgroup::~Addgroup()
{
    delete ui;
}
/*
{
     "msg_id":
     "msg_vlaue":{
         "Role":
         "JoinTime":
         "GroupID":
         "UserID":
     }
     注意role和jointime格式
}
*/
void Addgroup::on_pushButton_clicked()
{
     auto groupID=ui->lineEdit->text();
     if(groupID==""){
          QMessageBox::warning(this, "警告", "群号不能为空！");
          return;
     }
     auto m_socket=Socket::GetInstance();
     if (NULL != m_socket) {
         QJsonObject message;
         message["msg_id"]=static_cast<int>(ServerMessage::ADD_GROUP_MSG);
         QJsonObject message_value;
         message_value["Role"]="Member";
         message_value["UserID"]=  ::curUserInfo.id.toInt();
         message_value["GroupID"]= groupID.toInt();
         message_value["JoinTime"]= "1999-09-01";
         message["msg_value"]=message_value;
         QJsonDocument personDocument(message);
         QString jsonstring = personDocument.toJson();
        m_socket->sendMsg(jsonstring);

     }
}
void Addgroup::on_pushButton_2_clicked()
{
    auto GroupName=ui->lineEdit_2->text();
    auto Description=ui->lineEdit_3->text();
    if(GroupName==""||Description==""){
         QMessageBox::warning(this, "警告", "群号或者群信息不能为空！");
         return;
    }
    auto m_socket=Socket::GetInstance();
    if (NULL != m_socket) {
        QJsonObject message;
        message["msg_id"]=static_cast<int>(ServerMessage::CREATE_GROUP_MSG);
        QJsonObject message_value;
        message_value["UserID"]=  ::curUserInfo.id.toInt();
        message_value["JoinTime"]= "1999-09-01";
        message_value["GroupName"]=GroupName;
        message_value["Description"]=Description;
        message["msg_value"]=message_value;
        QJsonDocument personDocument(message);
        QString jsonstring = personDocument.toJson();
       m_socket->sendMsg(jsonstring);
    }
}

void Addgroup::ADD_GROUP_MSG_ACK(QString& ADD_GROUP_MSG_ACK_data){
    auto jsonobject=QJsonDocument::fromJson(ADD_GROUP_MSG_ACK_data.toUtf8());

   if(jsonobject["value"]==QString("加群成功")){
         QMessageBox::warning(this, "恭喜", "成功加入群组"+ui->lineEdit->text());
        return;
   }
   if(jsonobject["value"]==QString("加群失败")){
         QMessageBox::warning(this, "警告", "没有这个群"+ui->lineEdit->text()+"或者你已经在群组里面重新登录用来刷新群");
       return;
  }
}

void Addgroup::CREATE_GROUP_MSG_ACK(QString&  CREATE_GROUP_MSG_ACK_data){
      auto jsonobject=QJsonDocument::fromJson(CREATE_GROUP_MSG_ACK_data.toUtf8());
      if(jsonobject["value"]==QString("创建群组成功")){

            QMessageBox::warning(this, "恭喜", "你成为"+QString::number(jsonobject["GroupID"].toInt())+"的群主啦！");
           return;
      }
      if(jsonobject["value"]==QString("创建群组失败")){
            QMessageBox::warning(this, "警告", "创建群组失败");
          return;
     }
}
