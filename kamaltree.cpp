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

void kamalTree::dropEvent(QDropEvent *event)
{
    qDebug() << "Moving " << currentItem()->text(0);
    QTreeWidget::dropEvent(event);
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
