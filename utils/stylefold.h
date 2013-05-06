#ifndef STYLEFOLD_H
#define STYLEFOLD_H

#include <QMap>
#include <QTreeWidgetItem>
#include "networkicon.h"

class styleFold : public QObject
{
    Q_OBJECT

private:
    QMap<QString, QIcon*>               iconStyle;
    QMap<QString, QString>              mappedStyle;
    QMap<QString, QUrl>                 mappedUrl;

    QMap<QTreeWidgetItem*, QString>     pending;

public:
    QMap<QString, QString>              mappedLineColor;
    QMap<QString, QString>              mappedLineWidth;
    QMap<QString, QString>              mappedPolyColor;

    styleFold();
    void setIconStyle(const QString style, QTreeWidgetItem *wt);
    void addStyle(QString style, QUrl url);
    void addMappedStyle(QString from, QString to);
    QMap<QString, QUrl> getListUrl();

public slots:
    void solvePendingIcons();
};

#endif // STYLEFOLD_H
