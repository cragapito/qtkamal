#include "qtkamal.h"
#include "utils/kml.h"
#include "ui_qtkamal.h"
#include "dialogs/point.h"
#include "dialogs/beamdialog.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/circledialog.h"

#include <QUrl>
#include <QList>
#include <QDropEvent>

qtkamal::qtkamal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtkamal)
{
    ui->setupUi(this);
    sty = new styleFold();
    map = new kml( this, ui->treeWidget );

    groupPoints  = new QTreeWidgetItem();
    groupBeans   = new QTreeWidgetItem();
    groupERMs    = new QTreeWidgetItem();
    groupCircles = new QTreeWidgetItem();

    ui->treeWidget->addTopLevelItem(groupPoints );
    ui->treeWidget->addTopLevelItem(groupBeans  );
    ui->treeWidget->addTopLevelItem(groupERMs   );
    ui->treeWidget->addTopLevelItem(groupCircles);

    groupPoints->setIcon    (0, QIcon(":/icon/res/open-diamond.png" ));
    groupBeans->setIcon     (0, QIcon(":/icon/res/man.png"          ));
    groupERMs->setIcon      (0, QIcon(":/icon/res/target.png"       ));
    groupCircles->setIcon   (0, QIcon(":/icon/res/circle.png"       ));

    groupPoints->setText    (0, tr("Pontos"             ));
    groupBeans->setText     (0, tr("Feixes Manuais"     ));
    groupERMs->setText      (0, tr("Feixes de Estação"  ));
    groupCircles->setText   (0, tr("Círculos"           ));

    // disable dropping of leaves as top level items
    ui->treeWidget->invisibleRootItem()->setFlags(    Qt::ItemIsSelectable
                          | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled         );
    // top level itens
    groupPoints->setFlags ( Qt::ItemIsSelectable    | Qt::ItemIsUserCheckable
                          | Qt::ItemIsDropEnabled   | Qt::ItemIsEnabled         );
    groupBeans->setFlags  ( Qt::ItemIsSelectable    | Qt::ItemIsUserCheckable
                          | Qt::ItemIsDropEnabled   | Qt::ItemIsEnabled         );
    groupERMs->setFlags   ( Qt::ItemIsSelectable    | Qt::ItemIsUserCheckable
                          | Qt::ItemIsDropEnabled   | Qt::ItemIsEnabled         );
    groupCircles->setFlags( Qt::ItemIsSelectable    | Qt::ItemIsUserCheckable
                          | Qt::ItemIsDropEnabled   | Qt::ItemIsEnabled         );
}

qtkamal::~qtkamal()
{
    delete ui;
}

void qtkamal::dropEvent(QDropEvent *ev)
{
    QList<QUrl> urls = ev->mimeData()->urls();
    foreach(QUrl url, urls)
    {    
        map->readfile( url.toLocalFile() );
    }
}

void qtkamal::dragEnterEvent(QDragEnterEvent *ev)
{
    QList<QUrl> urls = ev->mimeData()->urls();
    foreach(QUrl url, urls) {
        qDebug() << url.toString();
        if (QFileInfo(url.toLocalFile()).suffix().toUpper() != "KML") {
            return;
        }
    }
    ev->accept();
}

void qtkamal::on_actionPnt_triggered()
{
    point *pd = new point();
    int result = pd->exec();

    if (result == QDialog::Accepted) {
        groupPoints->setExpanded( true );
        groupPoints->addChild( pd->pi );
        if ( pd->pi->element.isNull() ) {
            sty->setIconStyle( "sn_place", pd->pi );
            map->update( pd->pi );
        }
    }
}

void qtkamal::on_actionMan_triggered()
{
    beamDialog *bd = new beamDialog();
    int result = bd->exec();

    if (result == QDialog::Accepted) {

    }
}

void qtkamal::on_actionEst_triggered()
{
    beamDialog *bd = new beamDialog();
    int result = bd->exec();

    if (result == QDialog::Accepted) {

    }
}

void qtkamal::on_actionCirc_triggered()
{
    circleDialog *cd = new circleDialog();
    int result = cd->exec();

    if (result == QDialog::Accepted) {

    }
}

void qtkamal::on_actionGetEarth_triggered()
{
    map->readfile();
}

void qtkamal::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if ( item->parent() == groupPoints && column == 0 ) {
        qtpointitem* pwi = static_cast<qtpointitem*>(item);
        if ( pwi->open( this ) ) {
            item->setText(0, QString::fromStdString(pwi->pc->name) );
            map->update( pwi );
        }
    }

    // Após implementar Triangulação
    //if ( (groupERMs->childCount() + groupBeans->childCount() ) >=2 ) {
    //    ui->actionTrTarget->setEnabled( true );
    //}delete_icon

    /* Após implementar mapa
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it) {
        if ( (*it)->childCount() > 0 ) {
            ui->actionGetEarth->setEnabled( true );
            break;
        }
        ++it;
    }
    */
}

void qtkamal::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu ctxMenu;
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);

    ctxMenu.setStyleSheet("QMenu::item:selected { background: transparent; }");

    QTreeWidgetItem *item = ui->treeWidget->itemAt( pos );

    if (!item) { // Nenhum item selecionado
        clearOldAction = new QAction(tr("limpa"), this);
        clearOldAction->setIcon(QIcon(":/icon/res/clear.png"));
        clearOldAction->setStatusTip(tr("Limpa todas as referências obsoletas"));

        connect(clearOldAction, SIGNAL(triggered()), this, SLOT(clearOldHandler()));
        ctxMenu.addAction(clearOldAction);
        ctxMenu.exec(globalPos);
        return;
    }

    // Se o item não estiver na raiz
    if ( item->parent() ) {
        deleteItemAction = new QAction(tr("delete"), this);
        deleteItemAction->setIcon(QIcon(":/icon/res/delete_icon.png"));
        deleteItemAction->setStatusTip(tr("Remove este item"));
        if ( item->isDisabled() )
            deleteItemAction->setEnabled( false );

        connect(deleteItemAction, SIGNAL(triggered()), this, SLOT(deleteItemHandler()));
        ctxMenu.addAction(deleteItemAction);
        ctxMenu.exec(globalPos);
    }
}

void qtkamal::deleteItemHandler()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    qtpointitem* pwi = static_cast<qtpointitem*>( item );
    map->remove( pwi );
    int i = ui->treeWidget->indexOfTopLevelItem( item );
    ui->treeWidget->takeTopLevelItem(i);
    delete ui->treeWidget->currentItem();
}

void qtkamal::clearOldHandler()
{
    QTreeWidgetItemIterator it( ui->treeWidget );
    while (*it) {
        QTreeWidgetItemIterator child ( it );
        while (*child) {
            if ((*child)->isDisabled()) delete *child;
            child++;
        }
        it++;
    }
}

void qtkamal::args(QStringList args)
{
    foreach(QString arg, args) {
        if ( arg.contains(".kml",Qt::CaseInsensitive) ) {
            map->readfile( arg );
        }
    }
}

void qtkamal::on_actionAbout_triggered()
{
    aboutDialog *ad = new aboutDialog();
    ad->exec();
}
