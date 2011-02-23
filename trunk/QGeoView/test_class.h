#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <QObject>

class test_class : public QObject
{
    Q_OBJECT
public:
    explicit test_class(QObject *parent = 0);

signals:

public slots:

};

#endif // TEST_CLASS_H
