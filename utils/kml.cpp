#include "kml.h"
#include "qtpointitem.h"
#include "utils/networkicon.h"

#include <QDomText>
#include <QFileInfo>
#include <QFileDialog>
#include <QApplication>
#include <QTemporaryFile>

kml::kml(QWidget *parent, kamalTree *wt, styleFold *styFold) {
  this->sty = styFold;
  this->doc = new QDomDocument;
  this->wtree = wt;
  this->parent = parent;
  this->filename = "";
  this->zfilename = nullptr;
}

bool kml::readfile() {
  #ifdef QUAZIP
    filename = QFileDialog::getOpenFileName(parent, QObject::tr("Abrir arquivo"), QDir::homePath(),
                                   QObject::tr("Files (*.kml *.kmz)"));
  #else
    filename = QFileDialog::getOpenFileName(parent, QObject::tr("Abrir arquivo"), QDir::homePath(),
                                   QObject::tr("Files (*.kml)"));
  #endif

  QApplication::setOverrideCursor(Qt::WaitCursor);
  if (!filename.isEmpty()) {
    this->readfile(filename);
    QApplication::restoreOverrideCursor();
    return true;
  }
  QApplication::restoreOverrideCursor();
  return false;
}

bool kml::readfile(QString name) {
  // BUG: Ao carregar um arquivo por cima do outro, preservar o primeiro.
  filename = name;

  QString ext = name.right(1);
  if (ext.toLower() == 'z') {
      kmz2kmltmp();
  } else {
      zfilename = nullptr;
  }

  // BUG: Movimentar estes itens leva a segfault, eles estão desabilitados mas são selecionáveis
  QTreeWidgetItemIterator it(wtree);
  while (*it) {
    if ((*it)->parent()) {
      (*it)->setDisabled(true);
    }
    it++;
  }

  QXmlGet xmlGet = QXmlGet();

  if (!xmlGet.load(filename)) {
    QApplication::restoreOverrideCursor();

    QMessageBox::warning(parent, "Aviso",
        "Arquivo não suportado ou corrompido");

    return false;
  }

  if (xmlGet.find("Document")) {
    xmlGet.descend();
    xmlGet = xmlGet.restricted();
  }

  if (xmlGet.find("name"))
    wtree->setHeaderLabel(xmlGet.getString());

  QString style;

  while (xmlGet.findNext("Style")) {
    style = xmlGet.getAttributeString("id");
    xmlGet.descend();
    xmlGet.findAndDescend("IconStyle");
    xmlGet.findAndDescend("Icon");
    xmlGet.find("href");
    sty->addStyle(style, QUrl(xmlGet.getString()));
    xmlGet.rise();
    xmlGet.rise();
    xmlGet.rise();
  }

  while (xmlGet.findNext("StyleMap")) {
    style = xmlGet.getAttributeString("id");
    xmlGet.descend();
    xmlGet.findAndDescend("Pair");
    xmlGet.find("styleUrl");
    if (xmlGet.getString().contains("#")) {
      /*
       * Se o estilo estiver definido em outro local ele
       * estará definido antes do caracter #
       */
      sty->addMappedStyle(style, xmlGet.getString().split("#").at(1));
    }

    xmlGet.rise();
    xmlGet.rise();
  }

  while (xmlGet.findNext("Placemark"))
    parsePlaceMark(xmlGet.element(), xmlGet);

  while (xmlGet.findNext("Folder")) {
    parseFolder(xmlGet);
  }

  *doc = xmlGet.document();

  wtree->groupPoints->setExpanded(true);

  this->save();

  return true;
}

void kml::parseFolder(QXmlGet xmlGet) {
  xmlGet.descend();

  while (xmlGet.findNext("Folder")) {
    parseFolder(xmlGet);
  }

  while (xmlGet.findNext("Placemark")) {
    parsePlaceMark(xmlGet.element(), xmlGet);
  }
}

