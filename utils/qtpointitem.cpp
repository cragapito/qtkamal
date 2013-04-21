#include "utils/qtpointitem.h"
#include "dialogs/point.h"

qtpointitem::qtpointitem(QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    pc = new Coordinate();
}

qtpointitem::~qtpointitem()
{
    delete(pc);
}

void qtpointitem::open(QWidget *parent)
{
    point *a = new point( parent, this->pc );
    a->exec();
}

void qtpointitem::qtpointitem::setText(int column, const QString &text) // Overrided
{
    if ( !text.isEmpty() )
        pc->name = text.toStdString();
    QTreeWidgetItem::setText(column, text);
}
