#include "MainWindow.h"
#include"gloabal.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFont>
#include <QIcon>
#include <QListWidgetItem>
#include <QStringList>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonArray>
#include<qpainterpath.h>
#include"ui/addui.h"
#include"ui/addgroup.h"
MainWindow::MainWindow(const QString& _ui_data,QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(":/img/softwareIcon.png"));

    QSystemTrayIcon *trayIcon= new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/img/softwareIcon.png"));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();

    m_pressFlag = false;
    setUIdata(_ui_data);
    loadResources();
    constructUI();
    connectSlots();
    initDisplayArea();
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow()";
}

void MainWindow::loadResources()
{
    m_mainBackImg.load(":/img/mainBackImg.jpg");
    m_searchImg.load(":/img/search.png");
    m_headImg.load(":/img/head.jpg");
}

void MainWindow::constructUI()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    m_mainBackLabel = new QLabel(this);
    m_mainBackLabel->setFixedHeight(150);

    m_mainLayout.setContentsMargins(0, 0, 0, 0);

    m_mainLayout.addWidget(m_mainBackLabel);
    m_mainLayout.addWidget(&m_displayArea);

    setLayout(&m_mainLayout);

     QJsonDocument jsondoucment__=QJsonDocument::fromJson(user_data.toUtf8());
     auto jsondata__=jsondoucment__.object();

    m_submainLayout = new QVBoxLayout;
    m_submainLayout->setContentsMargins(10, 0, 0, 0);
    m_headLabel.setFixedSize(65, 65);
    m_idLabel.setText( jsondata__.value("Username").toString());
    m_signEdit.setFrame(false);
    m_signEdit.setPlaceholderText(jsondata__.value("PersonalSignature").toString());
    m_signEdit.setStyleSheet("background-color: rgb(255, 255, 255, 0);");

    m_minisizeBtn = new QPushButton(this);;
    m_closeBtn = new QPushButton(this);;
    m_minisizeBtn->setFixedSize(24, 24);
    QString minisizeBtnStyle = "\
        QPushButton{\
            border-image:url(:/img/minisize.png);\
        }\
        QPushButton:hover{\
            border-image:url(:/img/minisizeHover.png);\
        }\
        QPushButton:pressed{\
            border-image:url(:/img/minisizePressed.png);\
        }";
    m_minisizeBtn->setStyleSheet(minisizeBtnStyle);
    m_closeBtn->setFixedSize(24, 24);
    QString closeBtnStyle = "\
        QPushButton{\
            border-image:url(:/img/close.png);\
        }\
        QPushButton:hover{\
            border-image:url(:/img/closeHover.png);\
        }\
        QPushButton:pressed{\
            border-image:url(:/img/closePressed.png);\
        }";
    m_closeBtn->setStyleSheet(closeBtnStyle);
    m_subHLayout0 = new QHBoxLayout;
    m_subHLayout0->setContentsMargins(0, 0, 0, 0);
    m_subHLayout0->setSpacing(0);
    m_subHLayout0->addStretch();
    m_subHLayout0->addWidget(m_minisizeBtn);
    m_subHLayout0->addWidget(m_closeBtn);

    m_subVLayout = new QVBoxLayout;
    m_subVLayout->setSpacing(10);
    m_subVLayout->addWidget(&m_idLabel);
    m_subVLayout->addWidget(&m_signEdit);
    m_subVLayout->addStretch();

    m_subHLayout1 = new QHBoxLayout;
    m_subHLayout1->addWidget(&m_headLabel);
    m_subHLayout1->addLayout(m_subVLayout);

    m_searchLabel.setPixmap(QPixmap::fromImage(m_searchImg));
    m_searchLabel.setFixedSize(24, 30);

    m_searchEdit.setFixedHeight(30);
    m_searchEdit.setFrame(false);
    m_searchEdit.setPlaceholderText("搜索好友");
    m_searchEdit.setStyleSheet("background-color: rgb(255, 255, 255, 80);");

    m_searchEdit1.setFixedHeight(30);
    m_searchEdit1.setFrame(false);
    m_searchEdit1.setPlaceholderText("搜索群");
    m_searchEdit1.setStyleSheet("background-color: rgb(255, 255, 255, 80);");


    m_subHLayout2 = new QHBoxLayout;
    m_subHLayout2->addWidget(&m_searchLabel);
    m_subHLayout2->addWidget(&m_searchEdit);
    m_subHLayout2->addWidget(&m_searchEdit1);

    m_submainLayout->addLayout(m_subHLayout0);
    m_submainLayout->addStretch();
    m_submainLayout->addLayout(m_subHLayout1);
    m_submainLayout->addLayout(m_subHLayout2);

    m_mainBackLabel->setLayout(m_submainLayout);

    resize(300, 700);
    setMinimumWidth(300);
}

