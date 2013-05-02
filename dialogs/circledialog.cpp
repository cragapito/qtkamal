#include "circledialog.h"
#include "ui_circledialog.h"
#include "src/Geo/Beam.h"

circleDialog::circleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::circleDialog)
{
    ci = new qtcircleitem();
    ui->setupUi(this);
    ui->circname->setFocus();
}

circleDialog::circleDialog(QWidget *parent, qtcircleitem *ci) :
    QDialog(parent),
    ui(new Ui::circleDialog)
{
    this->ci = ci;
    ui->setupUi(this);
    ui->circname->setText( QString::fromStdString( ci->center->name ));
    ui->gbwidget->EditCoordinates( ci->center );
    ui->raio->setValue(   ci->radius );
    ui->pontos->setValue( ci->points );
}

circleDialog::~circleDialog()
{
    delete ui;
}

void circleDialog::on_buttonBox_accepted()
{
    ci->center = ui->gbwidget->returnCoord();
    ci->center->name = ui->circname->text().toStdString();
    ci->radius = ui->raio->value();
    ci->points = ui->pontos->value();
    ci->setText(0, QString::fromStdString(
        ui->circname->text().toStdString() ));

    this->calc();
    this->accept();
}

void circleDialog::on_buttonBox_rejected()
{
    this->reject();
}

void circleDialog::calc()
{
    Beam *b = new Beam();
    b->source = ci->center;
    double step = 360.0 / ci->points;

    ci->perimeter.clear();

    for ( int i = 0 ; i < ci->points + 1 ; i++ ){
        b->daz = i * step;
        b->proj( ci->radius );

        ci->perimeter.append(   QString::number( b->scope->y, 'g', 12)
                          + ","
                          + QString::number( b->scope->x, 'g', 12)
                          + ",0 ");
    }

    delete(b);
}
