#include "utils/qtpointitem.h"

qtpointitem::qtpointitem(QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    Coordinate* pc = new Coordinate();
}

qtpointitem::~qtpointitem()
{
    delete(pc);
}
