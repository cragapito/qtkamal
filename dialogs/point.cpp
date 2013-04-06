#include "point.h"
#include "ui_point.h"

point::point(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::point)
{   
    gb = new gbcoordinates();
    pi = new qtpointitem();

    ui->setupUi(this);
    ui->piname->setFocus();
}

point::point(QWidget *parent, Coordinate *pc) :
    QDialog(parent),
    ui(new Ui::point)
{
    gb = new gbcoordinates( parent, pc );
    ui->setupUi(this);
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
