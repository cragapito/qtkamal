#include "beamdialog.h"
#include "ui_beamdialog.h"

beamDialog::beamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::beamDialog)
{
    bi = new qtbeamitem();
    cnf = new config();
    ui->setupUi(this);

    ui->azimute->setValue( cnf->beam_azimuth    );
    ui->alcance->setValue( cnf->beam_reach      );

    ui->beamname->setFocus();
}

beamDialog::beamDialog(QWidget *parent, qtbeamitem *bi) :
    QDialog(parent),
    ui(new Ui::beamDialog)
{
    cnf = nullptr; // Apenas o construtor padrão utiliza nova instância de configuração
    this->bi = bi;
    ui->setupUi(this);

    ui->beamname->setText( QString::fromStdString( bi->bm->source->name ) );
    ui->coord_entry->EditCoordinates( bi->bm->source );
    ui->azimute->setValue( bi->bm->daz );
    ui->alcance->setValue( bi->alcance );

    ui->beamname->setFocus();
}

beamDialog::~beamDialog()
{
    delete ui;
    if (cnf) delete cnf;
}

void beamDialog::on_buttonBox_accepted()
{
    Coordinate *newCoord = ui->coord_entry->returnCoord();
    // Atualiza a coordenada de origem do feixe liberando a anterior caso seja uma nova instância
    if (newCoord && bi->bm->source != newCoord) {
        delete bi->bm->source;
        bi->bm->source = newCoord;
    }
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
