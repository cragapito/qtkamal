#include "utils/qtpointitem.h"
#include "dialogs/point.h"

#include <QDragEnterEvent>

qtpointitem::qtpointitem(QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    pc = new Coordinate();
    this->setFlags(Qt::ItemIsSelectable  | Qt::ItemIsUserCheckable
                 | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
}

qtpointitem::~qtpointitem()
{
    delete(pc);
}

int qtpointitem::open(QWidget *parent)
{
    point *a = new point( parent, this->pc, this->icon(0));
    return a->exec();
}

void qtpointitem::qtpointitem::setText(int column, const QString &text) // Overrided
{
    if ( !text.isEmpty() )
        pc->name = text.toStdString();
    QTreeWidgetItem::setText(column, text);
}
