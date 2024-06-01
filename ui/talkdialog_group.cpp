#include "talkdialog_group.h"
#include "ui_talkdialog_group.h"
#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonArray>
#include<QListWidgetItem>
#include<QIcon>
#include"Socket.h"
#include<QDateTime>
talkdialog_group::talkdialog_group(int x,QString y,QString z,QString ui_data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::talkdialog_group)
{
    ui->setupUi(this);
    ui_groupmember_data=ui_data;
    groupid=x;
    groupname=y;
    description=z;
    constructUi();
}

talkdialog_group::~talkdialog_group()
{
    delete ui;
}

void talkdialog_group::constructUi(){
    //解析groupmember
    QJsonDocument jsondoucment=QJsonDocument::fromJson(ui_groupmember_data.toUtf8());
    auto groupmembers=jsondoucment.array();
    for (const QJsonValue& groupMemberValue : groupmembers) {
        QJsonObject groupMemberObject = groupMemberValue.toObject();
        QString joinTime = groupMemberObject.value("JoinTime").toString();
        QString role = groupMemberObject.value("Role").toString();
        int userID = groupMemberObject.value("UserID").toInt();
        QListWidgetItem*  member=new QListWidgetItem;
        member->setText(role+":  "+QString::number(userID));
        member->setIcon(QIcon("://img/headIcon.jpg"));
        member->setTextAlignment(Qt::AlignHCenter);
        ui->listWidget->addItem(member);
    }
    ui->textEdit_2->append(description);
    ui->textEdit_2->setReadOnly(true);

}

void talkdialog_group::on_pushButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();

    if (Socket::GetInstance()) {

        QJsonObject message;
        message["msg_id"]=static_cast<int>(ServerMessage::GROUP_CHAT_MSG);
        QJsonObject message_value;
        message_value["handle_value"]=  2;
        message_value["SenderID"]=   ::curUserInfo.id.toInt();
        message_value["GroupID"]=  groupid;
        message_value["Content"]=msg;
        message_value["SendTime"]=(QDateTime::currentDateTime()).toString("yyyy-MM-dd");
        message["msg_value"]=message_value;
        QJsonDocument personDocument(message);
        QString jsonstring = personDocument.toJson();
       Socket::GetInstance()->sendMsg(jsonstring);
                                       //   qDebug() << "msg:" << msg;
    }

        QString formattedText = QString("<div style='text-align:right;'>"
                                                "<div style='font-size:small; color:grey;'>%1</div>"
                                                "<div>%2</div>"
                                                "</div>").arg((QDateTime::currentDateTime()).toString("yyyy-MM-dd"), msg);

        ui->textBrowser->append(formattedText);

        ui->textEdit->clear();

}

void talkdialog_group::GROUP_CHAT_MSG_ACK_(QString& data){
    QJsonDocument jsondoucment=QJsonDocument::fromJson(data.toUtf8());
     auto jsondata=jsondoucment.object();
      int x=jsondata.value("handle_value").toInt();
      switch (x) {
      case 1:{

      }
      case 2:{
          QString SendTime=jsondata.value("SendTime").toString();
          QString Content=jsondata.value("Content").toString();
          QString formattedText = QString("<div style='text-align:right;'>"
                                                  "<div style='font-size:small; color:grey;'>%1</div>"
                                                  "<div>%2</div>"
                                                  "</div>").arg(SendTime, Content);
          ui->textBrowser->append(formattedText);

      }
      default: break;
      }
      return ;
}


