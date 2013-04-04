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

        QTreeWidgetItem *itempoint = new QTreeWidgetItem( groupPoints );

        //inserindo objeto
        itempoint->setIcon(0, QIcon(":/icon/res/open-diamond.png"));
        QVariant v;

        //v.setValue( a->gb->returnCoord() );
        itempoint->setText(0, QString::fromStdString( a->gb->returnCoord()->name ));
        //itempoint->setData(0, Qt::UserRole, v);
    }
}

void qtkamal::on_actionCirc_triggered()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
        while (*it) {
            if ((*it)->text(0) == "Feixes Manuais")
                (*it)->setSelected(true);
            ++it;
        }

        QTreeWidgetItem* const item = new QTreeWidgetItem();

    ui->treeWidget->addTopLevelItem(item);
    ui->treeWidget->addTopLevelItem(item);
    ui->treeWidget->addTopLevelItem(item);

    item->setIcon(0, QIcon(":/icon/res/man.png"));
    item->setText(0, tr("teste"));
}
