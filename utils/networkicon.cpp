#include "networkicon.h"

NetworkIcon::NetworkIcon()
{


    iconStyle["sn_man"]         = QIcon(":/icon/res/man.png"            );
    iconStyle["sn_erm"]         = QIcon(":/icon/res/target.png"         );
    iconStyle["sn_cir"]         = QIcon(":/icon/res/open-diamond.png"   );
    iconStyle["sn_place"]       = QIcon(":/icon/res/open-diamond.png"   );
    iconStyle["sn_location"]    = QIcon(":/icon/res/circle.png"         );
}

NetworkIcon::NetworkIcon(QTreeWidgetItem *wt)
{
    wtree = wt;
    nam = new QNetworkAccessManager();
    connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)));
}

void NetworkIcon::request(QUrl url)
{
    nam->get(QNetworkRequest(url));
}

void NetworkIcon::finishedSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
        {
        QImageReader imageReader(reply);
        QImage pic = imageReader.read();
        wtree->setIcon(0, QIcon(QPixmap::fromImage(pic)));
    }
}
