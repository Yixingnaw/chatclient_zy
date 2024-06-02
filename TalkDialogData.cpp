#include "TalkDialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonArray>
#include<QDateTime>
#include <QDebug>
#include"Buddy.h"
void TalkDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressFlag) {
        if (m_isMaxsize) {      // 有问题
            m_isMaxsize = false;
            this->showNormal();
            /*resize(m_lastSize);
            setWindowState(Qt::WindowNoState);
            int x = event->pos().x() - m_lastSize.width() / 2;
            if (x < 0) {
                x = 0;
            }
            this->move(x, event->pos().y());
            m_maxisizeBtn->setStyleSheet(m_maxsizeBtnStyle);
            */
        } else {
            QPoint pos = event->globalPos();
            move(this->pos() + pos - m_lastPos);
            m_lastPos = pos;
        }
    }

    event->ignore();//表示继续向下传递事件，其他的控件还可以去获取
}

void TalkDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->pos().y() < 100) {
        onMaxsizeBtn();
    }

    event->ignore();
}

void TalkDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressFlag = true;
        m_lastPos = event->globalPos();
    }

    event->ignore();
}

void TalkDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressFlag = false;
    }

    event->ignore();
}

void TalkDialog::onMinisizeBtn()
{
    this->showMinimized();
}
void TalkDialog::onMaxsizeBtn()
{
    if (!m_isMaxsize) {
        //qDebug() << windowState();
        m_lastSize = this->size();
        this->showMaximized();
        m_maxisizeBtn->setStyleSheet(m_restoreBtnStyle);
    } else {
        this->showNormal();
        m_maxisizeBtn->setStyleSheet(m_maxsizeBtnStyle);
    }
    m_isMaxsize = !m_isMaxsize;
}

void TalkDialog::onCloseBtn()
{
    this->close();
}
void TalkDialog::onSendBtn()
{
    QString msg = m_inputArea->toPlainText();
     if(msg=="")return;
    if (m_socket) {
        QJsonObject message;
        message["msg_id"]=static_cast<int>(ServerMessage::ONE_CHAT_MSG);
        QJsonObject message_value;
        message_value["SenderID"]=   ::curUserInfo.id.toInt();
        std::function<int()>  funC=std::bind(&Buddy::getID,reinterpret_cast<Buddy*>(this->m_buddy));
        message_value["ReceiverID"]=funC();
        message_value["Content"]=msg;
        message_value["SendTime"]=(QDateTime::currentDateTime()).toString("yyyy-MM-dd");
        message["msg_value"]=message_value;
        QJsonDocument personDocument(message);
        QString jsonstring = personDocument.toJson();
       m_socket->sendMsg(jsonstring);
                                      //   qDebug() << "msg:" << msg;
    }

        QString formattedText = QString("<div style='text-align:right;'>"
                                                "<div style='font-size:small; color:grey;'>%1</div>"
                                                "<div>%2</div>"
                                                "</div>").arg((QDateTime::currentDateTime()).toString("yyyy-MM-dd"), msg);

        m_msgDisplayArea->appendHtml(formattedText);
        m_inputArea->clear();

}
//显示数据就行。
void TalkDialog::ONE_CHAT_MSG_ACK_(QString& data){
    QJsonDocument jsondoucment=QJsonDocument::fromJson(data.toUtf8());
    auto jsondata=jsondoucment.object();
    QString SendTime=jsondata.value("SendTime").toString();
    QString Content=jsondata.value("Content").toString();
    QString formattedText = QString("<div style='text-align:right;'>"
                                            "<div style='font-size:small; color:grey;'>%1</div>"
                                            "<div>%2</div>"
                                            "</div>").arg(SendTime, Content);
    m_msgDisplayArea->appendHtml(formattedText);
}

void TalkDialog::GROUP_CHAT_MSG_ACK_(QString& data){

}
