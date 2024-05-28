#ifndef SOCKET_H
#define SOCKET_H

#include"gloabal.h"
#include <QThread>
#include <QHostAddress>
#include <QTcpSocket>
#include<qstring.h>
class Socket : public QThread
{
    Q_OBJECT

private:
    static Socket* c_instance;

    int m_port;
    QString m_ip;
    QHostAddress* m_serverIP;
    QTcpSocket* m_tcpSocket;

    bool m_connectStatus;      // 标识是否连接上服务器
    bool m_runFlag;     // 线程运行标志


    QString data;//用来一次性读取服务器所有数据
    bool flage;//数据包第一次到来是更新length数据
    int64_t length;//数据包长度
    QByteArray bytedata;
private:
    Socket();
    Socket(const Socket&);
    Socket& operator= (const Socket&);
    bool construct();       // 二阶构造

protected:
    void run();     // 线程入口函数

protected slots:
    void onConnected();
    void onDisconnected();
    void onDataReceived();
public:
    static Socket* GetInstance();
    ~Socket();

    bool connectStatus();
    bool runFlag();
    void startThread();
    void stopThread();

    bool sendMsg(const char* buf, int size);
    bool sendMsg(QString msg);
    bool userLogin(QString id, QString passwd);     // 用户登录
    bool registerAccount();     // 注册账号
    bool foundPasswd();         // 找回密码

 signals:
    void  LOGIN_MSG_ACK(QString&);//传递界面数据信号
    void  REG_MSG_ACK(QString&); //服务器注册数据响应
    void ONE_CHAT_MSG_ACK(QString&);
    void ADD_GROUP_MSG_ACK(QString&);
    void ADD_FRIEND_MSG_ACK(QString&);
    void GROUP_CHAT_MSG_ACK(QString&);
    void CREATE_GROUP_MSG_ACK(QString&);
    void LOGINOUT_MSG_ACK(QString&);
};

#endif // SOCKET_H
