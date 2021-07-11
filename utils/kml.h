#ifndef KMLPARSER_H
#define KMLPARSER_H

#include "kamaltree.h"
#include "utils/qtbeamitem.h"
#include "utils/qtcircleitem.h"
#include "utils/qtpointitem.h"
#include "utils/qxmlputget.h"
#include "utils/stylefold.h"

#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTreeWidget>
#include <QtXml>
#include <iostream>

#ifdef QUAZIP
#include <quazip5/JlCompress.h>
#endif


class kamalTree;

class kml {
private:
  QString filename;
  QString zfilename;
  QTemporaryDir dirtmp;

  QDomDocument *doc;
  styleFold *sty;
  kamalTree *wtree;
  QWidget *parent;

  void parseFolder(QXmlGet xmlGet);
  void parsePlaceMark(QDomElement e, QXmlGet xmlGet);

public:
  kml(QWidget *parent, kamalTree *wt, styleFold *styFold);

  bool readfile();
  bool readfile(const QString name);
  bool save();

  void newFile();
  void addStylesToFile();

  void update(qtbeamitem *item);
  void update(qtpointitem *item);
  void update(qtcircleitem *item);
  void update(QString style, QString modelStyle);

  void kmz2kmltmp();
  void kmltmp2kmz();

  void remove(QTreeWidgetItem *item);

  ~kml();
};

#endif // KMLPARSER_H
