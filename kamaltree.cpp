#include "kamaltree.h"

#include "utils/qtbeamitem.h"
#include "utils/qtpointitem.h"
#include "utils/qtcircleitem.h"

#include <QDebug>
#include <QDragLeaveEvent>

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

void kamalTree::SetStyleFold(styleFold *sf)
{
    this->sty = sf;
}

void kamalTree::removeChild(QTreeWidgetItem *child)
{
    map->remove( child );
    delete child;
}

void kamalTree::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem *item = currentItem();

    QString group;

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

    // TODO: Falha ao copiar item
    QTreeWidget::dropEvent(event);

    if ( group == "Pontos" && dynamic_cast<qtbeamitem*>(item)) {
        toPoint( dynamic_cast<qtbeamitem*>(item) );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Pontos" && dynamic_cast<qtcircleitem*>(item)) {
        toPoint( dynamic_cast<qtcircleitem*>(item) );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Feixes Manuais" && dynamic_cast<qtpointitem*>(item)) {
        toBeam( dynamic_cast<qtpointitem*>(item), qtbeamitem::MAN );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Feixes de Estação" && dynamic_cast<qtpointitem*>(item)) {
        toBeam( dynamic_cast<qtpointitem*>(item), qtbeamitem::ERM );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Feixes Manuais" && dynamic_cast<qtcircleitem*>(item)) {
        toBeam( dynamic_cast<qtcircleitem*>(item), qtbeamitem::MAN );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Feixes de Estação" && dynamic_cast<qtcircleitem*>(item)) {
        toBeam( dynamic_cast<qtcircleitem*>(item), qtbeamitem::ERM );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Feixes Manuais" && dynamic_cast<qtbeamitem*>(item)) {
        toBeam( dynamic_cast<qtbeamitem*>(item), qtbeamitem::MAN  );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Feixes de Estação" && dynamic_cast<qtbeamitem*>(item)) {
        toBeam( dynamic_cast<qtbeamitem*>(item), qtbeamitem::ERM );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Área" && dynamic_cast<qtpointitem*>(item)) {
        toCircle( dynamic_cast<qtpointitem*>(item) );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }

    if ( group == "Área" && dynamic_cast<qtbeamitem*>(item)) {
        toCircle( dynamic_cast<qtbeamitem*>(item) );
        if ( event->proposedAction() == Qt::MoveAction )
            this->removeChild( item );
        return;
    }
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

void kamalTree::toPoint(qtbeamitem *bi)
{
    qtpointitem *pi = new qtpointitem();

    pi->pc->x = bi->bm->source->x;
    pi->pc->y = bi->bm->source->y;
    pi->pc->name = bi->bm->source->name;
    pi->setText(0, bi->text(0) );

    pi->style = bi->style;
    ( sty->isInternalStyle( bi->style ) || bi->style.isEmpty() )?
        sty->setIconStyle( "sn_place", pi ):
        sty->setIconStyle(bi->style, pi);

    bi->parent()->addChild( pi );
    map->update( pi );
    groupPoints->setExpanded( true );
}

void kamalTree::toPoint(qtcircleitem *ci)
{
    qtpointitem *pi = new qtpointitem();

    pi->pc->x = ci->center->x;
    pi->pc->y = ci->center->y;
    pi->pc->name = ci->center->name;
    pi->setText(0, ci->text(0) );
    pi->style = "sn_place";
    sty->setIconStyle( pi->style, pi );

    ci->parent()->addChild( pi );
    map->update( pi );
    groupPoints->setExpanded( true );
}

void kamalTree::toBeam(qtpointitem *pi, qtbeamitem::TYPE type)
{
    qtbeamitem *bi = new qtbeamitem();

    bi->bm->source->x = pi->pc->x;
    bi->bm->source->y = pi->pc->y;
    bi->bm->source->name = pi->pc->name;
    bi->bm->daz = 45;
    bi->alcance = 5;
    bi->beamType = type;
    bi->bm->proj( bi->alcance );
    bi->setText(0, pi->text(0) );

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

    pi->parent()->addChild( bi );
    map->update( bi );
    ( type == qtbeamitem::MAN )?
        groupBeans->setExpanded(true):
        groupERMs->setExpanded(true);
}

