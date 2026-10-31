#include "stylefold.h"
#include "networkicon.h"

#include <iostream>

NetworkIcon::NetworkIcon(QIcon *newni)
{
    ni = newni;
    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));
}

void NetworkIcon::request(QUrl url)
{
    if ( ! url.isEmpty() )
        nam->get(QNetworkRequest(url));
}

void NetworkIcon::finishedSlot(QNetworkReply *reply )
{
    if (reply->error() != QNetworkReply::NoError ) {
        std::cerr << "Error bringing icon: " << reply->errorString().toStdString() << std::endl;
    } else {
        QImageReader imageReader(reply);
        QImage pic = imageReader.read();
        QIcon i = QIcon(QPixmap::fromImage(pic));
        i.swap( *ni );
        emit requestDone();
    }
    // Libera a resposta de rede e agenda a exclusão segura do objeto pelo loop de eventos do Qt
    reply->deleteLater();
    this->deleteLater();
}
