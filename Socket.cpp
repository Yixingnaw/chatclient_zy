#include "Socket.h"
#include<QDebug>
#include<QMessageBox>
#include<QJsonDocument>
#include<QJsonObject>
#include"gloabal.h"
#include<QtEndian>
Socket* Socket::c_instance = NULL;

Socket::Socket()
{
    m_connectStatus = false;
    m_runFlag = false;
    m_port = 9999;
    m_ip = "192.168.124.14";


    flage=false;
    length=0;
}

Socket::~Socket()
{
    delete m_serverIP;
    delete m_tcpSocket;
    stopThread();
}

bool Socket::construct()
{
    m_serverIP = new QHostAddress();
    m_tcpSocket = new QTcpSocket();

    if (!(m_serverIP && m_tcpSocket)) {
        return false;
    }

    if (!m_serverIP->setAddress(m_ip)) {
        return false;
    }

    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onDataReceived()));

    m_tcpSocket->connectToHost(*m_serverIP, m_port);
    if(m_tcpSocket->waitForConnected(5000)){
        qDebug()<<QString("连接成功");}
    else{
        qDebug()<<"连接失败";
    }

    return true;
}

Socket* Socket::GetInstance()
{
    if (c_instance == NULL) {
        c_instance = new Socket();
        // 若第二阶段构造失败，返回 NULL
        if (!(c_instance && c_instance->construct())) {

            delete c_instance;
            c_instance = NULL;
        }
    }

    return c_instance;
}

bool Socket::connectStatus()
{
    return m_connectStatus;
}

bool Socket::runFlag()
{
    return m_runFlag;
}

void Socket::startThread()
{
    m_runFlag = true;
    //start();
}
void Socket::stopThread()
{
    m_runFlag = false;
    //wait(100000);   // 等待100ms，若线程还不退出，函数返回
}

bool Socket::sendMsg(const char* buf, int size)
{
    if (NULL==buf || size<=0) {
        return false;
    }

    int ret = m_tcpSocket->write(buf, size);
    if (ret != size) {
        return false;
    }

    return true;
}

bool Socket::sendMsg(QString msg)
{
    return sendMsg(msg.toUtf8(), msg.toUtf8().size());
}

bool Socket::userLogin(QString id, QString passwd)
{
    if (!m_connectStatus) {
        //return false;
    }

    return true;
}

bool Socket::registerAccount()
{
    if (!m_connectStatus) {
        //return false;
    }
    return true;
}

bool Socket::foundPasswd()
{
    if (!m_connectStatus) {
        //return false;
    }

    return true;
}

/*
* 1.检查是否连接上服务器，若没有连接服务器
* 2.定期发送心跳包
*/

void Socket::run()
{
    while (m_runFlag); {
        QThread::sleep(1);
    }
}

void Socket::onConnected()
{
    m_connectStatus = true;
}

void Socket::onDisconnected()
{
    m_connectStatus = false;
      QMessageBox::warning(nullptr,"警告 ", "长时间不使用已经掉线");
}
//通过socket发出不同信号连接不同风格槽函数。
void Socket::onDataReceived()
{

    auto  bytedata__=m_tcpSocket->readAll();
                                                                   qDebug()<<bytedata__.size();
     bytedata.append(bytedata__);
     if(bytedata.size()<8){
         return;//继续读取
     }
      if(!flage){
                //读取到八字节后初始化数据包长度
          flage=true;
          auto x=bytedata.left(8);
          length = qFromLittleEndian<qint64>(  *reinterpret_cast<const qint64*>(x.constData()) );
      }
                                                                    qDebug()<<"datasize"<<length<<"   "<<"bytedatesize"<<bytedata.size();
     if(length==bytedata.size()){
       data=QString::fromUtf8(bytedata.mid(8));
     QJsonDocument jsondoucment=QJsonDocument::fromJson(data.toUtf8());
     auto jsondata=jsondoucment.object();
     int x=jsondata["msg_id"].toInt();
     auto msg_id=static_cast<ServerMessage>(x);
      auto value=jsondata["msg_value"].toObject();
      QString msg_value =(QJsonDocument(value)).toJson();   //jsonobejct转化成qstring
     switch (msg_id) {
     case ServerMessage::LOGIN_MSG_ACK:
        {
          emit LOGIN_MSG_ACK(msg_value);
         break;
        }
     case ServerMessage::REG_MSG_ACK:{
         emit REG_MSG_ACK(msg_value);
         break;
     }
     case ServerMessage::LOGINOUT_MSG_ACK:{
         emit LOGINOUT_MSG_ACK(msg_value);
         break;
     }
     case ServerMessage::ONE_CHAT_MSG_ACK:{
         emit ONE_CHAT_MSG_ACK(msg_value);

         break;
     }
     case ServerMessage::ADD_GROUP_MSG_ACK:{
         emit ADD_GROUP_MSG_ACK(msg_value);
         break;
     }
     case ServerMessage::ADD_FRIEND_MSG_ACK:{
         emit ADD_FRIEND_MSG_ACK(msg_value);
         break;
     }
     case ServerMessage::GROUP_CHAT_MSG_ACK:{
         emit GROUP_CHAT_MSG_ACK(msg_value);
         break;
     }
     case ServerMessage::CREATE_GROUP_MSG_ACK:{
         emit CREATE_GROUP_MSG_ACK(msg_value);
         break;
     }
     default: break;
   }
     data.clear();
     bytedata.clear();
     length=0;
     flage=false;
     return;//成功处理完数据
  }else {
    return;//没有读取完继续读取
}
}



