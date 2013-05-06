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

void kamalTree::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem *item = currentItem();

    QTreeWidget::dropEvent(event);

    QString group;

    if ( itemAt(event->pos())->parent() ) {
        group = itemAt(event->pos())->parent()->text(0);
    } else {
        group = itemAt(event->pos())->text(0);
    }

    if ( group == "Pontos" && dynamic_cast<qtbeamitem*>(item))
        toPoint( dynamic_cast<qtbeamitem*>(item) );

    if ( group == "Pontos" && dynamic_cast<qtcircleitem*>(item))
        toPoint( dynamic_cast<qtcircleitem*>(item) );

    // TODO: Implementar o resto
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
    // TODO: Mapa fora do alcance
    //map->update( pi );
    //map->remove( bi );
    delete bi;
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
    //map->update( pi );
    //map->remove( ci );
    delete ci;
}