void MainWindow::connectSlots()
{
    connect(m_minisizeBtn, SIGNAL(clicked(bool)), this, SLOT(onMinisizeBtn()));
    connect(m_closeBtn, SIGNAL(clicked(bool)), this, SLOT(onCloseBtn()));
    //添加好友
    connect(&m_searchEdit, &QLineEdit::returnPressed, this, [&](){
             QString data=m_searchEdit.text();
             Addui *friendui=new Addui();
             friendui->setData(data);
             friendui->show();
    });
    //添加群
    connect(&m_searchEdit1, &QLineEdit::returnPressed, this, [&](){
        QString data=m_searchEdit.text();
        Addgroup *groupui=new Addgroup();
       // groupui->setData(data);
        groupui->show();
    });
}

void MainWindow::initDisplayArea()
{
    m_displayArea.setTabShape(QTabWidget::Triangular);
    m_displayArea.setDocumentMode(true);
    m_displayArea.setIconSize(QSize(20, 20));
    QString tabBarStyle =
        "QTabWidget::pane{\
            border:none;\
        }\
        QTabWidget::tab-bar{\
                alignment:left;\
        }\
        QTabBar::tab{\
            background:transparent;\
            color:white;\
            min-width:30ex;\
            min-height:10ex;\
        }\
        QTabBar::tab:hover{\
            background:rgb(255, 151, 68, 100);\
        }\
        QTabBar::tab:selected{\
            border-color:rgb(111, 151, 68, 100);\
            background:rgb(111, 151, 68, 80);\
            color:green;\
        }";
    m_displayArea.setStyleSheet(tabBarStyle);

    dialogListWidget = new QListWidget;
    dialogListWidget->setFrameStyle(0);

    friendList = new FriendList(this,friend_ui_data);//好友栏界面
    friendList->setFrameStyle(0);

    groupChatListWidget = new QListWidget;//!!!群界面，待完成
    groupChatListWidget->setFrameStyle(0);

    m_displayArea.addTab(dialogListWidget, QIcon(QPixmap(":/img/dialogIcon.png")), "");
    m_displayArea.addTab(friendList, QIcon(QPixmap(":/img/friendListIcon.png")), "");
    m_displayArea.addTab(groupChatListWidget, QIcon(QPixmap(":/img/groupChatIcon.png")), "");

    m_displayArea.setTabToolTip(0, "会话");
    m_displayArea.setTabToolTip(1, "联系人");
    m_displayArea.setTabToolTip(2, "群聊");

    m_displayArea.setCurrentIndex(1);
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(m_mainBackLabel->x(), m_mainBackLabel->y(), m_mainBackLabel->width(),
            m_mainBackLabel->height(), QPixmap::fromImage(m_mainBackImg));

    painter.setRenderHint(QPainter::Antialiasing, true);    // 让图像边缘显示平滑
    QPainterPath path;
    path.addEllipse(m_headLabel.x(), m_headLabel.y(),
                    m_headLabel.width(), m_headLabel.height());
    painter.setClipPath(path);

    painter.drawPixmap(m_headLabel.x(), m_headLabel.y(), m_headLabel.width(),
                       m_headLabel.height(), QPixmap::fromImage(m_headImg));
    painter.setRenderHint(QPainter::Antialiasing, false);
}

//分割数据，初始化好友数据和群组界面数据
void   MainWindow::setUIdata(const QString& data){

       QJsonDocument jsondoucment=QJsonDocument::fromJson(data.toUtf8());

        // 获取QJsonObject对象
        QJsonObject jsonObject = jsondoucment.object();

        // 解析User部分
        QJsonObject userObject = jsonObject.value("User").toObject();
          user_data =(QJsonDocument(userObject)).toJson();

        // 解析Group部分
        QJsonArray groupArray = jsonObject.value("Group").toArray();
          // 使用QJsonDocument将QJsonArray转换为JSON格式的QByteArray
          QJsonDocument groupDocument(groupArray);
          QByteArray groupByteArray = groupDocument.toJson();
         group_ui_data=groupByteArray;

        for (const QJsonValue& groupValue : groupArray) {
            QJsonObject groupObject = groupValue.toObject();
            QString groupName = groupObject.value("GroupName").toString();
            QString description = groupObject.value("Description").toString();

            // 解析GroupMember部分
            QJsonArray groupMemberArray = groupObject.value("GroupMember").toArray();
            for (const QJsonValue& groupMemberValue : groupMemberArray) {
                QJsonObject groupMemberObject = groupMemberValue.toObject();
                QString joinTime = groupMemberObject.value("JoinTime").toString();
                QString role = groupMemberObject.value("Role").toString();
                int userID = groupMemberObject.value("UserID").toInt();

            }
        }

        // 解析Group部分
        QJsonArray friends = jsonObject.value("Friendship").toArray();
          // 使用QJsonDocument将QJsonArray转换为JSON格式的QByteArray
          QJsonDocument friend__(friends);
         friend_ui_data        = friend__.toJson();
        qDebug()<<friend_ui_data;

}
