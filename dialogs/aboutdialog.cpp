#include "aboutdialog.h"
#include "ui_aboutdialog.h"

// TODO: Descrever o menu de configuração na ajuda.
aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
}

aboutDialog::~aboutDialog()
{
    delete ui;
}
