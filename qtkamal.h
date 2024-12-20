#ifndef qtkamal_H
#define qtkamal_H

#include <src/Calc/LinearSolver.h>
#include <utils/qtbeamitem.h>

#include <QList>
#include <QMainWindow>
#include <QTreeWidgetItem>

#include "src/Geo/Beam.h"
#include "utils/stylefold.h"

#include "utils/config.h"

namespace Ui {
class qtkamal;
}

class qtkamal : public QMainWindow {
  Q_OBJECT

private:
  QAction *deleteItemAction;
  QAction *clearOldAction;
  config *cnf;

public:
  explicit qtkamal(QWidget *parent = 0);
  ~qtkamal();

  styleFold *sty;

  QList<qtbeamitem *> *vbeans;

  void args(QStringList args);

protected:
  void dropEvent(QDropEvent *ev);
  void dragEnterEvent(QDragEnterEvent *ev);

private slots:
  void on_actionPnt_triggered();
  void on_actionMan_triggered();
  void on_actionEst_triggered();
  void on_actionCirc_triggered();
  void on_actionGetEarth_triggered();
  void on_actionConfig_triggered();
  void on_actionAbout_triggered();

  void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
  void on_treeWidget_customContextMenuRequested(const QPoint &pos);

  void deleteItemHandler();

  void on_actionTrTarget_triggered();
  void on_actionToCircle_triggered();

public slots:
  void checkTargetFunction();

signals:
  void itemMoved();

private:
  Ui::qtkamal *ui;
};

#endif // QTKAMAL_H
