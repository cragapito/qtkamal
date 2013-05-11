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

    QTreeWidget::dropEvent(event);

    if ( group == "Pontos" && dynamic_cast<qtbeamitem*>(item))
        toPoint( dynamic_cast<qtbeamitem*>(item) );

    if ( group == "Pontos" && dynamic_cast<qtcircleitem*>(item))
        toPoint( dynamic_cast<qtcircleitem*>(item) );

    if ( group == "Feixes Manuais" && dynamic_cast<qtpointitem*>(item))
        toBeam( dynamic_cast<qtpointitem*>(item), qtbeamitem::MAN );

    if ( group == "Feixes de Estação" && dynamic_cast<qtpointitem*>(item))
        toBeam( dynamic_cast<qtpointitem*>(item), qtbeamitem::ERM );

    if ( group == "Feixes Manuais" && dynamic_cast<qtcircleitem*>(item))
        toBeam( dynamic_cast<qtcircleitem*>(item), qtbeamitem::MAN );

    if ( group == "Feixes de Estação" && dynamic_cast<qtcircleitem*>(item))
        toBeam( dynamic_cast<qtcircleitem*>(item), qtbeamitem::ERM );

    if ( group == "Feixes Manuais" && dynamic_cast<qtbeamitem*>(item))
        toBeam( dynamic_cast<qtbeamitem*>(item), qtbeamitem::MAN  );

    if ( group == "Feixes de Estação" && dynamic_cast<qtbeamitem*>(item))
        toBeam( dynamic_cast<qtbeamitem*>(item), qtbeamitem::ERM );

    if ( group == "Área" && dynamic_cast<qtpointitem*>(item))
        toCircle( dynamic_cast<qtpointitem*>(item) );

    if ( group == "Área" && dynamic_cast<qtbeamitem*>(item))
        toCircle( dynamic_cast<qtbeamitem*>(item) );
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
    sty->setIconStyle( "sn_place", pi );

    bi->parent()->addChild( pi );
    map->update( pi );
    this->removeChild( bi );
    groupPoints->setExpanded( true );
}

void kamalTree::toPoint(qtcircleitem *ci)
{
    qtpointitem *pi = new qtpointitem();

    pi->pc->x = ci->center->x;
    pi->pc->y = ci->center->y;
    pi->pc->name = ci->center->name;
    pi->setText(0, ci->text(0) );
    sty->setIconStyle( "sn_place", pi );

    ci->parent()->addChild( pi );
    map->update( pi );
    this->removeChild( ci );
    groupPoints->setExpanded( true );
}

void kamalTree::toBeam(qtpointitem *pi, qtbeamitem::TYPE type)
{
    qtbeamitem *bi = new qtbeamitem();

    bi->bm->source->x = pi->pc->x;
    bi->bm->source->y = pi->pc->y;
    bi->bm->source->name = pi->pc->name;
    bi->bm->daz = 0;
    bi->alcance = 40;
    bi->bm->proj( bi->alcance );
    bi->setText(0, pi->text(0) );
    ( type == qtbeamitem::MAN )?
        sty->setIconStyle( "sn_man", bi ):
        sty->setIconStyle( "sn_erm", bi );

    pi->parent()->addChild( bi );
    map->update( bi );
    this->removeChild( pi );
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

    ( type == qtbeamitem::MAN )?
        sty->setIconStyle( "sn_man", bi ):
        sty->setIconStyle( "sn_erm", bi );

    bii->parent()->addChild( bi );
    map->update( bi );
    this->removeChild( bii );
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
    bi->bm->proj( ci->radius );
    bi->setText(0, ci->text(0) );
    ( type == qtbeamitem::MAN )?
        sty->setIconStyle( "sn_man", bi ):
        sty->setIconStyle( "sn_erm", bi );

    ci->parent()->addChild( bi );
    map->update( bi );
    this->removeChild( ci );
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
    ci->radius = 100;
    ci->points = 100;
    ci->tipoSelect = 0;
    ci->setText(0, pi->text(0) );
    sty->setIconStyle( "sn_cir", ci );

    pi->parent()->addChild( ci );
    map->update( ci );
    this->removeChild( pi );
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
    ci->tipoSelect = 1;
    ci->setText(0, bi->text(0) );
    sty->setIconStyle( "sn_cir", ci );

    bi->parent()->addChild( ci );
    map->update( ci );
    this->removeChild( bi );
    groupCircles->setExpanded(true);
}
