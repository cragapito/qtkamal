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
    QWidget *parent;
    QTreeWidget *wtree;
    QString filename;
    QDomDocument *doc;
    qtkamal *main;

public:
    kml(QWidget *parent, QTreeWidget *wt);

    bool readfile(QString name);
};

#endif // KMLPARSER_H
