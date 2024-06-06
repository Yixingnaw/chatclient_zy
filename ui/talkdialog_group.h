#ifndef TALKDIALOG_GROUP_H
#define TALKDIALOG_GROUP_H
#include<QDebug>
#include <QWidget>
#include<QEvent>
#include<qpushbutton.h>
#include<QKeyEvent>
#include<QApplication>
#include<QTextEdit>
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
public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void history_handle_(QString& data);//加载历史消息
public:
    void history_handle_ACK(QString& data);

    bool event(QEvent *event) override;
};
class KeyPressEventFilter : public QObject {
    Q_OBJECT

public:
    KeyPressEventFilter(QObject *parent = nullptr) : QObject(parent) {}
    static int count;
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
               qDebug()<<"我是你得儿子的eventfiter"<<++count<<"type:"<<event->type();

               if (event->type() == QEvent::KeyPress) {
                          QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
                          QTextEdit *widget = qobject_cast<QTextEdit *>(obj);
                          talkdialog_group *mainWindow = qobject_cast<talkdialog_group *>(parent());
                          if (keyEvent && widget) {
                              if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)&&widget->objectName()=="textEdit") {
                                   mainWindow->on_pushButton_clicked();
                                      return true; // 吃掉这个事件
                              }else if ( keyEvent->key() == Qt::Key_Escape) {
                                  mainWindow->hide();
                                  return  true;
}
                          }
                      }
         return QObject::eventFilter(obj, event);
    }
};
class KeyPressEventFilter_ : public QObject {
    Q_OBJECT

public:
    KeyPressEventFilter_(QObject *parent = nullptr) : QObject(parent) {}
    static int count;
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
               qDebug()<<"我是你得爹的eventfiter"<<++count<<"type:"<<event->type();

               if (event->type() == QEvent::KeyPress) {
                          QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
                          QTextEdit *widget = qobject_cast<QTextEdit *>(obj);
                          talkdialog_group *mainWindow = qobject_cast<talkdialog_group *>(parent());
                          if (keyEvent && widget) {
                              if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)&&widget->objectName()=="textEdit") {
                                   mainWindow->on_pushButton_clicked();
                                      return true; // 吃掉这个事件
                              }else if ( keyEvent->key() == Qt::Key_Escape) {
                                  mainWindow->hide();
                                  return  true;
}
                          }
                      }
               if (event->type() == QEvent::WindowDeactivate) {
                   return  true;
                      }
         return QObject::eventFilter(obj, event);
    }
};
#endif // TALKDIALOG_GROUP_H
