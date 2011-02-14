#include "newitemdialog.h"
#include "ui_newitemdialog.h"

NewItemDialog::NewItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewItemDialog)
{
    ui->setupUi(this);
}

NewItemDialog::~NewItemDialog()
{
    delete ui;
}

void NewItemDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
