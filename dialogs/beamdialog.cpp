#include "beamdialog.h"
#include "ui_beamdialog.h"

beamDialog::beamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::beamDialog)
{
    ui->setupUi(this);
    ui->beamname->setFocus();
}

beamDialog::~beamDialog()
{
    delete ui;
}
