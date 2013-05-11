#include "qtcircleitem.h"
#include "dialogs/circledialog.h"
#include "src/Geo/Beam.h"

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

void qtcircleitem::calc()
{
     Beam *b = new Beam();
     b->source = center;
     perimeter.clear();

     if ( tipoSelect == 0 ) {

         double step = 360.0 / points;

         for ( int i = 0 ; i < points + 1 ; i++ ){
             b->daz = i * step;
             b->proj( radius );

             perimeter.append(   QString::number( b->scope->y, 'g', 12)
                               + ","
                               + QString::number( b->scope->x, 'g', 12)
                               + ",0 ");
         }

     } else {

         double step = abertura / points;

         perimeter.append(   QString::number( b->source->y, 'g', 12)
                           + ","
                           + QString::number( b->source->x, 'g', 12)
                           + ",0 ");

         for ( double i = azimute - abertura / 2;
                      i < azimute + abertura / 2;
                      i += step ) {

             b->daz = i;
             b->proj( radius );
             perimeter.append(   QString::number( b->scope->y, 'g', 12)
                               + ","
                               + QString::number( b->scope->x, 'g', 12)
                               + ",0 ");
         }

         perimeter.append(   QString::number( b->source->y, 'g', 12)
                           + ","
                           + QString::number( b->source->x, 'g', 12)
                           + ",0 ");
     }

     delete(b);
}
