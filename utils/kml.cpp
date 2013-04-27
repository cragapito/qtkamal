#include "kml.h"
#include "qtpointitem.h"
#include "utils/qxmlputget.h"
#include "utils/networkicon.h"

#include <QDomText>

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
    QDomElement e;

    while ( xmlGet.findNext("Placemark")) {
        e = xmlGet.element();
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
                    pi->element = e;
                    main->sty->setIconStyle(style, pi);
                    main->groupPoints->addChild( pi );
                }
                xmlGet.rise();
            }
        }
        xmlGet.rise();
    }

    *doc = xmlGet.document();

    main->groupPoints->setExpanded(true);

    return true;
}

bool kml::save()
{
    QXmlPut xmlPut = QXmlPut( QXmlGet( *doc ) );
    if (! xmlPut.save("file.kml")) std::cerr << "Falha ao gravar";
    return true;
}

void kml::update(qtpointitem *item)
{
    // Cria estrutura vazia caso não exista nenhuma e atribui ao item.
    if ( item->element.isNull() ) {
        QDomNode docref = doc->firstChildElement("kml").firstChildElement("Document");
        QDomElement place = doc->createElement("Placemark");
        docref.appendChild( place );
        QDomElement elname = doc->createElement("name");
        place.appendChild( elname );
        QDomElement elstyle = doc->createElement("styleUrl");
        place.appendChild( elstyle );
        QDomElement elpoint = doc->createElement("Point");
        place.appendChild( elpoint );
        QDomElement elcoord = doc->createElement("coordinates");
        elpoint.appendChild( elcoord );
        QDomText coorddflt = doc->createTextNode("");
        elcoord.appendChild( coorddflt );
        item->element = place;
    }

    QDomElement tagname = item->element.firstChildElement("name");
    QDomText newname = doc->createTextNode(
                QString::fromStdString( item->pc->name ) );
    tagname.removeChild( tagname.childNodes().at(0) );
    tagname.appendChild( newname );

    QDomElement coord = item->element.firstChildElement("Point");
    coord = coord.firstChildElement("coordinates");
    QDomText newcoord = doc->createTextNode(
                  QString::number( item->pc->y, 'g', 12 )
                + ", "
                + QString::number( item->pc->x, 'g', 12 ) );
    coord.removeChild( coord.childNodes().at(0) );
    coord.appendChild( newcoord );

    this->save();
}

void kml::remove(qtpointitem *item)
{
    item->element.parentNode().removeChild( item->element );
    this->save();
}


