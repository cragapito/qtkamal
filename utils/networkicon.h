#ifndef NETWORKICON_H
#define NETWORKICON_H

#include <QUrl>
#include <QHash>
#include <QImageReader>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTreeWidgetItem>
#include <QNetworkAccessManager>

class NetworkIcon : public QObject
{
    Q_OBJECT
    QNetworkAccessManager* nam;
    QTreeWidgetItem *wtree;
    QHash<QString, QIcon> iconStyle;

public:
    NetworkIcon();
    NetworkIcon(QTreeWidgetItem *wt);
    void setIcon(QTreeWidgetItem *wt, QString style);
    void request(QUrl url);

private slots:
    void finishedSlot(QNetworkReply* reply);
};

#endif // NETWORKICON_H
