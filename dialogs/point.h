#ifndef POINT_H
#define POINT_H

#include <QDialog>
#include <QString>
#include <gbcoordinates.h>
#include "utils/qtpointitem.h"

namespace Ui {
class point;
}

class point : public QDialog
{
    Q_OBJECT

public:
    explicit point(QWidget *parent = 0);
    explicit point(QWidget *parent, Coordinate *pc, QIcon icon );
    ~point();

    qtpointitem *pi;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::point *ui;
};

#endif // POINT_H
