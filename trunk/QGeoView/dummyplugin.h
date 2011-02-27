#ifndef DUMMYPLUGIN_H
#define DUMMYPLUGIN_H

#include <QtPlugin>

class DummyPlugin : public QObject
{
    Q_OBJECT
public:
    DummyPlugin();
    virtual QString name() = 0;
};

class DummyPluginFactory
{
public:
    virtual DummyPlugin *get_plugin() = 0;
};

Q_DECLARE_INTERFACE(DummyPluginFactory, "org.homelinux.darwinsurvivor.QGeoView.DummyPluginFactory");

#endif // DUMMYPLUGIN_H
