#ifndef GBDECCOORDINATES_H
#define GBDECCOORDINATES_H

#include <math.h>
#include <QGroupBox>
#include "src/Geo/Coordinate.h"

namespace Ui {
class gbdeccoordinates;
}

class gbdeccoordinates : public QGroupBox
{
    Q_OBJECT
    
public:
    explicit gbdeccoordinates(QWidget *parent = 0);
    ~gbdeccoordinates();

    Coordinate* returnCoord();
    Coordinate* gbc;

    void EditCoordinates( Coordinate *c );

private:
    Ui::gbdeccoordinates *ui;

private slots: 
    void on_lat_textChanged (const QString &arg1);
    void on_lon_textChanged (const QString &arg1);


signals:
    void editDone();
};

#endif // GBDECCOORDINATES_H
