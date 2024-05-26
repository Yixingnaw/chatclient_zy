#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include<QString>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    RegisterWidget(QWidget *parent = nullptr);
signals:
      //初始化socket之后在连接。
    void registerSignal(const QString &json_string);

private slots:

    void registerClicked();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *confirmPasswordLineEdit;
    QLineEdit  *personalsignatureEdit;

public:
    QString register_data;
public slots:
    void REG_MSG_ACK(QString& REG_MSG_ACK_data);
};

#endif // REGISTERWIDGET_H
