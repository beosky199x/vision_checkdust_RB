#include "teachcheckglare.h"
#include "ui_teachcheckglare.h"

teachcheckglare::teachcheckglare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teachcheckglare)
{
    ui->setupUi(this);
}

teachcheckglare::~teachcheckglare()
{
    delete ui;
}
