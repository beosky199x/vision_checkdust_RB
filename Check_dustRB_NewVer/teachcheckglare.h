#ifndef TEACHCHECKGLARE_H
#define TEACHCHECKGLARE_H

#include <QDialog>

namespace Ui {
class teachcheckglare;
}

class teachcheckglare : public QDialog
{
    Q_OBJECT

public:
    explicit teachcheckglare(QWidget *parent = 0);
    ~teachcheckglare();

private:
    Ui::teachcheckglare *ui;
};

#endif // TEACHCHECKGLARE_H