void kml::parsePlaceMark(QDomElement e, QXmlGet xmlGet) {
  QString placeName;
  QString style;

  xmlGet.descend();
  if (xmlGet.find("name")) {
    placeName = xmlGet.getString();
    xmlGet.findNextAndDescend("styleUrl");

    if (xmlGet.getString().contains("#")) {
      /*
       * Se o estilo estiver definido em outro arquivo (ou url),
       * o endereço estará antes do caracter #
       */
      style = xmlGet.getString().split("#").at(1);
    }
    xmlGet.rise();

    // Point
    while (xmlGet.findNextAndDescend("Point")) {
      if (xmlGet.find("coordinates")) {
        qtpointitem *pi = new qtpointitem();
        QStringList StringList =
            xmlGet.getString().split(","); // longitude, latitude
        pi->setText(0, placeName);

        if (StringList.count() >= 2) {
          pi->pc->x = StringList.at(1).toDouble();
          pi->pc->y = StringList.at(0).toDouble();
          pi->element = e;
        }

        pi->style = style;

        (pi->style.isEmpty()) ? pi->style = "sn_place" : pi->style = style;

        sty->setIconStyle(pi->style, pi);
        wtree->groupPoints->addChild(pi);
      }
      xmlGet.rise();
    }

    // Beam
    while (xmlGet.findNext("MultiGeometry")) {
      qtbeamitem *bi = new qtbeamitem();

      bi->element = e;
      bi->alcance = xmlGet.getAttributeDouble("alcance");
      bi->bm->daz = xmlGet.getAttributeDouble("azimute");

      if (xmlGet.getAttributeInt("tipo")) {
        bi->beamType = bi->ERM;
      } else {
        bi->beamType = bi->MAN;
      }

      xmlGet.descend();
      while (xmlGet.findNextAndDescend("LineString")) {
        if (xmlGet.find("coordinates")) {
          QStringList StringList = xmlGet.getString().split(",");
          bi->setText(0, placeName);

          if (StringList.count() >= 2) {
            bi->bm->source->x = StringList.at(1).toDouble();
            bi->bm->source->y = StringList.at(0).toDouble();
            bi->bm->proj(bi->alcance);
          }

          bi->style = style;
          sty->setIconStyle(style, bi);
          if (bi->beamType == bi->MAN) {
            wtree->groupBeans->addChild(bi);
            wtree->groupBeans->setExpanded(true);
          } else {
            wtree->groupERMs->addChild(bi);
            wtree->groupERMs->setExpanded(true);
          }
        }
        xmlGet.rise();
      }
    }

    // Circle / Section
    while (xmlGet.findNext("Polygon")) {
      qtcircleitem *ci = new qtcircleitem();

      ci->element = e;

      xmlGet.descend();
      xmlGet.findAndDescend("outerBoundaryIs");
      xmlGet.findAndDescend("LinearRing");

      ci->radius = xmlGet.getAttributeDouble("radius");
      ci->points = xmlGet.getAttributeDouble("points");
      ci->azimute = xmlGet.getAttributeDouble("azimute");
      ci->abertura = xmlGet.getAttributeDouble("abertura");
      ci->tipoSelect = xmlGet.getAttributeInt("tipo");

      ci->setText(0, placeName);

      QStringList StringList = xmlGet.getAttributeString("center").split(", ");

      if (StringList.count() >= 2) {
        ci->center->x = StringList.at(1).toDouble();
        ci->center->y = StringList.at(0).toDouble();
        ci->calc();
      }

      wtree->groupCircles->addChild(ci);
      sty->setIconStyle(style, ci);
      wtree->groupCircles->setExpanded(true);
    }
  }
  xmlGet.rise();
}

