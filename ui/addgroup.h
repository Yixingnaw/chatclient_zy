#ifndef ADDGROUP_H
#define ADDGROUP_H
#include<QString>
#include <QDialog>
#include"gloabal.h"
namespace Ui {
class Addgroup;
}

class Addgroup : public QDialog
{
    Q_OBJECT

public:
    explicit Addgroup(QWidget *parent = nullptr);
    ~Addgroup();

private slots:
    void on_pushButton_clicked();
    void ADD_GROUP_MSG_ACK(QString&);
    void CREATE_GROUP_MSG_ACK(QString&);
    void on_pushButton_2_clicked();

private:
    Ui::Addgroup *ui;

};

#endif // ADDGROUP_H
