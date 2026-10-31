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

// Remove o item da árvore e do mapa KML de forma segura.
// Itens de dados são filhos de grupos (groupPoints, etc.), logo child->parent()->removeChild é obrigatório.
void kamalTree::removeChild(QTreeWidgetItem *child)
{
    if (!child) return;
    if (child->parent()) {
        child->parent()->removeChild(child);
    } else {
        int idx = this->indexOfTopLevelItem(child);
        if (idx >= 0)
            this->takeTopLevelItem(idx);
    }
    if (map)
        map->remove(child);
    delete child;
}

// NOTE: Faz sentido multiseleção para feixes?
// Gerencia Drag & Drop para promoção/conversão entre os 4 grupos principais (Pontos, Feixes Manuais, Feixes de Estação e Área).
void kamalTree::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem *targetItem = itemAt(event->pos());
    if ( !targetItem ) {
        qDebug() << "Falha ao executar a ação: alvo inválido";
        event->ignore();
        return;
    }

    // Identifica o grupo de destino (seja o próprio cabeçalho ou um item filho dentro dele)
    QTreeWidgetItem *targetGroup = targetItem->parent() ? targetItem->parent() : targetItem;

    if (targetGroup != groupPoints && targetGroup != groupBeans &&
        targetGroup != groupERMs && targetGroup != groupCircles) {
        event->ignore();
        return;
    }

    QList<QTreeWidgetItem *> itens = this->selectedItems();
    if (itens.isEmpty()) {
        event->ignore();
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    bool anyHandled = false;

    for (int i = 0; i < itens.count(); i++)
    {
        QTreeWidgetItem *item = itens.at(i);
        if (!item || item == groupPoints || item == groupBeans ||
            item == groupERMs || item == groupCircles)
            continue;

        // Se o item já pertence ao mesmo grupo, nada a converter
        if (item->parent() == targetGroup) {
            continue;
        }

        qtbeamitem *bi = dynamic_cast<qtbeamitem*>(item);
        qtpointitem *pi = dynamic_cast<qtpointitem*>(item);
        qtcircleitem *ci = dynamic_cast<qtcircleitem*>(item);

        bool handled = false;

        // Conversão para Pontos
        if (targetGroup == groupPoints) {
            if (bi) {
                toPoint(bi, groupPoints);
                handled = true;
            } else if (ci) {
                toPoint(ci, groupPoints);
                handled = true;
            }
        // Conversão para Feixes Manuais
        } else if (targetGroup == groupBeans) {
            if (pi) {
                toBeam(pi, qtbeamitem::MAN, groupBeans);
                handled = true;
            } else if (ci) {
                toBeam(ci, qtbeamitem::MAN, groupBeans);
                handled = true;
            } else if (bi) {
                toBeam(bi, qtbeamitem::MAN, groupBeans);
                handled = true;
            }
        // Conversão para Feixes de Estação
        } else if (targetGroup == groupERMs) {
            if (pi) {
                toBeam(pi, qtbeamitem::ERM, groupERMs);
                handled = true;
            } else if (ci) {
                toBeam(ci, qtbeamitem::ERM, groupERMs);
                handled = true;
            } else if (bi) {
                toBeam(bi, qtbeamitem::ERM, groupERMs);
                handled = true;
            }
        // Conversão para Área / Círculos
        } else if (targetGroup == groupCircles) {
            if (pi) {
                toCircle(pi, groupCircles);
                handled = true;
            } else if (bi) {
                toCircle(bi, groupCircles);
                handled = true;
            }
        }

        // Se o item foi convertido e a ação é mover (não copiar/Ctrl), remove o original
        if (handled) {
            anyHandled = true;
            if (event->proposedAction() == Qt::MoveAction) {
                this->removeChild(item);
            }
        }
    }

    QApplication::restoreOverrideCursor();

    if (anyHandled) {
        // Aceita a ação proposta sem chamar o dropEvent base, evitando conflito com ponteiros já deletados
        event->acceptProposedAction();
        emit itemMoved();
    } else {
        // Reordenação interna dentro do mesmo grupo
        QTreeWidget::dropEvent(event);
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
    config cnf;

    bi->bm->source->x       = pi->pc->x;
    bi->bm->source->y       = pi->pc->y;
    bi->bm->source->name    = pi->pc->name;
    bi->bm->daz             = cnf.beam_azimuth;
    bi->alcance             = cnf.beam_reach;
    bi->beamType            = type;
    bi->bm->proj( bi->alcance );
    bi->setText(0, pi->text(0) );

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

    where->addChild( bi );
    map->update( bi );
    ( type == qtbeamitem::MAN )?
        groupBeans->setExpanded(true):
        groupERMs->setExpanded(true);
}

void kamalTree::toCircle(qtpointitem *pi, QTreeWidgetItem *where)
{
    qtcircleitem *ci = new qtcircleitem();
    config cnf;

    ci->center->x       = pi->pc->x;
    ci->center->y       = pi->pc->y;
    ci->center->name    = pi->pc->name;
    ci->abertura        = cnf.circ_opening;
    ci->radius          = cnf.circ_radius;
    ci->points          = cnf.circ_points;
    ci->azimute         = cnf.beam_azimuth;
    ci->tipoSelect      = 0;
    ci->calc();
    ci->setText(0, pi->text(0) );
    ci->style = "sn_cir";
    sty->setIconStyle( "sn_cir", ci );

    where->addChild( ci );
    map->update( ci );
    groupCircles->setExpanded( true );
}

void kamalTree::toCircle(qtbeamitem *bi, QTreeWidgetItem *where)
{
    qtcircleitem *ci = new qtcircleitem();
    config cnf;

    ci->center->x       = bi->bm->source->x;
    ci->center->y       = bi->bm->source->y;
    ci->center->name    = bi->bm->source->name;
    ci->azimute         = bi->bm->daz;
    ci->radius          = bi->alcance;
    ci->abertura        = cnf.circ_opening;
    ci->points          = cnf.circ_points;
    ci->tipoSelect      = 1;
    ci->calc();
    ci->setText(0, bi->text(0) );
    ci->style = "sn_cir";

    sty->setIconStyle( "sn_cir", ci );

    where->addChild( ci );
    map->update( ci );
    groupCircles->setExpanded(true);
}

kamalTree::~kamalTree()
{
    // Libera a instância do parser KML alocada para a árvore
    delete map;
}
