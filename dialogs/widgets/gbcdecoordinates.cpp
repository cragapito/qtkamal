#include "gbdeccoordinates.h"
#include "ui_gbdeccoordinates.h"
#include "src/Geo/Coordinate.h"

// FIXME: Operar coordenadas decimais
gbdeccoordinates::gbdeccoordinates(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::gbdeccoordinates)
{
    gbc = NULL;
    ui->setupUi(this);
}

gbdeccoordinates::~gbdeccoordinates()
{
    delete ui;
}

Coordinate *gbdeccoordinates::returnCoord()
{
    if ( ! gbc ) gbc = new Coordinate();

    //int lat = ui->latgr->text().toInt();
    //int lon = ui->longr->text().toInt();

    //if ( ui->comboLat->currentIndex() == 0 ) lat *= -1;
    //if ( ui->comboLon->currentIndex() == 0 ) lon *= -1;

    //gbc->setGMS( lat,
    //           ui->latmin->text().toInt(),
    //           ui->latseg->text().toDouble(),

    //           lon,
    //           ui->lonmin->text().toInt(),
    //           ui->lonseg->text().toDouble() );

    return gbc;
}

void gbdeccoordinates::EditCoordinates(Coordinate *c)
{
    gbc = c;
    double fractpart, intpart;
    fractpart = modf(fabs(c->x), &intpart);
    //ui->latgr->setText( QString::number((int) intpart ));
    //ui->latseg->setText( QString::number(
    //    modf((fabs(fractpart) * 60.0), &intpart) * 60.0));
    //ui->latmin->setText( QString::number((int) intpart ));

    //fractpart = modf(fabs(c->y), &intpart);
    //ui->longr->setText( QString::number((int) intpart ));
    //ui->lonseg->setText( QString::number(
    //    modf((fabs(fractpart) * 60.0), &intpart) * 60.0));
    //ui->lonmin->setText( QString::number((int) intpart ));

    //(c->x < 0 )? ui->comboLat->setCurrentIndex( 0 ):
    //             ui->comboLat->setCurrentIndex( 1 );
    //(c->y < 0 )? ui->comboLon->setCurrentIndex( 0 ):
    //             ui->comboLon->setCurrentIndex( 1 );
}

// Movimentação do Foco
void gbdeccoordinates::on_lat_textChanged(const QString &arg1) {
    if ( arg1.size() >= 2 ) {
        //ui->latmin->setFocus();
        //ui->latmin->selectAll();
    }
}

void gbdeccoordinates::on_lon_textChanged(const QString &arg1) {
    if ( arg1.size() >= 2 ) {
    //    ui->lonmin->setFocus();
    //    ui->lonmin->selectAll();
    }
}