bool kml::save() {
  QXmlPut xmlPut = QXmlPut(QXmlGet(*doc));

  if (filename.isEmpty()) {
    #ifdef QUAZIP
      filename = QFileDialog::getSaveFileName(parent, QObject::tr("Salvar arquivo"), QDir::homePath(),
                                   QObject::tr("Files (*.kml *.kmz)"));
    #else
      filename = QFileDialog::getSaveFileName(parent, QObject::tr("Salvar arquivo"), QDir::homePath(),
                                   QObject::tr("Files (*.kml)"));
    #endif
  }

  QApplication::setOverrideCursor(Qt::WaitCursor);

  // NOTE: Verificar implicações de não salvar o arquivo "Sem nome" (usuário cancelando o diálogo).
  // Cada alteração solicitará o diálogo novamente e não há outra forma de salvar.
  if (filename.isEmpty()) {
      QApplication::restoreOverrideCursor();
      return false;
      filename = "Sem nome";
  }

  if ( filename.right(4).chopped(1).toUpper() != ".KM" ){
    filename.append(".kmz");
  }

  QString ext = filename.right(1);
  if (ext.toLower() == 'z') {
      kmz2kmltmp();
  }

  addStylesToFile();

  QString fname;
  (zfilename == NULL) ? fname = QString(QFileInfo(filename).baseName())
                      : fname = QString(QFileInfo(zfilename).baseName());
  // The extra firstChild() call which will actually access the text node and enable you to change the value
  doc->firstChildElement("kml").firstChildElement("Document").firstChildElement("name").firstChild().setNodeValue( fname );
  wtree->setHeaderLabel(fname);

  if (!xmlPut.save( filename )) {
    QApplication::restoreOverrideCursor();
    QApplication::restoreOverrideCursor(); // Sem a segunda chamada o cursor permanece ocupado.
    QMessageBox::critical(parent, "Erro",
                          "Não foi possível gravar arquivo" + QString(filename));
    QApplication::quit();
  }

  if ( zfilename != NULL ) {
      kmltmp2kmz();
  }

  QApplication::restoreOverrideCursor();
  return true;
}

void kml::newFile() {
  QXmlPut xmlPut("kml");
  xmlPut.setAttributeString("xmlns", "http://www.opengis.net/kml/2.2");
  xmlPut.setAttributeString("xmlns:gx", "http://www.google.com/kml/ext/2.2");
  xmlPut.setAttributeString("xmlns:kml", "http://www.opengis.net/kml/2.2");
  xmlPut.setAttributeString("xmlns:atom", "http://www.w3.org/2005/Atom");
  xmlPut.descend("Document");
  // NOTE: Verificar implicações de não salvar o arquivo se vazio.
  //if (filename.isEmpty())
  //  this->save();

  QString fname;
  ( zfilename == NULL )?
      fname = filename:
      fname = zfilename;
  xmlPut.putString("name", QString(QFileInfo(fname).baseName()));
  wtree->setHeaderLabel(QString(QFileInfo(fname).baseName()));

  addStylesToFile();

  *doc = xmlPut.document();

  // NOTE: Verificar implicações de não salvar o arquivo novo.
  //this->save();
}

void kml::addStylesToFile() {
  QXmlGet xmlGet = QXmlGet(*doc);

  if (xmlGet.find("Document")) {
    xmlGet.descend();
    xmlGet = xmlGet.restricted();
  }

  QXmlPut xmlPut = QXmlPut(xmlGet);

  while (xmlGet.findNext("Style")) {
    QString styleTest = xmlGet.getAttributeString("id");
    if (sty->isInternalStyle(styleTest)) {
      return; // Já contém os estilos internos
    }
  }

  foreach (QString style, sty->mappedUrl.keys()) {
    xmlPut.descend("Style");
    xmlPut.setAttributeString("id", style);
    xmlPut.descend("IconStyle");
    xmlPut.descend("Icon");
    xmlPut.putString("href", sty->mappedUrl[style].toString());
    xmlPut.rise();
    xmlPut.putInt("scale", 1);
    xmlPut.rise();
    if (sty->mappedLineColor.contains(style)) {
      xmlPut.descend("LineStyle");
      xmlPut.putString("color", sty->mappedLineColor[style]);
      xmlPut.putString("width", sty->mappedLineWidth[style]);
      xmlPut.rise();
    }
    if (sty->mappedPolyColor.contains(style)) {
      xmlPut.descend("PolyStyle");
      xmlPut.putString("color", sty->mappedPolyColor[style]);
      xmlPut.rise();
    }
    xmlPut.rise();
  }
}

