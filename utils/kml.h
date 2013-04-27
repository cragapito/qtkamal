#ifndef KMLPARSER_H
#define KMLPARSER_H

#include "qtkamal.h"

#include <QFile>
#include <QtXml>
#include <QString>
#include <iostream>
#include <QTreeWidget>
#include <QMessageBox>

class kml
{
    QString         filename;

    QDomDocument    *doc;
    qtkamal         *main;
    QTreeWidget     *wtree;
    QWidget         *parent;

public:
    kml(QWidget *parent, QTreeWidget *wt);

    bool readfile(const QString name);
    bool save();

    void update (qtpointitem *item);
    void remove (qtpointitem *item);
};

#endif // KMLPARSER_H
