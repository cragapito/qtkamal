#ifndef KAMALTREE_H
#define KAMALTREE_H

#include "utils/kml.h"
#include "utils/stylefold.h"
#include "utils/qtbeamitem.h"
#include "utils/qtpointitem.h"
#include "utils/qtcircleitem.h"

#include <QTreeWidget>

class kml;

class kamalTree : public QTreeWidget
{
    Q_OBJECT

private:

    styleFold       *sty;

    void toPoint(qtbeamitem   *bi, QTreeWidgetItem *where);
    void toPoint(qtcircleitem *ci, QTreeWidgetItem *where);

    void toBeam(qtpointitem   *pi, qtbeamitem::TYPE type, QTreeWidgetItem *where);
    void toBeam(qtbeamitem    *bii, qtbeamitem::TYPE type, QTreeWidgetItem *where);
    void toBeam(qtcircleitem  *ci, qtbeamitem::TYPE type, QTreeWidgetItem *where);

    void toCircle(qtpointitem *pi, QTreeWidgetItem *where);
    void toCircle(qtbeamitem  *bi, QTreeWidgetItem *where);

public:
    explicit kamalTree(QWidget *parent = 0);

    kml            *map;

    QTreeWidgetItem* groupPoints;
    QTreeWidgetItem* groupBeans;
    QTreeWidgetItem* groupERMs;
    QTreeWidgetItem* groupCircles;

    void SetStyleFold(styleFold *sf);
    void removeChild (QTreeWidgetItem *child);
    
protected:
    void dropEvent (QDropEvent *event);

public slots:
    void clearOldHandler();

signals:
    void beamMoved();
};

#endif // KAMALTREE_H
