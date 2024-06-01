#ifndef TALKDIALOG_GROUP_H
#define TALKDIALOG_GROUP_H

#include <QWidget>

namespace Ui {
class talkdialog_group;
}

class talkdialog_group : public QWidget
{
    Q_OBJECT

public:
    explicit talkdialog_group(int x,QString y,QString z,QString ui_data="",QWidget *parent = nullptr);
    ~talkdialog_group();
     void constructUi();
private:
    Ui::talkdialog_group *ui;
    QString ui_groupmember_data;
    int groupid;
    QString groupname;
    QString description;
public slots:
    void GROUP_CHAT_MSG_ACK_(QString&);
private slots:
    void on_pushButton_clicked();
};

#endif // TALKDIALOG_GROUP_H