void kml::update(qtbeamitem *item) {
  if (!doc->hasChildNodes())
    this->newFile();

  if (item->isDisabled()) {
    item->element = QDomElement();
    item->setDisabled(false);
  }

  // Cria estrutura vazia caso não exista nenhuma e atribui ao item.
  if (item->element.isNull()) {
    QDomNode docref =
        doc->firstChildElement("kml").firstChildElement("Document");
    QDomElement placemark = doc->createElement("Placemark");
    docref.appendChild(placemark);
    QDomElement name = doc->createElement("name");
    placemark.appendChild(name);
    QDomElement styleurl = doc->createElement("styleUrl");
    placemark.appendChild(styleurl);
    QDomText style;
    if (item->beamType == item->MAN)
      style = doc->createTextNode("#sn_man");
    if (item->beamType == item->ERM)
      style = doc->createTextNode("#sn_erm");
    styleurl.appendChild(style);
    QDomElement multigeometry = doc->createElement("MultiGeometry");
    placemark.appendChild(multigeometry);
    QDomElement linesource = doc->createElement("Point");
    multigeometry.appendChild(linesource);
    QDomElement coordinates = doc->createElement("coordinates");
    linesource.appendChild(coordinates);
    QDomElement linestring = doc->createElement("LineString");
    multigeometry.appendChild(linestring);
    QDomElement tessellate = doc->createElement("tessellate");
    linestring.appendChild(tessellate);
    tessellate.appendChild(doc->createTextNode("1"));
    QDomElement linecoord = doc->createElement("coordinates");
    linestring.appendChild(linecoord);
    item->element = placemark;
  }

  QDomElement tagname = item->element.firstChildElement("name");
  QDomText newname =
      doc->createTextNode(QString::fromStdString(item->bm->source->name));
  tagname.removeChild(tagname.childNodes().at(0));
  tagname.appendChild(newname);

  QDomElement tagstyle = item->element.firstChildElement("styleUrl");
  QDomText newstyle;
  if (sty->isInternalStyle(item->style) || item->style.isEmpty()) {
    if (item->beamType == item->MAN)
      newstyle = doc->createTextNode("#sn_man");
    if (item->beamType == item->ERM)
      newstyle = doc->createTextNode("#sn_erm");
  } else {
    newstyle = doc->createTextNode(QString("#") + item->style);
  }
  tagstyle.removeChild(tagstyle.childNodes().at(0));
  tagstyle.appendChild(newstyle);

  QDomElement multi = item->element.firstChildElement("MultiGeometry");

  multi.setAttribute("tipo", QString::number(item->beamType));
  multi.setAttribute("alcance", QString::number(item->alcance));
  multi.setAttribute("azimute", QString::number(item->bm->daz));

  QDomElement coordsource = multi.firstChildElement("Point");
  coordsource = coordsource.firstChildElement("coordinates");
  QDomText newcoordsource =
      doc->createTextNode(QString::number(item->bm->source->y, 'g', 12) + ", " +
                          QString::number(item->bm->source->x, 'g', 12));
  coordsource.removeChild(coordsource.childNodes().at(0));
  coordsource.appendChild(newcoordsource);

  QDomElement coord = multi.firstChildElement("LineString");
  coord = coord.firstChildElement("coordinates");
  QDomText newcoord = doc->createTextNode(
      QString::number(item->bm->source->y, 'g', 12) + "," +
      QString::number(item->bm->source->x, 'g', 12) + ",0 " +
      QString::number(item->bm->scope->y, 'g', 12) + "," +
      QString::number(item->bm->scope->x, 'g', 12) + ",0 ");
  coord.removeChild(coord.childNodes().at(0));
  coord.appendChild(newcoord);

  this->save();
}

