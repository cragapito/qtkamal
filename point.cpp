#include "point.h"
#include "ui_point.h"

point::point(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::point)
{   
    ui->setupUi(this);
    ui->name->setFocus();
}

point::~point()
{
    delete ui;
}
