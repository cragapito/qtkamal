#include "circledialog.h"
#include "ui_circledialog.h"
#include "src/Geo/Beam.h"

circleDialog::circleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::circleDialog)
{
    ci = new qtcircleitem();

    ui->setupUi(this);

    cnf = new config();

    if ( cnf->useDecimal ) {
        ui->coord_entry->setCurrentIndex(1);
    }

    ui->raio->setValue      ( cnf->circ_radius      );
    ui->pontos->setValue    ( cnf->circ_points      );
    ui->alcance->setValue   ( cnf->circ_radius      );
    ui->abertura->setValue  ( cnf->circ_opening     );
    ui->azimute->setValue   ( cnf->beam_azimuth     );

    ui->circname->setFocus();
}

circleDialog::circleDialog(QWidget *parent, qtcircleitem *ci) :
    QDialog(parent),
    ui(new Ui::circleDialog)
{
    cnf = NULL;
    this->ci = ci;
    ui->setupUi(this);

    cnf = new config();
    if ( cnf->useDecimal ) {
        ui->coord_entry->setCurrentIndex(1);
    }

    ui->GMS->EditCoordinates( ci->center );
    ui->decimal->EditCoordinates( ci->center );
    ui->circname->setText( QString::fromStdString( ci->center->name ));
    ui->comboType->setCurrentIndex( ci->tipoSelect );

    ui->raio->setValue    ( ci->radius   );
    ui->pontos->setValue  ( ci->points   );
    ui->azimute->setValue ( ci->azimute  );
    ui->alcance->setValue ( ci->radius   );
    ui->abertura->setValue( ci->abertura );
}

circleDialog::~circleDialog()
{
    delete ui;
}

void circleDialog::on_buttonBox_accepted()
{
    if ( cnf != NULL ) {
        cnf->circ_radius    = ui->raio->value();
        cnf->circ_points    = ui->pontos->value();
        cnf->circ_radius    = ui->alcance->value();
        cnf->circ_opening   = ui->abertura->value();

        if ( ci->tipoSelect == 1 ) {
                    cnf->beam_azimuth   = ui->azimute->value();
        }

        cnf->save();
    }

    ci->center->name = ui->circname->text().toStdString();
    // FIXME: Unificar os dados dos dois widgets de entrada
    //ci->center       = ui->gbwidget->returnCoord();
    ci->radius       = ui->raio->value();
    ci->points       = ui->pontos->value();
    ci->azimute      = ui->azimute->value();
    ci->abertura     = ui->abertura->value();
    ci->tipoSelect   = ui->comboType->currentIndex();

    ci->setText(0, QString::fromStdString(
        ui->circname->text().toStdString() ));

    ci->calc();

    this->accept();
}

void circleDialog::on_buttonBox_rejected()
{
    this->reject();
}

void circleDialog::on_comboType_currentIndexChanged(int index)
{
    ui->cirSect->setCurrentIndex( index );
    ci->tipoSelect = index;
}
