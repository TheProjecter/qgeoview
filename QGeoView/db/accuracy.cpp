#include "accuracy.h"

Accuracy::Accuracy(QObject *parent) :
    DatabaseObject(parent)
{
}

Accuracy::~Accuracy()
{
    save();
}

void Accuracy::save()
{
    emit saved();
}

void Accuracy::remove()
{
    emit removed();
}
