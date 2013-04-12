#include "point.h"
#include "ui_point.h"

point::point(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::point)
{   
    pi = new qtpointitem();
    ui->setupUi(this);
    ui->piname->setFocus();
}

point::point(QWidget *parent, Coordinate *pc) :
    QDialog(parent),
    ui(new Ui::point)
{
    ui->setupUi(this);
    ui->piname->setText( QString::fromStdString( pc->name ) );
    pi = new qtpointitem();
    pi->pc = pc;
    ui->gbwidget->EditCoordinates( pc );
}

point::~point()
{
    delete ui;
}

void point::on_buttonBox_accepted()
{
    // Não está alterando o nome no widget
    pi->pc = ui->gbwidget->returnCoord();
    pi->pc->name = ui->piname->text().toStdString();
    pi->setText(0, QString::fromStdString(
                    ui->piname->text().toStdString() ));
    this->accept();
}

void point::on_buttonBox_rejected()
{
    this->reject();
}
