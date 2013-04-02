#ifndef GROUPBOXCOORDINATES_H
#define GROUPBOXCOORDINATES_H

#include <QWidget>
#include "src/Geo/Coordinate.h"

class groupboxcoordinates : public QWidget
{
    Q_OBJECT
public:
    explicit groupboxcoordinates(QWidget *parent = 0);
    Coordinate* returnCoord();
    
signals:

private slots:

    void on_buttonBox_accepted();

    void on_latgr_textChanged (const QString &arg1);
    void on_latmin_textChanged(const QString &arg1);
    void on_latseg_textChanged(const QString &arg1);

    void on_longr_textChanged (const QString &arg1);
    void on_lonmin_textChanged(const QString &arg1);
    void on_lonseg_textChanged(const QString &arg1);
    
public slots:
    
};

#endif // GROUPBOXCOORDINATES_H
