#ifndef qtkamal_H
#define qtkamal_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "utils/stylefold.h"
#include "utils/qtbeamitem.h"
#include "utils/qtpointitem.h"
#include "utils/qtcircleitem.h"
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

    styleFold       *sty;
    kml             *map;

    void args(QStringList args);

protected:
    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);
    
private slots:
    void on_actionPnt_triggered();
    void on_actionMan_triggered();
    void on_actionEst_triggered();
    void on_actionCirc_triggered();
    void on_actionGetEarth_triggered();
    void on_actionAbout_triggered();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void deleteItemHandler();

private:
    Ui::qtkamal *ui;
};

#endif // qtkamal_H
