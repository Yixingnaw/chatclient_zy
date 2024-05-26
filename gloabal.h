#ifndef GLOABAL_H
#define GLOABAL_H
#include<qstring.h>
struct UserInfo {
    QString id;
    QString username;
    QString pesonalSignature;
    QString passwd;
    bool remeberPasswd;
    bool autoLogin;
};
enum class ServerMessage{
    LOGIN_MSG = 1,  //登录消息，绑定login
    LOGIN_MSG_ACK,  //登录响应消息
    REG_MSG,        //注册消息，绑定regist
    REG_MSG_ACK,    //注册响应消息
    ONE_CHAT_MSG,   //一对一聊天消息
    ONE_CHAT_MSG_ACK, //一对一聊天消息响应
    ADD_FRIEND_MSG, //添加好友消息
    ADD_FRIEND_MSG_ACK,
    CREATE_GROUP_MSG, //创建群聊
    CREATE_GROUP_MSG_ACK,
    ADD_GROUP_MSG,    //加入群聊
    ADD_GROUP_MSG_ACK,
    GROUP_CHAT_MSG,   //群聊消息
    GROUP_CHAT_MSG_ACK,
    LOGINOUT_MSG,   //注销消息
    LOGINOUT_MSG_ACK,
};
extern UserInfo curUserInfo;
#endif // GLOABAL_H
