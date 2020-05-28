#include "pointdialog.h"
#include "ui_pointdialog.h"

pointDialog::pointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pointDialog)
{   
    pi = new qtpointitem();
    ui->setupUi(this);
    ui->piname->setFocus();
}

pointDialog::pointDialog(QWidget *parent, Coordinate *pc, QIcon icon ) :
    QDialog(parent),
    ui(new Ui::pointDialog)
{
    pi = new qtpointitem();
    pi->pc = pc;

    ui->setupUi(this);
    ui->piname->setText( QString::fromStdString( pc->name ) );
    QPixmap pixmap( icon.pixmap(40, QIcon::Normal, QIcon::On) );
    ui->iconPreview->setPixmap( pixmap );
    // FIXME: Alterar widget para gbdeccoordinates se configurado
    ui->gbwidget->EditCoordinates( pc );
}

pointDialog::~pointDialog()
{
    delete ui;
}

void pointDialog::on_buttonBox_accepted()
{
    pi->pc = ui->gbwidget->returnCoord();
    pi->setText(0, QString::fromStdString(
        ui->piname->text().toStdString() ));
    this->accept();
}

void pointDialog::on_buttonBox_rejected()
{
    this->reject();
}
