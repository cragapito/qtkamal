#ifndef QTPOINTITEM_H
#define QTPOINTITEM_H

#include <QTreeWidgetItem>
#include <src/Geo/Coordinate.h>


class qtpointitem : public QTreeWidgetItem
{
public:
    qtpointitem(QTreeWidget *parent=0);
    ~qtpointitem();

    Coordinate* pc;
};

#endif // QTPOINTITEM_H
