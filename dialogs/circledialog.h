#ifndef CIRCLEDIALOG_H
#define CIRCLEDIALOG_H

#include <QDialog>

namespace Ui {
class circleDialog;
}

class circleDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit circleDialog(QWidget *parent = 0);
    ~circleDialog();
    
private:
    Ui::circleDialog *ui;
};

#endif // CIRCLEDIALOG_H
