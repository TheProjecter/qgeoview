#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>

class DummyPlugin
{
public:
    virtual void print() = 0;
};

class DummyPluginFactory
{
public:
    virtual DummyPlugin *get_plugin() = 0;
};

Q_DECLARE_INTERFACE(DummyPluginFactory, "org.homelinux.darwinsurvivor.QGeoView.DummyPluginFactory");

#endif
