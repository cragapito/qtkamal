#include "configdialog.h"
#include "ui_configdialog.h"

#include "configdialog.h"

configDialog::configDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configDialog)
{
    ui->setupUi(this);
    cnf = new config();

    ui->usedecimals->setChecked( cnf->useDecimal);

    ui->fazimuth->setValue( cnf->beam_azimuth   );
    ui->freach->setValue(   cnf->beam_reach     );

    ui->aazimute->setValue( cnf->circ_opening   );
    ui->apoints->setValue(  cnf->circ_points    );
    ui->aradius->setValue(  cnf->circ_radius    );

    ui->gproj->setValue(    cnf->gproj          );
    ui->gattack->setValue(  cnf->gattack        );
}

configDialog::~configDialog()
{
    delete ui;
}

void configDialog::on_buttonBox_accepted()
{
    cnf->useDecimal     = ui->usedecimals->checkState();

    cnf->beam_azimuth   = ui->fazimuth->value();
    cnf->beam_reach     = ui->freach->value();

    cnf->circ_opening   = ui->aazimute->value();
    cnf->circ_points    = ui->apoints->value();
    cnf->circ_radius    = ui->aradius->value();

    cnf->gproj          = ui->gproj->value();
    cnf->gattack        = ui->gattack->value();

    cnf->save();
    this->accept();
}

void configDialog::on_buttonBox_rejected()
{
    this->reject();
}

void configDialog::on_reset_clicked()
{
    cnf->reset();
    this->close();
}
