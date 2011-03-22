#include <iostream>

#include "editcollectiondialog.h"
#include "ui_editcollectiondialog.h"

EditCollectionDialog::EditCollectionDialog(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    _collection(new Collection(db)),
    ui(new Ui::EditCollectionDialog)
{
    ui->setupUi(this);
}

EditCollectionDialog::EditCollectionDialog(Collection *collection, QWidget *parent) :
    QDialog(parent),
    _collection(collection),
    ui(new Ui::EditCollectionDialog)
{
    ui->setupUi(this);
    if (_collection->isSet(NULLMASK_COLLECTION_NAME))
        ui->name->setText(_collection->getName());

    if (_collection->isSet(NULLMASK_COLLECTION_DESCRIPTION))
        ui->description->setText(_collection->getDescription());
}

EditCollectionDialog::~EditCollectionDialog()
{
    delete ui;
}

void EditCollectionDialog::on_buttonBox_accepted()
{
    // only save if you specified a name.
    if (!ui->name->text().isEmpty()) {
        _collection->setName(ui->name->text());
        _collection->setDescription(ui->description->text());
        _collection->save();
    }
}

void EditCollectionDialog::on_buttonBox_rejected()
{
    std::cout << "Cancel" << std::endl;
}
