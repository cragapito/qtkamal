#ifndef QTPOINTITEM_H
#define QTPOINTITEM_H

#include <QtXml>
#include <QTreeWidgetItem>
#include <src/Geo/Coordinate.h>

class qtpointitem : public QTreeWidgetItem
{
public:
    qtpointitem(QTreeWidget *parent = 0);
    ~qtpointitem();

    Coordinate* pc;
    QDomElement element;

    void open(QWidget *parent);
    void setText( int column, const QString & text ); // Overrided
};

Q_DECLARE_METATYPE(qtpointitem)

#endif // QTPOINTITEM_H
