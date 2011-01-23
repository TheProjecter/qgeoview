#ifndef ACCURACY_H
#define ACCURACY_H

#include <QObject>
#include "databaseobject.h"

class Accuracy : public DatabaseObject
{
    Q_OBJECT
public:
    explicit Accuracy(QObject *parent = 0);
    ~Accuracy();

signals:

public slots:
    void save();
    void remove();
private:
    QString _fix;
    int _satelites;
    float _horizontalDOP;
    float _verticalDOP;
    float _positionDOP;
    float _ageOfDGPSData;
    int _DGPSID;
};

#endif // ACCURACY_H
