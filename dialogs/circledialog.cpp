#include "circledialog.h"
#include "ui_circledialog.h"

circleDialog::circleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::circleDialog)
{
    ui->setupUi(this);
}

circleDialog::~circleDialog()
{
    delete ui;
}
