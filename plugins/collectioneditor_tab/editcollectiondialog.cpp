#include <iostream>

#include "editcollectiondialog.h"
#include "ui_editcollectiondialog.h"

EditCollectionDialog::EditCollectionDialog(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    _collection(Collection(db)),
    ui(new Ui::EditCollectionDialog)
{
    ui->setupUi(this);
}

EditCollectionDialog::EditCollectionDialog(QSqlDatabase *db, Collection collection, QWidget *parent) :
    QDialog(parent),
    _collection(collection),
    ui(new Ui::EditCollectionDialog)
{
    ui->setupUi(this);
    if (_collection.isSet(NULLMASK_COLLECTION_NAME))
        ui->name->setText(_collection.getQStringValue(NULLMASK_COLLECTION_NAME));

    if (_collection.isSet(NULLMASK_COLLECTION_DESCRIPTION))
        ui->description->setText(_collection.getQStringValue(NULLMASK_COLLECTION_DESCRIPTION));
}

EditCollectionDialog::~EditCollectionDialog()
{
    delete ui;
}

void EditCollectionDialog::on_buttonBox_accepted()
{
    // only save if you specified a name.
    if (!ui->name->text().isEmpty()) {
        _collection.setQStringValue(NULLMASK_COLLECTION_NAME, ui->name->text());
        _collection.setQStringValue(NULLMASK_COLLECTION_DESCRIPTION, ui->description->text());
        _collection.save();
    }
}

void EditCollectionDialog::on_buttonBox_rejected()
{
    std::cout << "Cancel" << std::endl;
}
