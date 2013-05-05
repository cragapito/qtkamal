#include "beamdialog.h"
#include "ui_beamdialog.h"

beamDialog::beamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::beamDialog)
{
    bi = new qtbeamitem();
    ui->setupUi(this);
    ui->beamname->setFocus();
}

beamDialog::beamDialog(QWidget *parent, qtbeamitem *bi) :
    QDialog(parent),
    ui(new Ui::beamDialog)
{
    this->bi = bi;
    ui->setupUi(this);

    ui->beamname->setText( QString::fromStdString( bi->bm->source->name ) );
    ui->gbwidget->EditCoordinates( bi->bm->source );
    ui->azimute->setValue( bi->bm->daz );
    ui->alcance->setValue( bi->alcance );
}

beamDialog::~beamDialog()
{
    delete ui;
}

void beamDialog::on_buttonBox_accepted()
{
    bi->bm->source = ui->gbwidget->returnCoord();
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