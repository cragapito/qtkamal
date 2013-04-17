#ifndef KMLPARSER_H
#define KMLPARSER_H

#include "qtkamal.h"


#include <QFile>
#include <QtXml>
#include <QString>
#include <iostream>
#include <QTreeWidget>
#include <QMessageBox>
#include <QImageReader>

// Para a função setIcon em kml.cpp
//#include <QUrl>
//#include <QNetworkReply>
//#include <QNetworkRequest>
//#include <QNetworkAccessManager>

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
    void parsePlacemark(const QDomElement &element);

    //bool setIcon(QUrl url, QTreeWidgetItem *w);
};

#endif // KMLPARSER_H
