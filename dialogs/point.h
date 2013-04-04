#ifndef POINT_H
#define POINT_H

#include <QDialog>
#include <widgets/gbcoordinates.h>

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
    gbcoordinates* gb;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::point *ui;
    gbcoordinates* coord;
};

#endif // POINT_H
