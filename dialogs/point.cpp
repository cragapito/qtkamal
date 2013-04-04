#include "point.h"
#include "ui_point.h"
#include "utils/qtpointitem.h"

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


void point::on_buttonBox_accepted()
{

}

