#include "networkicon.h"
#include <iostream>
#include "stylefold.h"

NetworkIcon::NetworkIcon(QIcon *newni)
{
    ni = newni;
    nam = new QNetworkAccessManager();
    connect(nam, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));
}

void NetworkIcon::request(QUrl url)
{
    nam->get(QNetworkRequest(url));
}

void NetworkIcon::finishedSlot(QNetworkReply *reply )
{
    if (reply->error() == QNetworkReply::NoError)
        {
        QImageReader imageReader(reply);
        QImage pic = imageReader.read();
        QIcon i = QIcon(QPixmap::fromImage(pic));
        i.swap( *ni );
        emit requestDone();
    }
    this->~NetworkIcon();
}
