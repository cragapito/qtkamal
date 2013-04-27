#include "kml.h"
#include "qtpointitem.h"
#include "utils/qxmlputget.h"
#include "utils/networkicon.h"

#include <QDomText>
#include <QFileInfo>
#include <QFileDialog>

kml::kml(QWidget *parent, QTreeWidget *wt)
{
    parent = parent;
    wtree = wt;
    main = static_cast<qtkamal*>(parent);
    doc = new QDomDocument;
    filename="";
}

bool kml::readfile()
{
    filename = QFileDialog::getOpenFileName(main, QObject::tr("Abrir arquivo"),
                                                  "",
                                                  QObject::tr("Files (*.kml)"));
    if ( !filename.isEmpty() ) {
        this->readfile( filename );
        return true;
    }
    return false;
}

bool kml::readfile(QString name)
{
    QTreeWidgetItemIterator it( wtree );
    while (*it) {
        if ( (*it)->parent() ) {
            (*it)->setDisabled( true );
        }
        it++;
    }

    QXmlGet xmlGet = QXmlGet();

    if ( !xmlGet.load(name) ){
        QMessageBox::critical( parent, "Erro",
                               "Arquivo não suportado ou corrompido");
        return false;
    }

    filename = name;

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

    xmlGet.findAndDescend("Folder");

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

    this->save();

    return true;
}

bool kml::save()
{
    QString arq;
    QXmlPut xmlPut = QXmlPut( QXmlGet( *doc ) );

    if ( filename.isEmpty() ) {
    filename = QFileDialog::getSaveFileName(main, QObject::tr("Salvar arquivo"),
                                                  "",
                                                  QObject::tr("Files (*.kml)"));
    }

    arq = filename;

    ( filename.endsWith(".kml") )?
        filename.remove( filename.length()-4, 4 ):
        arq.append(".kml");

    if (! xmlPut.save( arq )) {
        QMessageBox::critical( parent,
            "Erro",
            "Não é possível gravar arquivo" + QString(filename) );
        return false;
    }

    return true;
}

void kml::newFile()
{
    QMap<QString, QUrl> styleUrlList = main->sty->getListUrl();
    QString style;

    QXmlPut xmlPut("kml");
    xmlPut.setAttributeString("xmlns","http://www.opengis.net/kml/2.2");
    xmlPut.setAttributeString("xmlns:gx","http://www.google.com/kml/ext/2.2");
    xmlPut.setAttributeString("xmlns:kml","http://www.opengis.net/kml/2.2");
    xmlPut.setAttributeString("xmlns:atom","http://www.w3.org/2005/Atom");
    xmlPut.descend("Document");
    if ( filename.isEmpty() ) this->save();
    xmlPut.putString("name", QString( QFileInfo(filename).fileName() ) );
    wtree->setHeaderLabel(   QString( QFileInfo(filename).fileName() ) );

    foreach ( style, styleUrlList.keys() ) {
        xmlPut.descend("Style");
        xmlPut.setAttributeString("id", style);
        xmlPut.descend("IconStyle");
        xmlPut.descend("Icon");
        xmlPut.putString("href", styleUrlList[style].toString());
        xmlPut.rise();
        xmlPut.putInt("scale", 1);
        xmlPut.rise();
        xmlPut.rise();
    }

    *doc = xmlPut.document();

    this->save();
}

void kml::update(qtpointitem *item)
{
    if ( ! doc->hasChildNodes() ) this->newFile();

    if ( item->isDisabled() ) {
        item->element = QDomElement();
        item->setDisabled( false );
    }

    // Cria estrutura vazia caso não exista nenhuma e atribui ao item.
    if ( item->element.isNull() ) {
        QDomNode docref = doc->firstChildElement("kml").firstChildElement("Document");
        QDomElement place = doc->createElement("Placemark");
        docref.appendChild( place );
        QDomElement elname = doc->createElement("name");
        place.appendChild( elname ); 
        QDomElement elstyle = doc->createElement("styleUrl");
        place.appendChild( elstyle );
        QDomText styledflt = doc->createTextNode("#sn_place"); // Default Point Style
        elstyle.appendChild( styledflt );
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
