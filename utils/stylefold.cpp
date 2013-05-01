#include <iostream>
#include <QDebug>
#include "stylefold.h"

styleFold::styleFold()
{
    iconStyle.insert("sn_man",      new QIcon(":/icon/res/man.png")             );
    iconStyle.insert("sn_erm",      new QIcon(":/icon/res/target.png")          );
    iconStyle.insert("sn_cir",      new QIcon(":/icon/res/circle.png")          );
    iconStyle.insert("sn_place",    new QIcon(":/icon/res/open-diamond.png")    );
    iconStyle.insert("sn_location", new QIcon(":/icon/res/open-diamond.png")    );

    mappedUrl.insert("sn_man",      QUrl("http://maps.google.com/mapfiles/kml/shapes/man.png")              );
    mappedUrl.insert("sn_erm",      QUrl("http://maps.google.com/mapfiles/kml/shapes/target.png")           );
    mappedUrl.insert("sn_cir",      QUrl("http://maps.google.com/mapfiles/kml/shapes/open-diamond.png")     );
    mappedUrl.insert("sn_place",    QUrl("http://maps.google.com/mapfiles/kml/shapes/open-diamond.png")     );
    mappedUrl.insert("sn_location", QUrl("http://maps.google.com/mapfiles/kml/shapes/placemark_circle.png") );
}

void styleFold::setIconStyle(const QString style, QTreeWidgetItem *wt)
{
    if ( !iconStyle.contains(style) ) {
        std::cerr << "Ícone para estilo '" + style.toStdString() + "'' não definido." << std::endl;
        return;
    }

    if ( ! iconStyle[style]->isNull() ) {
        wt->setIcon(0, *iconStyle[style]);
        return;
    }

    pending.insert(wt, style);
}

void styleFold::addStyle(QString style, QUrl url)
{
    if ( iconStyle.contains(style) ) return;

    mappedUrl.insert(style, url);

    QIcon *ntwi = new QIcon();
    iconStyle.insert(style, ntwi);
    NetworkIcon *ni = new NetworkIcon( ntwi );
    ni->request(url);
    connect( ni, SIGNAL(requestDone()), this, SLOT(solvePendingIcons()) );
}

void styleFold::addMappedStyle(QString from, QString to)
{
    if ( mappedStyle.contains( from )) return;

    mappedStyle.insert(from, to);
    addStyle(from, mappedUrl.value(to));
    std::cerr << "Mapeando estilo "
                 + from.toStdString()
                 + " para "
                 + to.toStdString() << std::endl;
}

QMap<QString, QUrl> styleFold::getListUrl()
{
     return mappedUrl;
}

void styleFold::solvePendingIcons()
{
    foreach ( QTreeWidgetItem* wt, pending.keys() ) {
        QString style = pending.value( wt );

        if ( iconStyle[ style ] ) {
            setIconStyle( style, wt );
            if ( ! iconStyle[style]->isNull() )
                pending.remove(wt);
        }
    }
}
