#ifndef QTPOINTITEM_H
#define QTPOINTITEM_H

#include "src/Geo/Coordinate.h"

#include <QtXml>
#include <QTreeWidgetItem>

class qtpointitem : public QTreeWidgetItem
{
public:
    qtpointitem(QTreeWidget *parent = 0);
    virtual ~qtpointitem();

    Coordinate* pc;
    QDomElement element;
    QString     style;

    int open(QWidget *parent);
    void setText( int column, const QString & text ); // Overrided
};

Q_DECLARE_METATYPE(qtpointitem)

#endif // QTPOINTITEM_H
