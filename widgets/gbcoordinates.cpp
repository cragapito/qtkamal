#include "gbcoordinates.h"
#include "ui_gbcoordinates.h"
#include "src/Geo/Coordinate.h"

gbcoordinates::gbcoordinates(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::gbcoordinates)
{
    ui->setupUi(this);
}

gbcoordinates::~gbcoordinates()
{
    delete ui;
}

Coordinate *gbcoordinates::returnCoord()
{
   /* Coordinate *c = new Coordinate(
                ui->latgr->text().toInt(),
                ui->latmin->text().toInt(),
                ui->latseg->text().toDouble(),

                ui->longr->text().toInt(),
                ui->lonmin->text().toInt(),
                ui->lonseg->text().toDouble()   ); */

    Coordinate *c = new Coordinate(10,10);
    //c->name = ui->name->text().toStdString();
    c->name = "testando";
    return c;
}

//TODO: Adicionar Validação

void gbcoordinates::on_latgr_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 2 )
        ui->latmin->setFocus();
}

void gbcoordinates::on_latmin_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 2 )
        ui->latseg->setFocus();
}

void gbcoordinates::on_latseg_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 4 )
        ui->longr->setFocus();
}

void gbcoordinates::on_longr_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 2 )
        ui->lonmin->setFocus();
}

void gbcoordinates::on_lonmin_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 2 )
        ui->lonseg->setFocus();
}
