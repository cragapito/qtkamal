#include "stylefold.h"
#include "networkicon.h"

#include <iostream>

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
    if (reply->error() == QNetworkReply::TimeoutError )
        std::cerr << "Timeout when bringing icon.";

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
