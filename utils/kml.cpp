#include "kml.h"
#include "qtpointitem.h"
#include "utils/qxmlputget.h"

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
        QMessageBox::critical( parent, "Erro", "Formato de arquivo não suportado ou corrompido");
        return false;
    }

    if ( xmlGet.xmlDeclaration() != "kml" ) {
        QMessageBox::critical( parent, "Erro", "Não é um arquivo kml válido" );
        return false;
    }

    if (xmlGet.find("Document")) {
        xmlGet.descend();
        xmlGet = xmlGet.restricted();
    }

    if (xmlGet.find("name"))
        wtree->setHeaderLabel( xmlGet.getString() );

    QString placeName;

    while ( xmlGet.findNext("Placemark")) {
        xmlGet.descend();
        if (xmlGet.find("name")) {
            placeName = xmlGet.getString();
            while (xmlGet.findNext("Point")) {
                xmlGet.descend();
                if (xmlGet.find("coordinates")) {
                    qtpointitem *pi = new qtpointitem();
                    QStringList StringList = xmlGet.getString().split(","); // longitude, latitude
                    pi->setText(0, placeName );
                    pi->pc->x = StringList.at(1).toDouble();
                    pi->pc->y = StringList.at(0).toDouble();
                    pi->setIcon(0, QIcon(":/icon/res/open-diamond.png"));
                    main->groupPoints->addChild( pi );
                }
                xmlGet.rise();
            }
        }
        xmlGet.rise();
    }

    main->groupPoints->setExpanded(true);

    /*
    filename = name;
    QFile file(filename);

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc->setContent( &file, false, &errorStr, &errorLine, &errorColumn )) {
            std::cerr << "Error: Parse error at line " << errorLine << ", "
                  << "column " << errorColumn << ": "
                  << qPrintable(errorStr) << std::endl;
            QMessageBox::critical( parent, "Erro", "Documento mal formado");
            return false;
    }

    QDomElement root = doc->documentElement();

    if (root.tagName() != "kml") {
        std::cerr << "Error: Not a kml file" << std::endl;
        QMessageBox::critical( parent, "Erro", "Não é um arquivo kml");
        return false;
    }

    // O primeiro nó filho é <Document>
    QDomNode child = root.firstChild().firstChild();

    while (!child.isNull()) {
            if (child.toElement().tagName() == "name") {
                wtree->setHeaderLabel( child.toElement().text() );
                break;
            }
            child = child.nextSibling();
    }

    while (!child.isNull()) {
            if (child.toElement().tagName() == "Placemark") {
                parsePlacemark(child.toElement());
            }
            child = child.nextSibling();
    }

    file.close();
    */

    return true;
}

void kml::parsePlacemark(const QDomElement &element)
{
    // Importa nomes para o treeWidget
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
            if (child.toElement().tagName() == "name") {
                qtpointitem *pi = new qtpointitem();
                pi->setText(0, child.toElement().text());
                main->groupPoints->addChild( pi );
            }
            child = child.nextSibling();
    }
    main->groupPoints->setExpanded( true );
}

/* TODO implementar função setIcon em kml.cpp
 *
 *Adicionar QT += network no .pro
 *
 *
bool kml::setIcon(QUrl url, QTreeWidgetItem *w)
{

    QNetworkAccessManager* nam = new QNetworkAccessManager;
    QNetworkReply* reply = nam->get(QNetworkRequest(url));
    if (reply->error() == QNetworkReply::NoError) {
        QImageReader imageReader(reply);
        QImage pic = imageReader.read();
        qDebug() << imageReader.errorString();
        // "Unsupported image format"
        w->setIcon(0, QIcon(QPixmap::fromImage(pic)));
        return true;
    }

    std::cerr << "Função setIcon de kml.cpp não implementada";
    return false;
}
*/
