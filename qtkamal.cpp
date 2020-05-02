#include "qtkamal.h"
#include "ui_qtkamal.h"

#include "dialogs/beamdialog.h"
#include "dialogs/pointdialog.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/circledialog.h"

#include <QUrl>
#include <QDropEvent>

qtkamal::qtkamal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtkamal)
{
    ui->setupUi(this);
    sty = new styleFold();
    ui->treeWidget->map = new kml( this, ui->treeWidget, sty );
    ui->treeWidget->SetStyleFold( sty );

#ifdef WITH_TRIANG
    #ifndef MIN_TRIANG_ANGLE
        #define MIN_TRIANG_ANGLE 10
    #endif
    vbeans = new QList<qtbeamitem*>();
    connect(this          , SIGNAL(beamMoved()), this, SLOT(checkTargetFunction()));
    connect(ui->treeWidget, SIGNAL(beamMoved()), this, SLOT(checkTargetFunction()));
#endif
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
        ui->treeWidget->map->readfile( url.toLocalFile() );
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
    pointDialog *pd = new pointDialog();
    int result = pd->exec();

    if (result == QDialog::Accepted) {
        ui->treeWidget->groupPoints->setExpanded( true );
        ui->treeWidget->groupPoints->addChild( pd->pi );
        if ( pd->pi->element.isNull() ) {
            pd->pi->style = "sn_place";
            sty->setIconStyle( "sn_place", pd->pi );
            ui->treeWidget->map->update( pd->pi );
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
        bd->bi->style = "sn_man";
        sty->setIconStyle( "sn_man", bd->bi );
        ui->treeWidget->map->update( bd->bi );
        emit beamMoved();
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
        bd->bi->style = "sn_erm";
        sty->setIconStyle( "sn_erm", bd->bi );
        ui->treeWidget->map->update( bd->bi );
        emit beamMoved();
    }
}

void qtkamal::on_actionCirc_triggered()
{
    circleDialog *cd = new circleDialog();
    int result = cd->exec();

    if (result == QDialog::Accepted) {
        ui->treeWidget->groupCircles->setExpanded( true );
        ui->treeWidget->groupCircles->addChild( cd->ci );
        cd->ci->style = "sn_cir";
        sty->setIconStyle( "sn_cir", cd->ci );
        ui->treeWidget->map->update( cd->ci );
    }
}

void qtkamal::on_actionGetEarth_triggered()
{
    ui->treeWidget->map->readfile();
    emit beamMoved();
}

void qtkamal::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if ( item->parent() == ui->treeWidget->groupPoints && column == 0 ) {
        qtpointitem* pwi = static_cast<qtpointitem*>(item);
        if ( pwi->open( this ) ) {
            item->setText(0, QString::fromStdString(pwi->pc->name) );
            ui->treeWidget->map->update( pwi );
        }
    }

    if ( ( item->parent() == ui->treeWidget->groupBeans || item->parent() == ui->treeWidget->groupERMs ) && column == 0 ) {
        qtbeamitem* bwi = static_cast<qtbeamitem*>(item);
        if ( bwi->open( this ) ) {
            item->setText(0, QString::fromStdString( bwi->bm->source->name ) );
            ui->treeWidget->map->update( bwi );
            emit beamMoved();
        }
    }

    if ( item->parent() == ui->treeWidget->groupCircles && column == 0 ) {
        qtcircleitem* pwi = static_cast<qtcircleitem*>(item);
        if ( pwi->open( this ) ) {
            item->setText(0, QString::fromStdString(pwi->center->name) );
            pwi->calc();
            ui->treeWidget->map->update( pwi );
            emit beamMoved();
        }
    }
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

    // Nenhum item selecionado ou item de grupo ou obsoleto
    if (!item || !item->parent() || item->isDisabled()) {
        clearOldAction = new QAction(tr("limpa obsoletos"), this);
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
    ui->treeWidget->removeChild( item );
}

void qtkamal::checkTargetFunction()
{
#ifdef WITH_TRIANG
    if ( ( ui->treeWidget->groupBeans->childCount()
           + ui->treeWidget->groupERMs->childCount() ) >=2 ) {
        ui->actionTrTarget->setEnabled( true );

        QTreeWidgetItemIterator it( ui->treeWidget );

        vbeans->clear();

        while ( *it ) {
            if (   (*it)->parent() == ui->treeWidget->groupBeans
                || (*it)->parent() == ui->treeWidget->groupERMs   ) {
                vbeans->push_back( dynamic_cast<qtbeamitem*>(*it) );
            }
            it++;
        }

        qtbeamitem *b = vbeans->at(0);
        double ref = b->bm->daz;

        for ( int i = 1 ; i < vbeans->size() ; i++ ) {
            b = vbeans->at(i);

            // Libera se a diferença dos angulos for significativa
            if ( ( b->bm->daz - ref ) >=  MIN_TRIANG_ANGLE ||
                 ( b->bm->daz - ref ) <= -MIN_TRIANG_ANGLE ) {
                ui->actionTrTarget->setEnabled( true );
                return;
            }
        }
    }

    ui->actionTrTarget->setEnabled( false );

#endif
}

void qtkamal::args(QStringList args)
{
    foreach(QString arg, args) {
        if ( arg.contains(".kml",Qt::CaseInsensitive) ) {
            ui->treeWidget->map->readfile( arg );
        }
    }
}

void qtkamal::on_actionTrTarget_triggered()
{
#ifdef WITH_TRIANG

    ui->actionTrTarget->setEnabled( false );

    vector<Straight*> *vs = new vector<Straight*>();

    for ( int i = 0 ; i < vbeans->size() ; i++ ) {
        qtbeamitem *bo = vbeans->at(i);
        qtbeamitem *b = bo; // Deep copy
        vs->push_back( dynamic_cast<Straight*>( b->bm ) );
    }

    LinearSolver *ls = new LinearSolver( *vs );
    qtpointitem *pi = new qtpointitem();

    std::cout << "Calculando cruzamento de " << vbeans->size() << " retas." << std::endl;
    Point *c = ls->solve();

    std::cout << "Localização estimada em " << (Coordinate*)c << std::endl;

    std::cout << ls->getResidual() << std::endl;;

    pi->pc->x = c->x;
    pi->pc->y = c->y;

    pi->setText(0, QString( "Localização Estimada" ));
    pi->style = "sn_place";
    sty->setIconStyle( "sn_place", pi );

    /*
     *
     * Novo alcance 10% maior que a distância entre os pontos
     * para forçar o cruzamento dos feixes
     *
     */



    for ( int i = 0 ; i < vbeans->size() ; i++ ) {
        qtbeamitem *b = vbeans->at(i);
        double a = *pi->pc - *b->bm->source;
        b->alcance = a;
        b->bm->proj( a );
        ui->treeWidget->map->update( b );
    }

    ui->treeWidget->groupPoints->addChild( pi );
    ui->treeWidget->groupPoints->setExpanded( true );
    ui->treeWidget->map->update( pi );

    delete c;
    delete ls;
    delete vs;

#endif
}
