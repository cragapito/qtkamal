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

    QAction *deleteItemAction;

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

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void deleteItemHandler();

    void on_actionGetEarth_triggered();

private:
    Ui::qtkamal *ui;
};

#endif // qtkamal_H
