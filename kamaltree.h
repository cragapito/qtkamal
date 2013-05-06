#ifndef KAMALTREE_H
#define KAMALTREE_H

//#include "utils/kml.h"
#include "utils/stylefold.h"
#include "utils/qtbeamitem.h"
#include "utils/qtpointitem.h"
#include "utils/qtcircleitem.h"

#include <QTreeWidget>

class kamalTree : public QTreeWidget
{
    Q_OBJECT

private:
    styleFold       *sty;

    void toPoint(qtbeamitem *bi);
    void toPoint(qtcircleitem *ci);

public:
    explicit kamalTree(QWidget *parent = 0);

    QTreeWidgetItem* groupPoints;
    QTreeWidgetItem* groupBeans;
    QTreeWidgetItem* groupERMs;
    QTreeWidgetItem* groupCircles;

    void SetStyleFold(styleFold *sf);
    
protected:
    void dropEvent (QDropEvent *event);

public slots:
    void clearOldHandler();
    
};

#endif // KAMALTREE_H
