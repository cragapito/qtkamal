#ifndef KAMALTREE_H
#define KAMALTREE_H

#include <QTreeWidget>

class kamalTree : public QTreeWidget
{
    Q_OBJECT

public:
    explicit kamalTree(QWidget *parent = 0);

    QTreeWidgetItem* groupPoints;
    QTreeWidgetItem* groupBeans;
    QTreeWidgetItem* groupERMs;
    QTreeWidgetItem* groupCircles;
    
protected:
    void dropEvent (QDropEvent *event);

signals:
    
public slots:
    void clearOldHandler();
    
};

#endif // KAMALTREE_H
