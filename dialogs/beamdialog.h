#ifndef BEAMDIALOG_H
#define BEAMDIALOG_H

#include <QDialog>

#include "utils/qtbeamitem.h"

namespace Ui {
class beamDialog;
}

class beamDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit beamDialog(QWidget *parent = 0);
    explicit beamDialog(QWidget *parent, qtbeamitem *bi);
    ~beamDialog();

    qtbeamitem *bi;
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::beamDialog *ui;
};

#endif // BEAMDIALOG_H
