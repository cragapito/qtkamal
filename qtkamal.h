#ifndef qtkamal_H
#define qtkamal_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "utils/stylefold.h"
#include "utils/qtpointitem.h"
#include "src/Geo/Coordinate.h"

class kml;

namespace Ui {
class qtkamal;
}

class qtkamal : public QMainWindow
{
    Q_OBJECT
    QAction *deleteItemAction;
    QAction *clearOldAction;

public:
    explicit qtkamal(QWidget *parent = 0);
    ~qtkamal();

    QTreeWidgetItem* groupPoints;
    QTreeWidgetItem* groupBeans;
    QTreeWidgetItem* groupERMs;
    QTreeWidgetItem* groupCircles;

    styleFold       *sty;
    kml             *map;
    
private slots:
    void on_actionPnt_triggered();
    void on_actionCirc_triggered();
    void on_actionGetEarth_triggered();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void deleteItemHandler();
    void clearOldHandler();

private:
    Ui::qtkamal *ui;
};

#endif // qtkamal_H
