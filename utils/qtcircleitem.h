#ifndef QTCIRCLEITEM_H
#define QTCIRCLEITEM_H

#include "src/Geo/Coordinate.h"

#include <QtXml>
#include <QTreeWidgetItem>

class qtcircleitem : public QTreeWidgetItem
{
public:
    qtcircleitem(QTreeWidget *parent = 0);
    virtual ~qtcircleitem();

    Coordinate* center;
    double      radius;
    double      points;
    QDomElement element;

    int open(QWidget *parent);
    void setText( int column, const QString & text ); // Overrided
};

Q_DECLARE_METATYPE(qtcircleitem)

#endif // QTCIRCLEITEM_H
