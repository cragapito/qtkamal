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
    ui->treeWidget->SetStyleFold( sty );
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
        ui->treeWidget->groupPoints->setExpanded( true );
        ui->treeWidget->groupPoints->addChild( pd->pi );
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
        ui->treeWidget->groupBeans->setExpanded( true );
        ui->treeWidget->groupBeans->addChild( bd->bi );
        bd->bi->beamType = bd->bi->MAN;
        sty->setIconStyle( "sn_man", bd->bi );
        map->update( bd->bi );
    }
}

void qtkamal::on_actionEst_triggered()
{
    beamDialog *bd = new beamDialog();
    int result = bd->exec();

    if (result == QDialog::Accepted) {
        ui->treeWidget->groupERMs->setExpanded( true );
        ui->treeWidget->groupERMs->addChild( bd->bi );
        bd->bi->beamType = bd->bi->ERM;
        sty->setIconStyle( "sn_erm", bd->bi );
        map->update( bd->bi );
    }
}

void qtkamal::on_actionCirc_triggered()
{
    circleDialog *cd = new circleDialog();
    int result = cd->exec();

    if (result == QDialog::Accepted) {
        ui->treeWidget->groupCircles->setExpanded( true );
        ui->treeWidget->groupCircles->addChild( cd->ci );
        sty->setIconStyle( "sn_cir", cd->ci );
        map->update( cd->ci );
    }
}

void qtkamal::on_actionGetEarth_triggered()
{
    map->readfile();
}

void qtkamal::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if ( item->parent() == ui->treeWidget->groupPoints && column == 0 ) {
        qtpointitem* pwi = static_cast<qtpointitem*>(item);
        if ( pwi->open( this ) ) {
            item->setText(0, QString::fromStdString(pwi->pc->name) );
            map->update( pwi );
        }
    }

    if ( ( item->parent() == ui->treeWidget->groupBeans || item->parent() == ui->treeWidget->groupERMs ) && column == 0 ) {
        qtbeamitem* bwi = static_cast<qtbeamitem*>(item);
        if ( bwi->open( this ) ) {
            item->setText(0, QString::fromStdString( bwi->bm->source->name ) );
            map->update( bwi );
        }
    }

    if ( item->parent() == ui->treeWidget->groupCircles && column == 0 ) {
        qtcircleitem* pwi = static_cast<qtcircleitem*>(item);
        if ( pwi->open( this ) ) {
            item->setText(0, QString::fromStdString(pwi->center->name) );
            pwi->calc();
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

void qtkamal::on_actionAbout_triggered()
{
    aboutDialog *ad = new aboutDialog();
    ad->exec();
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

        connect(clearOldAction, SIGNAL(triggered()), ui->treeWidget, SLOT(clearOldHandler()));
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
    map->remove( item );
    int i = ui->treeWidget->indexOfTopLevelItem( item );
    ui->treeWidget->takeTopLevelItem(i);
    delete ui->treeWidget->currentItem();
}

void qtkamal::args(QStringList args)
{
    foreach(QString arg, args) {
        if ( arg.contains(".kml",Qt::CaseInsensitive) ) {
            map->readfile( arg );
        }
    }
}
