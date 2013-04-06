#ifndef qtkamal_H
#define qtkamal_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "src/Geo/Coordinate.h"
#include "utils/qtpointitem.h"

namespace Ui {
class qtkamal;
}

class qtkamal : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit qtkamal(QWidget *parent = 0);
    ~qtkamal();

    QTreeWidgetItem* groupPoints;
    QTreeWidgetItem* groupBeans;
    QTreeWidgetItem* groupERMs;
    QTreeWidgetItem* groupCircles;
    
private slots:
    void on_actionPnt_triggered();
    void on_actionCirc_triggered();

private:
    Ui::qtkamal *ui;
};

#endif // qtkamal_H