void kml::update(qtpointitem *item) {
  if (!doc->hasChildNodes())
    this->newFile();

  if (item->isDisabled()) {
    item->element = QDomElement();
    item->setDisabled(false);
  }

  // Cria estrutura vazia caso não exista nenhuma e atribui ao item.
  if (item->element.isNull()) {
    QDomNode docref =
        doc->firstChildElement("kml").firstChildElement("Document");
    QDomElement placemark = doc->createElement("Placemark");
    docref.appendChild(placemark);
    QDomElement name = doc->createElement("name");
    placemark.appendChild(name);
    QDomElement styleurl = doc->createElement("styleUrl");
    placemark.appendChild(styleurl);
    QDomText style = doc->createTextNode("#sn_place"); // Default Point Style
    styleurl.appendChild(style);
    QDomElement point = doc->createElement("Point");
    placemark.appendChild(point);
    QDomElement coordinates = doc->createElement("coordinates");
    point.appendChild(coordinates);
    item->element = placemark;
  }

  QDomElement tagname = item->element.firstChildElement("name");
  QDomText newname =
      doc->createTextNode(QString::fromStdString(item->pc->name));
  tagname.removeChild(tagname.childNodes().at(0));
  tagname.appendChild(newname);

  QDomElement tagstyle = item->element.firstChildElement("styleUrl");
  QDomText newstyle = doc->createTextNode("#" + item->style);
  tagstyle.removeChild(tagstyle.childNodes().at(0));
  tagstyle.appendChild(newstyle);

  QDomElement coord = item->element.firstChildElement("Point");
  coord = coord.firstChildElement("coordinates");
  QDomText newcoord =
      doc->createTextNode(QString::number(item->pc->y, 'g', 12) + ", " +
                          QString::number(item->pc->x, 'g', 12));
  coord.removeChild(coord.childNodes().at(0));
  coord.appendChild(newcoord);

  this->save();
}

void kml::update(qtcircleitem *item) {
  if (!doc->hasChildNodes())
    this->newFile();

  if (item->isDisabled()) {
    item->element = QDomElement();
    item->setDisabled(false);
  }

  // Cria estrutura vazia caso não exista nenhuma e atribui ao item.
  if (item->element.isNull()) {
    QDomNode docref =
        doc->firstChildElement("kml").firstChildElement("Document");
    QDomElement place = doc->createElement("Placemark");
    docref.appendChild(place);
    QDomElement elname = doc->createElement("name");
    place.appendChild(elname);
    QDomElement elstyle = doc->createElement("styleUrl");
    place.appendChild(elstyle);
    QDomText styledflt = doc->createTextNode("#sn_cir"); // Default Circle Style
    elstyle.appendChild(styledflt);
    QDomElement elpol = doc->createElement("Polygon");
    place.appendChild(elpol);
    QDomElement bound = doc->createElement("outerBoundaryIs");
    elpol.appendChild(bound);
    QDomElement ring = doc->createElement("LinearRing");
    bound.appendChild(ring); // TODO: Usar elemento google-pro circle
    QDomElement coords = doc->createElement("coordinates");
    ring.appendChild(coords);
    item->element = place;
  }

  QDomElement tagname = item->element.firstChildElement("name");
  QDomText newname =
      doc->createTextNode(QString::fromStdString(item->center->name));
  tagname.removeChild(tagname.childNodes().at(0));
  tagname.appendChild(newname);

  QDomElement coord = item->element.firstChildElement("Polygon");
  coord = coord.firstChildElement("outerBoundaryIs");
  coord = coord.firstChildElement("LinearRing");
  coord.setAttribute("tipo", item->tipoSelect);
  coord.setAttribute("radius", item->radius);
  coord.setAttribute("points", item->points);
  coord.setAttribute("azimute", item->azimute);
  coord.setAttribute("abertura", item->abertura);
  coord.setAttribute("center", QString::number(item->center->y, 'g', 12) +
                                   ", " +
                                   QString::number(item->center->x, 'g', 12));
  coord = coord.firstChildElement("coordinates");
  QDomText newcoord = doc->createTextNode(item->perimeter);
  coord.removeChild(coord.childNodes().at(0));
  coord.appendChild(newcoord);

  this->save();
}

