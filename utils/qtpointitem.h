#ifndef QTPOINTITEM_H
#define QTPOINTITEM_H

#include <QTreeWidgetItem>
#include <src/Geo/Coordinate.h>


class qtpointitem : public QTreeWidgetItem
{
public:
    qtpointitem(QTreeWidget *parent = 0);
    ~qtpointitem();

    Coordinate* pc;

    void open(QWidget *parent);
};

Q_DECLARE_METATYPE(qtpointitem)

#endif // QTPOINTITEM_H
