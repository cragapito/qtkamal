#include "qtbeamitem.h"
#include "dialogs/beamdialog.h"

qtbeamitem::qtbeamitem(QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    bm = new Beam();
    this->setFlags(Qt::ItemIsSelectable  | Qt::ItemIsUserCheckable
                   | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
}

qtbeamitem::~qtbeamitem()
{
    delete(bm);
}

int qtbeamitem::open(QWidget *parent)
{
    beamDialog *b = new beamDialog(parent, this);
    return b->exec();
}

void qtbeamitem::setText(int column, const QString &text)
{
    if ( !text.isEmpty() )
        *bm->name = text.toStdString();
    QTreeWidgetItem::setText(column, text);
}
