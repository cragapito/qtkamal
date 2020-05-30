#include "beamdialog.h"
#include "ui_beamdialog.h"

beamDialog::beamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::beamDialog)
{
    bi = new qtbeamitem();
    cnf = new config();
    ui->setupUi(this);

    cnf = new config();

    if ( cnf->useDecimal ) {
        ui->coord_entry->setCurrentIndex(1);
    }

    ui->azimute->setValue( cnf->beam_azimuth    );
    ui->alcance->setValue( cnf->beam_reach      );

    ui->beamname->setFocus();
}

beamDialog::beamDialog(QWidget *parent, qtbeamitem *bi) :
    QDialog(parent),
    ui(new Ui::beamDialog)
{
    cnf = NULL;
    this->bi = bi;
    ui->setupUi(this);

    cnf = new config();
    if ( cnf->useDecimal ) {
        ui->coord_entry->setCurrentIndex(1);
    }

    ui->beamname->setText( QString::fromStdString( bi->bm->source->name ) );
    ui->GMS->EditCoordinates( bi->bm->source );
    ui->decimal->EditCoordinates( bi->bm->source );
    ui->azimute->setValue( bi->bm->daz );
    ui->alcance->setValue( bi->alcance );
}

beamDialog::~beamDialog()
{
    delete ui;
}

void beamDialog::on_buttonBox_accepted()
{
    if ( cnf != NULL ) {
        cnf->beam_azimuth   = ui->azimute->value();
        cnf->beam_reach     = ui->alcance->value();
        cnf->save();
    }

    // FIXME: Unificar os dados dos dois widgets de entrada
    // bi->bm->source = ui->gbwidget->returnCoord();
    bi->bm->source->name = ui->beamname->text().toStdString();
    bi->bm->daz = ui->azimute->value();
    bi->bm->proj( ui->alcance->value() );

    bi->alcance = ui->alcance->value();
    bi->setText(0, QString::fromStdString(
        ui->beamname->text().toStdString() ));
    this->accept();
}

void beamDialog::on_buttonBox_rejected()
{
    this->reject();
}
