#ifndef POINT_H
#define POINT_H

#include <QDialog>
#include "src/Geo/Coordinate.h"

namespace Ui {
class point;
}

class point : public QDialog
{
    Q_OBJECT

    Coordinate* c;
    
public:
    explicit point(QWidget *parent = 0);
    ~point();

private:
    Ui::point *ui;
};

#endif // POINT_H
