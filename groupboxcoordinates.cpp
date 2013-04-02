#include "groupboxcoordinates.h"

groupboxcoordinates::groupboxcoordinates(QWidget *parent) :
    QWidget(parent)
{
}

Coordinate *groupboxcoordinates::returnCoord()
{
    Coordinate *c = new Coordinate(
                this->latgr->text().toInt(),
                this->latmin->text().toInt(),
                this->latseg->text().toDouble(),

                this->longr->text().toInt(),
                this->lonmin->text().toInt(),
                this->lonseg->text().toDouble()   );

    c->name = this->name->text().toStdString();

    return c;
}

void groupboxcoordinates::on_buttonBox_accepted()
{
    returnCoord();
}

void groupboxcoordinates::on_latgr_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 2 )
        this->latmin->setFocus();
}

void groupboxcoordinates::on_latmin_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 2 )
        this->latseg->setFocus();
}

void groupboxcoordinates::on_latseg_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 4 )
        this->longr->setFocus();
}

void groupboxcoordinates::on_longr_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 2 )
        this->lonmin->setFocus();
}

void groupboxcoordinates::on_lonmin_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 2 )
        this->lonseg->setFocus();
}

void groupboxcoordinates::on_lonseg_textChanged(const QString &arg1)
{
    if ( arg1.size() >= 4 )
        this->buttonBox->setFocus();
}
