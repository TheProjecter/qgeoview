#ifndef NEWITEMDIALOG_H
#define NEWITEMDIALOG_H

#include <QDialog>

namespace Ui {
    class NewItemDialog;
}

class NewItemDialog : public QDialog {
    Q_OBJECT
public:
    NewItemDialog(QWidget *parent = 0);
    ~NewItemDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::NewItemDialog *ui;
};

#endif // NEWITEMDIALOG_H