void kamalTree::toBeam(qtbeamitem *bii, qtbeamitem::TYPE type)
{
    qtbeamitem *bi = new qtbeamitem();

    bi->alcance = bii->alcance;
    bi->beamType = type;
    bi->bm->source->x = bii->bm->source->x;
    bi->bm->source->y = bii->bm->source->y;
    bi->bm->source->name = bii->bm->source->name;
    bi->bm->proj( bii->alcance );
    bi->setText(0, bii->text(0));

    if ( sty->isInternalStyle( bii->style ) || bii->style.isEmpty() ) {
        ( type == qtbeamitem::MAN )?
            sty->setIconStyle( "sn_man", bi ):
            sty->setIconStyle( "sn_erm", bi );
    } else {
        sty->setIconStyle( bii->style, bi );
    }

    ( type == qtbeamitem::MAN )?
        map->update(bii->style, "sn_man"):
        map->update(bii->style, "sn_erm");

    bii->parent()->addChild( bi );
    map->update( bi );
    ( type == qtbeamitem::MAN )?
        groupBeans->setExpanded(true):
        groupERMs->setExpanded(true);
}

void kamalTree::toBeam(qtcircleitem *ci, qtbeamitem::TYPE type)
{
    qtbeamitem *bi = new qtbeamitem();

    bi->bm->source->x = ci->center->x;
    bi->bm->source->y = ci->center->y;
    bi->bm->source->name = ci->center->name;
    bi->bm->daz = ci->azimute;
    bi->alcance = ci->radius;
    bi->bm->proj( ci->radius );

    bi->setText(0, ci->text(0) );
    ( type == qtbeamitem::MAN )?
        sty->setIconStyle( "sn_man", bi ):
        sty->setIconStyle( "sn_erm", bi );

    ( type == qtbeamitem::MAN )?
        map->update(bi->style, "sn_man"):
        map->update(bi->style, "sn_erm");

    if ( ! ci->style.isEmpty() )
        bi->style = ci->style;
    ci->parent()->addChild( bi );
    map->update( bi );
    ( type == qtbeamitem::MAN )?
        groupBeans->setExpanded(true):
        groupERMs->setExpanded(true);
}

void kamalTree::toCircle(qtpointitem *pi)
{
    qtcircleitem *ci = new qtcircleitem();

    ci->center->x = pi->pc->x;
    ci->center->y = pi->pc->y;
    ci->center->name = pi->pc->name;
    ci->abertura = 10;
    ci->azimute = 45;
    ci->radius = 5.0;
    ci->points = 100;
    ci->tipoSelect = 0;
    ci->calc();
    ci->setText(0, pi->text(0) );
    ci->style = pi->style;
    sty->setIconStyle( "sn_cir", ci );

    pi->parent()->addChild( ci );
    map->update(ci->style, "sn_cir");
    map->update("sn_cir", "sn_cir");
    map->update( ci );
    groupCircles->setExpanded( true );
}

void kamalTree::toCircle(qtbeamitem *bi)
{
    qtcircleitem *ci = new qtcircleitem();

    ci->center->x = bi->bm->source->x;
    ci->center->y = bi->bm->source->y;
    ci->center->name = bi->bm->source->name;
    ci->azimute = bi->bm->daz;
    ci->radius = bi->alcance;
    ci->abertura = 10;
    ci->tipoSelect = 1;
    ci->calc();
    ci->setText(0, bi->text(0) );
    ci->style = bi->style;
    sty->setIconStyle( "sn_cir", ci );
    map->update(ci->style, "sn_cir");

    bi->parent()->addChild( ci );
    map->update( ci );
    groupCircles->setExpanded(true);
}
