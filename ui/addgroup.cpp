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
     }
     auto m_socket=Socket::GetInstance();
     if (NULL != m_socket) {
         QJsonObject message;
         message["msg_id"]=static_cast<int>(ServerMessage::ADD_GROUP_MSG);
         QJsonObject message_value;
         message_value["Role"]="Member";//待确认
         message_value["UserID"]=  ::curUserInfo.id;
         message_value["GroupID"]= groupID;
         message_value["JoinTime"]= "1999-09-01";
         message["msg_value"]=message_value;
         QJsonDocument personDocument(message);
         QString jsonstring = personDocument.toJson();
        m_socket->sendMsg(jsonstring);

     }
}
