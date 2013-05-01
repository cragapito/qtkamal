#include "qtcircleitem.h"
#include "dialogs/circledialog.h"

qtcircleitem::qtcircleitem(QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    center = new Coordinate();
    this->setFlags(Qt::ItemIsSelectable  | Qt::ItemIsUserCheckable
                   | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
}

qtcircleitem::~qtcircleitem()
{
    delete(center);
}

int qtcircleitem::open(QWidget *parent)
{
    circleDialog *cd = new circleDialog(parent, this); // passa parâmetros para contrutor
    return cd->exec();
}

void qtcircleitem::setText(int column, const QString &text)
{
    if ( !text.isEmpty() )
        center->name = text.toStdString();
    QTreeWidgetItem::setText(column, text);
}
