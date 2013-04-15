#include <QLayout>
#include <QVariant>
#include "qtkamal.h"
#include "ui_qtkamal.h"
#include "dialogs/point.h"

qtkamal::qtkamal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtkamal)
{
    ui->setupUi(this);

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
}

void qtkamal::on_actionCirc_triggered()
{

}

void qtkamal::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if ( item->parent() == groupPoints && column == 0 ) {
        qtpointitem* pwi = static_cast<qtpointitem*>(item);
        pwi->open( this );
        item->setText(0, QString::fromStdString(pwi->pc->name) );
    }

    // Após implementar Triangulação
    //if ( (groupERMs->childCount() + groupBeans->childCount() ) >=2 ) {
    //    ui->actionTrTarget->setEnabled( true );
    //}delete_icon

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

void qtkamal::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget->itemAt( pos );
    if (!item) return; // Nenhum item selecionado

    // Se o item não estiver na raiz
    if ( item->parent() ) {
        QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
        QMenu ctxMenu;

        deleteItemAction = new QAction(tr("delete"), this);
        deleteItemAction->setIcon(QIcon(":/icon/res/delete_icon.png"));
        deleteItemAction->setStatusTip(tr("Remove este item"));

        connect(deleteItemAction, SIGNAL(triggered()), this, SLOT(deleteItemHandler()));
        ctxMenu.addAction(deleteItemAction);
        ctxMenu.setStyleSheet("QMenu::item:selected { background: transparent; }");
        ctxMenu.exec(globalPos);
    }
}

void qtkamal::deleteItemHandler()
{
    int i = ui->treeWidget->indexOfTopLevelItem(ui->treeWidget->currentItem());
    ui->treeWidget->takeTopLevelItem(i);
    delete ui->treeWidget->currentItem();
}
