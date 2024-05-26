#include "addgroup.h"
#include "ui_addgroup.h"

Addgroup::Addgroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addgroup)
{
    ui->setupUi(this);
}

Addgroup::~Addgroup()
{
    delete ui;
}
