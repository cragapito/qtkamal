#ifndef QTBEAMITEM_H
#define QTBEAMITEM_H

#include "src/Geo/Beam.h"

#include <QtXml>
#include <QString>
#include <QTreeWidgetItem>

class qtbeamitem : public QTreeWidgetItem
{
public:
    qtbeamitem(QTreeWidget *parent = 0);
    virtual ~qtbeamitem();

    Beam*       bm;
    double      alcance;
    QDomElement element;

    enum        TYPE { MAN, ERM };
    TYPE        beamType;

    int open(QWidget *parent);
    void setText( int column, const QString & text ); // Overrided
};

Q_DECLARE_METATYPE(qtbeamitem)

#endif // QTBEAMITEM_H
