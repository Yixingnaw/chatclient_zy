#include"RegisterWidget.h"
#include"gloabal.h"
#include"Socket.h"
RegisterWidget:: RegisterWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("用户注册", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // 用户名输入框
    QLabel *usernameLabel = new QLabel("用户名:", this);
    layout->addWidget(usernameLabel);
    usernameLineEdit = new QLineEdit(this);
    layout->addWidget(usernameLineEdit);

    // 密码输入框
    QLabel *passwordLabel = new QLabel("密码:", this);
    layout->addWidget(passwordLabel);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordLineEdit);

    // 确认密码输入框
    QLabel *confirmPasswordLabel = new QLabel("确认密码:", this);
    layout->addWidget(confirmPasswordLabel);
    confirmPasswordLineEdit = new QLineEdit(this);
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(confirmPasswordLineEdit);

    //个性签名输入框
    QLabel *personalsignature = new QLabel("个性签名:", this);
    layout->addWidget(personalsignature);
    personalsignatureEdit = new QLineEdit(this);
    layout->addWidget(personalsignatureEdit);


    // 注册按钮
    QPushButton *registerButton = new QPushButton("注册", this);
    connect(registerButton, &QPushButton::clicked, this, &RegisterWidget::registerClicked);
    layout->addWidget(registerButton);

    setLayout(layout);

    connect(Socket::GetInstance(),&Socket::REG_MSG_ACK,this,&RegisterWidget::REG_MSG_ACK);
}


void  RegisterWidget::registerClicked()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();
    QString confirmPassword = confirmPasswordLineEdit->text();
    QString personalsignature=personalsignatureEdit->text();
    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名或密码不能为空！");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "警告", "密码不一致！");
        return;
    }
    QJsonObject message;
    message["msg_id"]=static_cast<int>(ServerMessage::REG_MSG);
    QJsonObject message_value;
    message_value["Password"]=password;
    message_value["Username"]=username;
    message_value["PersonalSignature"]=personalsignature;
    message["msg_value"]=message_value;
    QJsonDocument personDocument(message);
    QString jsonString = personDocument.toJson();
    emit registerSignal(jsonString);
}
void RegisterWidget::REG_MSG_ACK(QString& REG_MSG_ACK_data){

}
