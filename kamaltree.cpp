#include "kamaltree.h"

#include "utils/config.h"
#include "utils/qtbeamitem.h"
#include "utils/qtpointitem.h"
#include "utils/qtcircleitem.h"

#include <QDebug>
#include <QApplication>
#include <QDragLeaveEvent>

// NOTE: Ordenar os pontos por nome(?)
kamalTree::kamalTree(QWidget *parent) :
    QTreeWidget(parent)
{
    groupPoints  = new QTreeWidgetItem();
    groupBeans   = new QTreeWidgetItem();
    groupERMs    = new QTreeWidgetItem();
    groupCircles = new QTreeWidgetItem();

    addTopLevelItem(groupPoints );
    addTopLevelItem(groupBeans  );
    addTopLevelItem(groupERMs   );
    addTopLevelItem(groupCircles);

    groupPoints->setIcon    (0, QIcon(":/icon/res/open-diamond.png" ));
    groupBeans->setIcon     (0, QIcon(":/icon/res/man.png"          ));
    groupERMs->setIcon      (0, QIcon(":/icon/res/target.png"       ));
    groupCircles->setIcon   (0, QIcon(":/icon/res/circle.png"       ));

    groupPoints->setText    (0, tr("Pontos"             ));
    groupBeans->setText     (0, tr("Feixes Manuais"     ));
    groupERMs->setText      (0, tr("Feixes de Estação"  ));
    groupCircles->setText   (0, tr("Área"               ));

    // disable dropping of leaves as top level items
    invisibleRootItem()->setFlags(    Qt::ItemIsSelectable
                                    | Qt::ItemIsUserCheckable
                                    | Qt::ItemIsEnabled       );

    // top level itens
    groupPoints->setFlags ( Qt::ItemIsUserCheckable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled );
    groupBeans->setFlags  ( Qt::ItemIsUserCheckable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled );
    groupERMs->setFlags   ( Qt::ItemIsUserCheckable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled );
    groupCircles->setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled );
}

void kamalTree::SetStyleFold(styleFold *sf)
{
    this->sty = sf;
}

void kamalTree::removeChild(QTreeWidgetItem *child)
{
    this->takeTopLevelItem( this->indexOfTopLevelItem( child ) );
    map->remove( child );
    delete child;
}

// NOTE: Faz sentido multiseleção para feixes?
void kamalTree::dropEvent(QDropEvent *event)
{
    QString group;

    QModelIndexList idxSelectedItems = this->selectionModel()->selectedRows();
    QList<QTreeWidgetItem *> itens = this->selectedItems();

    QApplication::setOverrideCursor(Qt::WaitCursor);

    for(int i=0; i< idxSelectedItems.count(); i++)
    {
        QTreeWidgetItem *item = itens.at(i);

        if ( ! itemAt(event->pos()) ) {
            qDebug() << "Falha ao executar a ação";
            event->ignore();
            return;
        }

        if ( itemAt(event->pos())->parent() ) {
            group = itemAt(event->pos())->parent()->text(0);
        } else {
            group = itemAt(event->pos())->text(0);
        }

        if ( dynamic_cast<qtbeamitem*>(item) == nullptr ){
            qDebug() << "dynamic_cast fail -> item nullptr";
            continue;
        }

        if ( event->proposedAction() == Qt::MoveAction )
            QTreeWidget::dropEvent(event);

        if ( group == "Pontos" && dynamic_cast<qtbeamitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toPoint( dynamic_cast<qtbeamitem*>(item), item->parent() );
                this->removeChild( item );
            } else {
                toPoint( dynamic_cast<qtbeamitem*>(item), groupPoints );
            }
        }

        if ( group == "Pontos" && dynamic_cast<qtcircleitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toPoint( dynamic_cast<qtcircleitem*>(item), item->parent() );
                this->removeChild( item );
            } else {
                toPoint( dynamic_cast<qtcircleitem*>(item), groupPoints );
            }
        }

        if ( group == "Feixes Manuais" && dynamic_cast<qtpointitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toBeam( dynamic_cast<qtpointitem*>(item), qtbeamitem::MAN, item->parent() );
                this->removeChild( item );
            } else {
                toBeam( dynamic_cast<qtpointitem*>(item), qtbeamitem::MAN, groupBeans );
            }
        }

        if ( group == "Feixes de Estação" && dynamic_cast<qtpointitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toBeam( dynamic_cast<qtpointitem*>(item), qtbeamitem::ERM, item->parent() );
                this->removeChild( item );
            } else {
                toBeam( dynamic_cast<qtpointitem*>(item), qtbeamitem::ERM, groupERMs );
            }
        }

        if ( group == "Feixes Manuais" && dynamic_cast<qtcircleitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toBeam( dynamic_cast<qtcircleitem*>(item), qtbeamitem::MAN, item->parent() );
                this->removeChild( item );
            } else {
                toBeam( dynamic_cast<qtcircleitem*>(item), qtbeamitem::MAN, groupBeans );
            }
        }

        if ( group == "Feixes de Estação" && dynamic_cast<qtcircleitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toBeam( dynamic_cast<qtcircleitem*>(item), qtbeamitem::ERM, item->parent() );
                this->removeChild( item );
            } else {
                toBeam( dynamic_cast<qtcircleitem*>(item), qtbeamitem::ERM, groupERMs );
            }
        }

        if ( group == "Feixes Manuais" && dynamic_cast<qtbeamitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toBeam( dynamic_cast<qtbeamitem*>(item), qtbeamitem::MAN, item->parent() );
                this->removeChild( item );
            } else {
                toBeam( dynamic_cast<qtbeamitem*>(item), qtbeamitem::MAN, groupBeans );
            }
        }

        if ( group == "Feixes de Estação" && dynamic_cast<qtbeamitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toBeam( dynamic_cast<qtbeamitem*>(item), qtbeamitem::ERM, item->parent() );
                this->removeChild( item );
            } else {
                toBeam( dynamic_cast<qtbeamitem*>(item), qtbeamitem::ERM, groupERMs );
            }
        }

        if ( group == "Área" && dynamic_cast<qtpointitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toCircle( dynamic_cast<qtpointitem*>(item), item->parent() );
                this->removeChild( item );
            } else {
                toCircle( dynamic_cast<qtpointitem*>(item), groupCircles );
            }
        }

        if ( group == "Área" && dynamic_cast<qtbeamitem*>(item)) {
            if ( event->proposedAction() == Qt::MoveAction ) {
                toCircle( dynamic_cast<qtbeamitem*>(item), item->parent() );
                this->removeChild( item );
            } else {
                toCircle( dynamic_cast<qtbeamitem*>(item), groupCircles );
            }
        }
    }
    QApplication::restoreOverrideCursor();
    emit itemMoved();
    return;
}

