#ifndef TIPSDIALOG_H
#define TIPSDIALOG_H

#include <QDialog>
#include "ui_tips-dialog.h"

namespace Ui {
class TipsDialog;
}

class TipsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TipsDialog(QWidget *parent = 0);
    ~TipsDialog();

private slots:
    void okButtonClicked();
private:
    Ui::TipsDialog *ui;
};

#endif // TIPSDIALOG_H
