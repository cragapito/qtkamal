#include <QLayout>
#include <QVariant>
#include "qtkamal.h"
#include "ui_qtkamal.h"
#include "dialogs/point.h"

#include <QMessageBox>

qtkamal::qtkamal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtkamal)
{
    ui->setupUi(this);

    /*
     * Esse slot não traz os dados da derivada!
     *
    connect(ui->treeWidget,
            SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,
            SLOT(on_treeWidget_itemClicked(QTreeWidgetItem*,int)) );*/

    groupPoints = new QTreeWidgetItem();
    groupBeans = new QTreeWidgetItem();
    groupERMs = new QTreeWidgetItem();
    groupCircles = new QTreeWidgetItem();

    ui->treeWidget->addTopLevelItem(groupPoints);
    ui->treeWidget->addTopLevelItem(groupBeans);
    ui->treeWidget->addTopLevelItem(groupERMs);
    ui->treeWidget->addTopLevelItem(groupCircles);

    groupPoints->setIcon(0, QIcon(":/icon/res/open-diamond.png"));
    groupBeans->setIcon(0, QIcon(":/icon/res/man.png"));
    groupERMs->setIcon(0, QIcon(":/icon/res/target.png"));
    groupCircles->setIcon(0, QIcon(":/icon/res/circle.png"));

    groupPoints->setText(0, tr("Pontos"));
    groupBeans->setText(0, tr("Feixes Manuais"));
    groupERMs->setText(0, tr("Feixes de Estação"));
    groupCircles->setText(0, tr("Círculos"));
}

qtkamal::~qtkamal()
{
    delete ui;
}


void qtkamal::on_actionPnt_triggered()
{
    point *a = new point();
    int result = a->exec();

    if (result == QDialog::Accepted) {
        groupPoints->setExpanded( true );
        groupPoints->addChild( a->pi );
    }

    // Após implementar Triangulação
    //if ( (groupERMs->childCount() + groupBeans->childCount() ) >=2 ) {
    //    ui->actionTrTarget->setEnabled( true );
    //}

    /* Após implementar mapa
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it) {
        if ( (*it)->childCount() > 0 ) {
            ui->actionGetEarth->setEnabled( true );
            break;
        }
        ++it;
    }
    */
}

void qtkamal::on_actionCirc_triggered()
{

}

void qtkamal::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if ( item->parent() == groupPoints && column == 0 ) {
        qtpointitem* pwi = static_cast<qtpointitem*>(item);
        pwi->open( this );
    }
}
