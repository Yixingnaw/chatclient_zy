#ifndef GROUP_H
#define GROUP_H

#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QMouseEvent>
#include <QList>
#include <QHBoxLayout>
#include <QListWidgetItem>

#include "Buddy.h"

class Group : public QWidget
{
    Q_OBJECT
private:
    bool m_isHide;                 // 该组是否隐藏
    int m_id;                      // 组ID
    QString m_name;                // 组名称
    QListWidgetItem* m_item;
    QList<Buddy*> m_friendList;    // 好友列表

    QList<Buddy*> m_groupList;    //群组列表
protected:
public:
    explicit Group(int id=0, QString name="");
    virtual ~Group();

    int id();
    QString name();
    void addBuddy_friend(Buddy* buddy);
    void  addBuddy_group(Buddy* buddy);
    void setListwidgetItem(QListWidgetItem* item);
    void displayGroup(QListWidget* listWidget);

    QListWidgetItem* item();
    void mousePress();
signals:

public slots:
      void ONE_CHAT_MSG_ACK_Select(QString& data);//具体选择触发显示哪个好友界面的函数
      void GROUP_CHAT_MSG_ACK_Select(QString& data);
};
#endif // GROUP_H
