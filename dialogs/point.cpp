#include "point.h"
#include "ui_point.h"

point::point(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::point)
{   
    gb = new gbcoordinates();

    if ( pi ) {
        pi = new qtpointitem();
        isnew = true;
    } else {
        isnew = false;
    }

    ui->setupUi(this);
    ui->piname->setFocus();
}

point::~point()
{
    delete ui;
}

void point::on_buttonBox_accepted()
{
    pi->pc = gb->returnCoord();
    pi->pc->name = ui->piname->text().toStdString();
    pi->setText(0, QString::fromStdString(
                    ui->piname->text().toStdString() ));
    this->accept();
}

void point::on_buttonBox_rejected()
{
    this->reject();
}
