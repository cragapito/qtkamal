#ifndef KMLPARSER_H
#define KMLPARSER_H

#include "kamaltree.h"
#include "utils/stylefold.h"
#include "utils/qxmlputget.h"
#include "utils/qtbeamitem.h"
#include "utils/qtpointitem.h"
#include "utils/qtcircleitem.h"

#include <QFile>
#include <QtXml>
#include <QString>
#include <iostream>
#include <QTreeWidget>
#include <QMessageBox>

class kamalTree;

class kml
{
private:
    QString         filename;

    QDomDocument    *doc;
    styleFold       *sty;
    kamalTree       *wtree;
    QWidget         *parent;

    void parseFolder   (QXmlGet xmlGet);
    void parsePlaceMark(QDomElement e , QXmlGet xmlGet);

public:
    kml(QWidget *parent, kamalTree *wt, styleFold *styFold);

    bool readfile();
    bool readfile(const QString name);
    bool save();

    void newFile();

    void update (qtbeamitem *item);
    void update (qtpointitem *item);
    void update (qtcircleitem *item);
    void update (QString style, QString modelStyle);

    void remove (QTreeWidgetItem *item);
};

#endif // KMLPARSER_H
