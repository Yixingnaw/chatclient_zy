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
        message_value["UserID"]=  ::curUserInfo.id;
        message_value["FriendID"]= friendID;
        message_value["FriendRemark"]= friendRemark;
        message["msg_value"]=message_value;
        QJsonDocument personDocument(message);
        QString jsonstring = personDocument.toJson();
       m_socket->sendMsg(jsonstring);

    }
}
