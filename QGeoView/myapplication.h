#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QApplication>

class MyApplication : public QApplication
{
    Q_OBJECT
public:
    MyApplication(int argc, char *argv[]);
    bool notify(QObject *rec, QEvent *ev);
};

#endif // MYAPPLICATION_H
