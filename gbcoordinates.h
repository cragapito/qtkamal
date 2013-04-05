#ifndef GBCOORDINATES_H
#define GBCOORDINATES_H

#include <QGroupBox>
#include "src/Geo/Coordinate.h"

namespace Ui {
class gbcoordinates;
}

class gbcoordinates : public QGroupBox
{
    Q_OBJECT
    
public:
    explicit gbcoordinates(QWidget *parent = 0);
    ~gbcoordinates();

    Coordinate* returnCoord();
    Coordinate* c;
    
private slots:

    void on_latgr_textChanged (const QString &arg1);
    void on_latmin_textChanged(const QString &arg1);
    void on_latseg_textChanged(const QString &arg1);

    void on_longr_textChanged (const QString &arg1);
    void on_lonmin_textChanged(const QString &arg1);
    void on_lonseg_textChanged(const QString &arg1);

private:
    Ui::gbcoordinates *ui;

};

#endif // GBCOORDINATES_H
