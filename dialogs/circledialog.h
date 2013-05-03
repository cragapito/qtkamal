#ifndef CIRCLEDIALOG_H
#define CIRCLEDIALOG_H

#include <QDialog>

#include "utils/qtcircleitem.h"

namespace Ui {
class circleDialog;
}

class circleDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit circleDialog(QWidget *parent = 0);
    explicit circleDialog(QWidget *parent, qtcircleitem *ci);
    ~circleDialog();

    qtcircleitem *ci;
    
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_comboType_currentIndexChanged(int index);

private:
    Ui::circleDialog *ui;
};

#endif // CIRCLEDIALOG_H
