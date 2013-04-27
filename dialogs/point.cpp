#include "point.h"
#include "ui_point.h"

point::point(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::point)
{   
    pi = new qtpointitem();
    ui->setupUi(this);
    ui->piname->setFocus();
}

point::point(QWidget *parent, Coordinate *pc, QIcon icon ) :
    QDialog(parent),
    ui(new Ui::point)
{
    pi = new qtpointitem();
    pi->pc = pc;

    ui->setupUi(this);
    ui->piname->setText( QString::fromStdString( pc->name ) );
    QPixmap pixmap( icon.pixmap(40, QIcon::Normal, QIcon::On) );
    ui->iconPreview->setPixmap( pixmap );
    ui->gbwidget->EditCoordinates( pc );
}

point::~point()
{
    delete ui;
}

void point::on_buttonBox_accepted()
{
    pi->pc = ui->gbwidget->returnCoord();
    pi->setText(0, QString::fromStdString(
        ui->piname->text().toStdString() ));
    this->accept();
}

void point::on_buttonBox_rejected()
{
    this->reject();
}
