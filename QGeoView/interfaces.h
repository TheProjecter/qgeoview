#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>
#include <QSqlDatabase>

#define COMPATIBLE_NO       0
#define COMPATIBLE_YES      1
#define COMPATIBLE_MAYBE    2

class ReadInterface
{
public:
    virtual void setup(QSqlDatabase *db) = 0;
    virtual QString name() = 0;
    virtual void read(QFile *file) = 0;
private:
    QSqlDatabase *_db;
};

class WriteInterface
{
public:
    virtual void setup(QSqlDatabase *db) { _db = db; }
    virtual QString name() = 0;
    virtual void write(QFile &file, int collection) = 0;
private:
    QSqlDatabase *_db;
};

class ModeInterface
{
public:
    virtual ~ModeInterface() {}
    virtual QString name() = 0;
public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void selected() = 0;
    virtual void deselected() = 0;
};

Q_DECLARE_INTERFACE(ReadInterface, "org.homelinux.darwinsurvivor.QGeoView.ReadInterface");
Q_DECLARE_INTERFACE(WriteInterface, "org.homelinux.darwinsurvivor.QGeoView.WriteInterface");
Q_DECLARE_INTERFACE(ModeInterface, "org.homelinux.darwinsurvivor.QGeoView.ModeInterface");

#endif
