#include "gbcoordinates.h"
#include "ui_gbcoordinates.h"
#include "src/Geo/Coordinate.h"

gbcoordinates::gbcoordinates(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::gbcoordinates)
{
    c = NULL;
    ui->setupUi(this);
}

gbcoordinates::gbcoordinates(QWidget *parent, Coordinate *c)
{
    double fractpart, intpart;
    fractpart = modf(c->x, &intpart);
    ui->latgr->text().setNum ( (int) intpart );
    ui->latseg->text().setNum( modf((fabs(fractpart) * 60.0), &intpart) * 60.0);
    ui->latmin->text().setNum( (int) intpart );
}

gbcoordinates::~gbcoordinates()
{
    delete ui;
}

Coordinate *gbcoordinates::returnCoord()
{
    c = new Coordinate();

    c->setGMS( ui->latgr->text().toInt(),
               ui->latmin->text().toInt(),
               ui->latseg->text().toDouble(),

               ui->longr->text().toInt(),
               ui->lonmin->text().toInt(),
               ui->lonseg->text().toDouble() );

    return c;
}

//TODO: Adicionar Validação
// Movimentação do Foco
void gbcoordinates::on_latgr_textChanged(const QString &arg1) {
    if ( arg1.size() >= 2 ) {
        ui->latmin->setFocus();
    }
}

void gbcoordinates::on_latmin_textChanged(const QString &arg1) {
    if ( arg1.size() >= 2 ) {
        ui->latseg->setFocus();
    }
}

void gbcoordinates::on_latseg_textChanged(const QString &arg1) {
    if ( arg1.size() >= 4 ) {
        ui->longr->setFocus();
    }
}

void gbcoordinates::on_longr_textChanged(const QString &arg1) {
    if ( arg1.size() >= 2 ) {
        ui->lonmin->setFocus();
    }
}

void gbcoordinates::on_lonmin_textChanged(const QString &arg1) {
    if ( arg1.size() >= 2 ) {
        ui->lonseg->setFocus();
    }
}

void gbcoordinates::on_lonseg_textChanged(const QString &arg1) {
    if ( arg1.size() >= 4 ) {
    }
}


