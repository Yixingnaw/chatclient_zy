#ifndef GROUP_GROUP_H
#define GROUP_GROUP_H


#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QMouseEvent>
#include <QList>
#include <QHBoxLayout>
#include <QListWidgetItem>

#include "Buddy_group.h"

class Group_group : public QWidget
{
    Q_OBJECT
private:
    bool m_isHide;                 // 该组是否隐藏
    int m_id;                      // 组ID
    QString m_name;                // 组名称
    QListWidgetItem* m_item;

    QList<Buddy_group*> m_groupList;    //群组列表
protected:
public:
    explicit Group_group(int id=0, QString name="");
    virtual ~Group_group();

    int id();
    QString name();

    void  addBuddy_group(Buddy_group* buddy);
    void setListwidgetItem(QListWidgetItem* item);
    void displayGroup(QListWidget* listWidget);

    QListWidgetItem* item();
    void mousePress();
signals:

public slots:

      void GROUP_CHAT_MSG_ACK_Select(QString& data);
};
#endif // GROUP_GROUP_H
