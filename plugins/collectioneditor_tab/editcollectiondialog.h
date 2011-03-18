#ifndef EDITCOLLECTIONDIALOG_H
#define EDITCOLLECTIONDIALOG_H

#include <QDialog>
#include "db/collection.h"

namespace Ui {
    class EditCollectionDialog;
}

class EditCollectionDialog : public QDialog
{
    Q_OBJECT

public:
    EditCollectionDialog(QSqlDatabase *db, Collection *collection, QWidget *parent = 0);
    EditCollectionDialog(QSqlDatabase *db, QWidget *parent = 0);
    ~EditCollectionDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Collection *_collection;
    Ui::EditCollectionDialog *ui;
};

#endif // EDITCOLLECTIONDIALOG_H