void kml::update(QString style, QString modelStyle) {
  QXmlGet xmlGet = QXmlGet(*doc);
  QDomElement e = QDomElement();

  if (xmlGet.find("Document")) {
    xmlGet.descend();
    xmlGet = xmlGet.restricted();
  }

  if (sty->mappedStyle[style].contains(style)) {
    style = sty->mappedStyle[style];
  }

  while (xmlGet.findNext("Style")) {
    QString styleTest = xmlGet.getAttributeString("id");
    if (styleTest == style) {
      styleTest = style;
      e = xmlGet.element();
    }
  }

  QXmlPut xmlPut = QXmlPut(xmlGet);

  if (e.isNull()) {
    xmlPut.descend("Style");
    xmlPut.setAttributeString("id", style);
    xmlPut.descend("IconStyle");
    xmlPut.descend("Icon");
    xmlPut.putString("href", sty->mappedUrl[style].toString());
    xmlPut.rise();
    xmlPut.putInt("scale", 1);
    xmlPut.rise();
  } else {
    xmlGet.goTo(e);
    xmlGet.findAndDescend("Style");
    e = xmlGet.element();
  }

  if (sty->mappedLineColor.contains(modelStyle)) {

    QDomElement lineStyle;

    if (!xmlGet.findNext("LineStyle")) {
      lineStyle = doc->createElement("LineStyle");
      e.appendChild(lineStyle);
    } else {
      lineStyle = e.firstChildElement("LineStyle");
      lineStyle.removeChild(lineStyle.firstChild());
      lineStyle.removeChild(lineStyle.firstChild());
    }

    QDomElement ecolor = doc->createElement("color");
    QDomElement ewidth = doc->createElement("width");
    QDomText newcolor = doc->createTextNode(sty->mappedLineColor[modelStyle]);
    QDomText newwidth = doc->createTextNode(sty->mappedLineWidth[modelStyle]);
    ecolor.appendChild(newcolor);
    ewidth.appendChild(newwidth);
  }

  if (sty->mappedPolyColor.contains(modelStyle)) {

    QDomElement polyStyle;

    if (!xmlGet.findNext("PolyStyle")) {
      polyStyle = doc->createElement("PolyStyle");
      e.appendChild(polyStyle);
    } else {
      polyStyle = e.firstChildElement("PolyStyle");
      polyStyle.removeChild(polyStyle.firstChild());
    }

    QDomElement pcolor = doc->createElement("color");
    QDomText newpolycolor =
        doc->createTextNode(sty->mappedLineColor[modelStyle]);
    pcolor.appendChild(newpolycolor);
  }

  *doc = xmlPut.document();

  this->save();
}

void kml::kmz2kmltmp() {
  this->zfilename = this->filename;

  filename.replace(QString("kmz"), QString("kml"));

  if (dirtmp.isValid()) {
    filename = dirtmp.path() + QDir::separator() + QFileInfo(this->filename).fileName();
  } else {
    QApplication::restoreOverrideCursor();
    QMessageBox::critical(parent, "Erro",
                          "Falha ao criar pasta de trabalho temporária.");
    QApplication::quit();
  }

#ifdef QUAZIP

  QuaZip zip( this->filename );

  qDebug() << "Original file " << zfilename;
  qDebug() << "Working on " << filename;

  JlCompress::extractDir( zfilename, dirtmp.path() );
#else
  qDebug() << "Quazip option was not compiled!";
  QMessageBox::critical(parent, "Erro",
                            "Esta versão não foi compilada com suporte a kmz!");
#endif
}

void kml::kmltmp2kmz() {
#ifdef QUAZIP
  JlCompress::compressDir( zfilename, dirtmp.path() + QDir::separator() );
  qDebug() << "Writting " << zfilename;
#endif
}

void kml::remove(QTreeWidgetItem *item) {
  QDomElement e;

  if (dynamic_cast<qtpointitem *>(item)) {
    e = dynamic_cast<qtpointitem *>(item)->element;
  }

  if (dynamic_cast<qtbeamitem *>(item)) {
    e = dynamic_cast<qtbeamitem *>(item)->element;
  }

  if (dynamic_cast<qtcircleitem *>(item)) {
    e = dynamic_cast<qtcircleitem *>(item)->element;
  }

  e.parentNode().removeChild(e);

  this->save();
}

kml::~kml()
{
    dirtmp.remove();
}
