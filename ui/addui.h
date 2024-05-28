#ifndef ADDUI_H
#define ADDUI_H
#include"gloabal.h"
#include <QWidget>
#include<QString>
#include<qstring.h>
namespace Ui {
class Addui;
}

class Addui : public QWidget
{
    Q_OBJECT

public:
    explicit Addui(QWidget *parent = nullptr);
    ~Addui();
    void  setData(QString &x);
private slots:
    void on_pushButton_clicked();
    void ADD_FRIEND_MSG_ACK(QString&);
private:
    Ui::Addui *ui;
    QString   friendID;
};

#endif // ADDUI_H
