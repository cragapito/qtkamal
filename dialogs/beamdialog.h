#ifndef BEAMDIALOG_H
#define BEAMDIALOG_H

#include <QDialog>

namespace Ui {
class beamDialog;
}

class beamDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit beamDialog(QWidget *parent = 0);
    ~beamDialog();
    
private:
    Ui::beamDialog *ui;
};

#endif // BEAMDIALOG_H
