#ifndef STYLEFOLD_H
#define STYLEFOLD_H

#include <QMap>
#include <QTreeWidgetItem>
#include "networkicon.h"

class styleFold : public QObject
{
    Q_OBJECT

    QMap<QString, QIcon*>               iconStyle;
    QMap<QString, QUrl>                 mappedUrl;
    QMap<QString, QString>              mappedStyle;

    QMap<QTreeWidgetItem*, QString>     pending;

public:
    styleFold();
    void setIconStyle(const QString style, QTreeWidgetItem *wt);
    void addStyle(QString style, QUrl url);
    void addMappedStyle(QString from, QString to);
    QMap<QString, QUrl> getListUrl();

public slots:
    void solvePendingIcons();
};

#endif // STYLEFOLD_H
