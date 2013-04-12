#include "utils/qtpointitem.h"
#include "dialogs/point.h"

qtpointitem::qtpointitem(QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
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