void kamalTree::clearOldHandler()
{
    QTreeWidgetItemIterator it( this );
    while (*it) {
        QTreeWidgetItemIterator child ( it );
        while (*child) {
            if ((*child)->isDisabled()) delete *child;
            child++;
        }
        it++;
    }
}

void kamalTree::toPoint(qtbeamitem *bi, QTreeWidgetItem *where)
{
    qtpointitem *pi = new qtpointitem();

    pi->pc->x = bi->bm->source->x;
    pi->pc->y = bi->bm->source->y;
    pi->pc->name = bi->bm->source->name;
    pi->setText(0, bi->text(0) );

    pi->style = "sn_place";
    /*
    ( sty->isInternalStyle( bi->style ) || bi->style.isEmpty() )?
        sty->setIconStyle( "sn_place", pi ):
        sty->setIconStyle(bi->style, pi);
    */

    sty->setIconStyle( "sn_place", pi );

    where->addChild( pi );
    map->update( pi );
    groupPoints->setExpanded( true );
}

void kamalTree::toPoint(qtcircleitem *ci, QTreeWidgetItem *where)
{
    qtpointitem *pi = new qtpointitem();

    pi->pc->x = ci->center->x;
    pi->pc->y = ci->center->y;
    pi->pc->name = ci->center->name;
    pi->setText(0, ci->text(0) );
    pi->style = "sn_place";
    sty->setIconStyle( pi->style, pi );

    where->addChild( pi );
    map->update( pi );
    groupPoints->setExpanded( true );
}

// NOTE: Verificar que as movimentações de/para beans, o alcance mantém o estado anterior.
void kamalTree::toBeam(qtpointitem *pi, qtbeamitem::TYPE type, QTreeWidgetItem *where)
{
    qtbeamitem *bi = new qtbeamitem();
    config *cnf = new config();

    bi->bm->source->x       = pi->pc->x;
    bi->bm->source->y       = pi->pc->y;
    bi->bm->source->name    = pi->pc->name;
    bi->bm->daz             = cnf->beam_azimuth;
    bi->alcance             = cnf->beam_reach;
    bi->beamType            = type;
    bi->bm->proj( bi->alcance );
    bi->setText(0, pi->text(0) );

    /*
    if ( sty->isInternalStyle( pi->style ) || pi->style.isEmpty() ) {
        ( type == qtbeamitem::MAN )?
            sty->setIconStyle( "sn_man", bi ):
            sty->setIconStyle( "sn_erm", bi );
    } else {
        ( type == qtbeamitem::MAN )?
            map->update(pi->style, "sn_man"):
            map->update(pi->style, "sn_erm");
        bi->style = pi->style;
        sty->setIconStyle( bi->style, bi );
    }
    */

    ( type == qtbeamitem::MAN )?
        sty->setIconStyle( "sn_man", bi ):
        sty->setIconStyle( "sn_erm", bi );

    ( type == qtbeamitem::MAN )?
        bi->style = "sn_man":
        bi->style = "sn_erm";

    where->addChild( bi );
    map->update( bi );
    ( type == qtbeamitem::MAN )?
        groupBeans->setExpanded(true):
        groupERMs->setExpanded(true);
}

