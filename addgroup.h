#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QDialog>

namespace Ui {
class Addgroup;
}

class Addgroup : public QDialog
{
    Q_OBJECT

public:
    explicit Addgroup(QWidget *parent = nullptr);
    ~Addgroup();

private:
    Ui::Addgroup *ui;
};

#endif // ADDGROUP_H
