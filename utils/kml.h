#ifndef KMLPARSER_H
#define KMLPARSER_H

#include "qtkamal.h"
#include "utils/qxmlputget.h"

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

    void parseFolder   (QXmlGet xmlGet);
    void parsePlaceMark(QDomElement e , QXmlGet xmlGet);

public:
    kml(QWidget *parent, QTreeWidget *wt);

    bool readfile();
    bool readfile(const QString name);
    bool save();

    void newFile();

    void update (qtbeamitem *item);
    void update (qtpointitem *item);
    void update (qtcircleitem *item);

    void remove (qtpointitem *item);
};

#endif // KMLPARSER_H
