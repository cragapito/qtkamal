#ifndef POINTDIALOG_H
#define POINTDIALOG_H

#include <QDialog>
#include <QString>

#include "utils/config.h"
#include "utils/qtpointitem.h"

namespace Ui {
class pointDialog;
}

class pointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit pointDialog(QWidget *parent = 0);
    explicit pointDialog(QWidget *parent, Coordinate *pc, QIcon icon );
    virtual  ~pointDialog();

    qtpointitem *pi;

private:
    config *cnf;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::pointDialog *ui;
};

#endif // POINTDIALOG_H
