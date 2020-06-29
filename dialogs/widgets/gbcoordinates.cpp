#include "gbcoordinates.h"
#include "ui_gbcoordinates.h"
#include "src/Geo/Coordinate.h"

#include <QDebug>

// TODO: Atalho para limpar os dados
gbcoordinates::gbcoordinates(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::gbcoordinates)
{
    gbc = NULL;
    keepFocus = false;

    ui->setupUi(this);

    ui->latgr->installEventFilter( this );
    ui->latmin->installEventFilter( this );
    ui->latseg->installEventFilter( this );

    ui->longr->installEventFilter( this );
    ui->lonmin->installEventFilter( this );
    ui->lonseg->installEventFilter( this );

    ui->dlat->installEventFilter( this );
    ui->dlon->installEventFilter( this );
}

gbcoordinates::~gbcoordinates()
{
    delete ui;
}

Coordinate *gbcoordinates::returnCoord() {
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

void gbcoordinates::updateGMS( Coordinate *c ) {
    keepFocus = true;
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
    keepFocus = false;
}

void gbcoordinates::EditCoordinates( Coordinate *c )
{
    gbc = c;
    updateGMS( c );

    ui->dlat->setText( QString::number( c->x ) );
    ui->dlon->setText( QString::number( c->y ) );
}

bool gbcoordinates::eventFilter(QObject *target, QEvent *event) {
    if ( event->type() == QEvent::FocusIn || event->type() == QEvent::MouseButtonRelease ) {
        QLineEdit* edit=qobject_cast<QLineEdit*>( target );
        if(edit !=nullptr) { // beware could be null
            edit->selectAll();
            return true;
        }
    }
    if ( event->type() == QEvent::KeyRelease ) {
        gbc = this->returnCoord();
        if ( target == ui->dlat || target == ui->dlon ) {
            gbc->x = ui->dlat->text().toDouble();
            gbc->y = ui->dlon->text().toDouble();
            this->updateGMS( gbc );
        } else {
            ui->dlat->setText( QString::number( gbc->x ) );
            ui->dlon->setText( QString::number( gbc->y ) );
        }
    }
    return false;
}

/*
 *
 *  Movimentação do Foco
 *
 */

void gbcoordinates::on_latgr_textChanged(const QString &what) {
    if ( keepFocus ) return;
    if ( what.size() >= 2 ) {
        ui->latmin->setFocus();
        ui->latmin->selectAll();
    }
}

void gbcoordinates::on_latmin_textChanged(const QString &what) {
    if ( keepFocus ) return;
    if ( what.size() >= 2 ) {
        ui->latseg->setFocus();
        ui->latseg->selectAll();
    }
}

void gbcoordinates::on_latseg_textChanged(const QString &what) {
    if ( keepFocus ) return;
    if ( what.size() >= 4 ) {
        ui->longr->setFocus();
        ui->longr->selectAll();
    }
}

void gbcoordinates::on_longr_textChanged(const QString &what) {
    if ( keepFocus ) return;
    if ( what.size() >= 2 ) {
        ui->lonmin->setFocus();
        ui->lonmin->selectAll();
    }
}

void gbcoordinates::on_lonmin_textChanged(const QString &what) {
    if ( keepFocus ) return;
    if ( what.size() >= 2 ) {
        ui->lonseg->setFocus();
        ui->lonseg->selectAll();
    }
}

void gbcoordinates::on_lonseg_textChanged(const QString &what) {
    if ( keepFocus ) return;
    if ( what.size() >= 4 ) {
        emit editDone();
    }
}
