#ifndef NETWORKICON_H
#define NETWORKICON_H

#include <QUrl>
#include <QHash>
#include <QIcon>
#include <QImageReader>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTreeWidgetItem>
#include <QNetworkAccessManager>

class NetworkIcon : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager* nam;
    QIcon *ni;

public:
    NetworkIcon(QIcon *newni);
    void request(const QUrl url);

private slots:
    void finishedSlot(QNetworkReply*);

signals:
    void requestDone();
};

#endif // NETWORKICON_H
