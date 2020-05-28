#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QAbstractButton>

#include "utils/config.h"

namespace Ui {
class configDialog;
}

class configDialog : public QDialog
{
    Q_OBJECT

public:
    explicit configDialog(QWidget *parent = 0);
    ~configDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_reset_clicked();

private:
    Ui::configDialog *ui;
    config *cnf;
};

#endif // CONFIGDIALOG_H
