#include "kml.h"
#include "qtpointitem.h"
#include "utils/qxmlputget.h"
#include "utils/networkicon.h"

kml::kml(QWidget *parent, QTreeWidget *wt)
{
    parent = parent;
    wtree = wt;
    main = static_cast<qtkamal*>(parent);
    doc = new QDomDocument;
}

bool kml::readfile(QString name)
{
    QXmlGet xmlGet;

    if ( !xmlGet.load(name) ){
        QMessageBox::critical( parent, "Erro", "Arquivo não suportado ou corrompido");
        return false;
    }

    if (xmlGet.find("Document")) {
        xmlGet.descend();
        xmlGet = xmlGet.restricted();
    }

    if (xmlGet.find("name"))
        wtree->setHeaderLabel( xmlGet.getString() );

    QString style;

    while ( xmlGet.findNext("Style")) {
        style = xmlGet.getAttributeString("id");
        xmlGet.descend();
        xmlGet.findAndDescend("IconStyle");
        xmlGet.findAndDescend("Icon");
        xmlGet.find("href");
        main->sty->addStyle(style, QUrl(xmlGet.getString()));
        xmlGet.rise();
        xmlGet.rise();
        xmlGet.rise();
    }

    while ( xmlGet.findNext("StyleMap")) {
        style = xmlGet.getAttributeString("id");
        xmlGet.descend();
        xmlGet.findAndDescend("Pair");
        xmlGet.find("styleUrl");
        main->sty->addMappedStyle( style, xmlGet.getString().remove(0,1) );
        xmlGet.rise();
        xmlGet.rise();
    }

    QString placeName;

    while ( xmlGet.findNext("Placemark")) {
        xmlGet.descend();
        if (xmlGet.find("name")) {
            placeName = xmlGet.getString();
            xmlGet.findAndDescend("styleUrl");
            style = xmlGet.getString().remove(0,1); // Remove o # da styleUrl
            xmlGet.rise();
            while (xmlGet.findNext("Point")) {
                xmlGet.descend();
                if (xmlGet.find("coordinates")) {
                    qtpointitem *pi = new qtpointitem();
                    QStringList StringList = xmlGet.getString().split(","); // longitude, latitude
                    pi->setText(0, placeName) ;
                    pi->pc->x = StringList.at(1).toDouble();
                    pi->pc->y = StringList.at(0).toDouble();
                    main->sty->setIconStyle(style, pi);
                    main->groupPoints->addChild( pi );
                }
                xmlGet.rise();
            }
        }
        xmlGet.rise();
    }

    main->groupPoints->setExpanded(true);

    return true;
}
