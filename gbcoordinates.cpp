#include "gbcoordinates.h"
#include "ui_gbcoordinates.h"
#include "src/Geo/Coordinate.h"

gbcoordinates::gbcoordinates(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::gbcoordinates)
{
    gbc = NULL;
    ui->setupUi(this);
    setFocusProxy( ui->latgr );
}

gbcoordinates::~gbcoordinates()
{
    delete ui;
}

Coordinate *gbcoordinates::returnCoord()
{
    if ( ! gbc ) gbc = new Coordinate();

    int lat = ui->latgr->text().toInt();
    int lon = ui->longr->text().toInt();

    if ( ui->comboLat->currentIndex() == 0 ) lat *= -1;
    if ( ui->comboLon->currentIndex() == 0 ) lon *= -1;

    gbc->setGMS( lat,
               ui->latmin->text().toInt(),
               ui->latseg->text().toDouble(),

               lon,
               ui->lonmin->text().toInt(),
               ui->lonseg->text().toDouble() );

    return gbc;
}

void gbcoordinates::EditCoordinates(Coordinate *c)
{
    gbc = c;
    double fractpart, intpart;
    fractpart = modf(fabs(c->x), &intpart);
    ui->latgr->setText( QString::number((int) intpart ));
    ui->latseg->setText( QString::number(
        modf((fabs(fractpart) * 60.0), &intpart) * 60.0));
    ui->latmin->setText( QString::number((int) intpart ));

    fractpart = modf(fabs(c->y), &intpart);
    ui->longr->setText( QString::number((int) intpart ));
    ui->lonseg->setText( QString::number(
        modf((fabs(fractpart) * 60.0), &intpart) * 60.0));
    ui->lonmin->setText( QString::number((int) intpart ));

    (c->x < 0 )? ui->comboLat->setCurrentIndex( 0 ):
                 ui->comboLat->setCurrentIndex( 1 );
    (c->y < 0 )? ui->comboLon->setCurrentIndex( 0 ):
                 ui->comboLon->setCurrentIndex( 1 );
}

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
        emit editDone();
    }
}


