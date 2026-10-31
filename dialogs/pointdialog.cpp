#include "pointdialog.h"
#include "ui_pointdialog.h"

#include <QDebug>

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
    // Libera a coordenada padrão alocada no construtor de qtpointitem antes de associar a existente
    if (pi->pc) delete pi->pc;
    pi->pc = pc;

    ui->setupUi(this);

    ui->piname->setText( QString::fromStdString( pc->name ) );
    QPixmap pixmap( icon.pixmap(40, QIcon::Normal, QIcon::On) );
    ui->iconPreview->setPixmap( pixmap );
    ui->coord_entry->EditCoordinates( pc );

    ui->piname->setFocus();
}

pointDialog::~pointDialog()
{
    delete ui;
}

void pointDialog::on_buttonBox_accepted()
{
    Coordinate *newCoord = ui->coord_entry->returnCoord();
    // Atualiza coordenada liberando a anterior caso seja uma nova instância
    if (newCoord && pi->pc != newCoord) {
        delete pi->pc;
        pi->pc = newCoord;
    }
    pi->pc->name = ui->piname->text().toStdString();
    pi->setText(0, QString::fromStdString(
        ui->piname->text().toStdString() ));
    this->accept();
}

void pointDialog::on_buttonBox_rejected()
{
    this->reject();
}