void kamalTree::toBeam(qtbeamitem *bii, qtbeamitem::TYPE type, QTreeWidgetItem *where)
{
    qtbeamitem *bi = new qtbeamitem();

    bi->alcance             = bii->alcance;
    bi->beamType            = type;
    bi->bm->daz             = bii->bm->daz;
    bi->bm->source->x       = bii->bm->source->x;
    bi->bm->source->y       = bii->bm->source->y;
    bi->bm->source->name    = bii->bm->source->name;

    bi->bm->proj( bi->alcance );
    bi->setText(0, bii->text(0));

    /*
    if ( sty->isInternalStyle( bii->style ) || bii->style.isEmpty() ) {
        ( type == qtbeamitem::MAN )?
            sty->setIconStyle( "sn_man", bi ):
            sty->setIconStyle( "sn_erm", bi );
    } else {
        sty->setIconStyle( bii->style, bi );
    }
    */

    ( type == qtbeamitem::MAN )?
        sty->setIconStyle( "sn_man", bi ):
        sty->setIconStyle( "sn_erm", bi );

    ( type == qtbeamitem::MAN )?
        bi->style = "sn_man":
        bi->style = "sn_erm";

    where->addChild( bi );
    map->update( bi );
    ( type == qtbeamitem::MAN )?
        groupBeans->setExpanded(true):
        groupERMs->setExpanded(true);
}

void kamalTree::toBeam(qtcircleitem *ci, qtbeamitem::TYPE type, QTreeWidgetItem *where)
{
    qtbeamitem *bi = new qtbeamitem();

    bi->alcance             = ci->radius;
    bi->beamType            = type;
    bi->bm->source->x       = ci->center->x;
    bi->bm->source->y       = ci->center->y;
    bi->bm->source->name    = ci->center->name;
    bi->bm->daz             = ci->azimute;
    bi->bm->proj( ci->radius );

    bi->setText(0, ci->text(0) );
    ( type == qtbeamitem::MAN )?
        sty->setIconStyle( "sn_man", bi ):
        sty->setIconStyle( "sn_erm", bi );

    ( type == qtbeamitem::MAN )?
        bi->style = "sn_man":
        bi->style = "sn_erm";

    /*
    if ( ! ci->style.isEmpty() )
        bi->style = ci->style;
    */

    where->addChild( bi );
    map->update( bi );
    ( type == qtbeamitem::MAN )?
        groupBeans->setExpanded(true):
        groupERMs->setExpanded(true);
}

void kamalTree::toCircle(qtpointitem *pi, QTreeWidgetItem *where)
{
    qtcircleitem *ci = new qtcircleitem();
    config *cnf = new config();

    ci->center->x       = pi->pc->x;
    ci->center->y       = pi->pc->y;
    ci->center->name    = pi->pc->name;
    ci->abertura        = cnf->circ_opening;
    ci->radius          = cnf->circ_radius;
    ci->points          = cnf->circ_points;
    ci->azimute         = cnf->beam_azimuth;
    ci->tipoSelect      = 0;
    ci->calc();
    ci->setText(0, pi->text(0) );
    ci->style = "sn_cir";
    //ci->style = pi->style;
    sty->setIconStyle( "sn_cir", ci );

    where->addChild( ci );
    map->update( ci );
    groupCircles->setExpanded( true );
}

void kamalTree::toCircle(qtbeamitem *bi, QTreeWidgetItem *where)
{
    qtcircleitem *ci = new qtcircleitem();
    config *cnf = new config();

    ci->center->x       = bi->bm->source->x;
    ci->center->y       = bi->bm->source->y;
    ci->center->name    = bi->bm->source->name;
    ci->azimute         = bi->bm->daz;
    ci->radius          = bi->alcance;
    ci->abertura        = cnf->circ_opening;
    ci->points          = cnf->circ_points;
    ci->tipoSelect      = 1;
    ci->calc();
    ci->setText(0, bi->text(0) );
    ci->style = "sn_cir";
    //ci->style = bi->style;

    sty->setIconStyle( "sn_cir", ci );

    where->addChild( ci );
    map->update( ci );
    groupCircles->setExpanded(true);
}

kamalTree::~kamalTree()
{
    map->~kml();
}
