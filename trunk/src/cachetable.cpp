/******************************************************************************
** Copyright 2010 Doug Penner
**
** This file is part of QGeoView.
**
** QGeoView is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QGeoView is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QGeoView.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


#include <QMessageBox>
#include <iostream>
#include "cachetable.h"

/*
  Creates an empty cache table with no caches
*/
CacheTable::CacheTable(QObject *parent) :
    QAbstractTableModel(parent)
{
}


/*
  Creates a cache table holding the specified caches
*/
CacheTable::CacheTable(QTableView *view, QSortFilterProxyModel *proxy, QObject *parent) :
        QAbstractTableModel(parent), _view(view), _proxy(proxy)
{
}


/*
  Returns the total number of rows (number of caches)
*/
int CacheTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _caches.size();
}


/*
  Returns the total number of columns (static)
*/
int CacheTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return CACHETABLE_COLUMNS;
}


/*
  Returns the data from a single cell
*/
QVariant CacheTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= _caches.size() || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole) {
        Cache *cache = _caches.at(index.row());
        switch (index.column()) {
            case CACHETABLE_COLUMN_NUMBER:
                return cache->number;
            case CACHETABLE_COLUMN_NAME:
                return cache->name;
            default:
                return QVariant();
        }
    } else if (role == Qt::CheckStateRole) {
        Cache *cache = _caches.at(index.row());
        switch (index.column()) {
            case CACHETABLE_COLUMN_SELECTED:
                return Qt::CheckState(cache->selected);
            default:
                return QVariant();
        }
    }
    return QVariant();
}


/*
  Returns the name of a column given the index value
*/
QVariant CacheTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case CACHETABLE_COLUMN_NUMBER:
                return tr("Number");
            case CACHETABLE_COLUMN_NAME:
                return tr("Name");
            default:
                return QVariant();
        }
    }
    return QVariant();
}


bool CacheTable::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; rows++) {
        Cache *cache = new Cache;
        _caches.insert(position, cache);
    }
    endInsertRows();
    return true;
}


bool CacheTable::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        _caches.removeAt(position);
    }

    endRemoveRows();
    return true;
}


bool CacheTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    int row = index.row();
    Cache *cache = _caches.at(row);
    switch (index.column()) {
        case CACHETABLE_COLUMN_SELECTED:
            if (role == Qt::EditRole || role == Qt::CheckStateRole)
                cache->selected = !(cache->selected);
            break;
        case CACHETABLE_COLUMN_NUMBER:
            if (role == Qt::EditRole)
                cache->number = value.toString();
            break;
        case CACHETABLE_COLUMN_NAME:
            if (role == Qt::EditRole)
                cache->name = value.toString();
            break;
        default:
            return false;
    }

    _caches.replace(row, cache);
    emit(dataChanged(index, index));

    return true;
}


Qt::ItemFlags CacheTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    Qt::ItemFlags retval = QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    if (index.column() == CACHETABLE_COLUMN_SELECTED)
        retval |= Qt::ItemIsUserCheckable;
    return retval;
}


void CacheTable::row_selected(const QModelIndex & index)
{
    if (!index.isValid())
        return;
    if (index.row() >= _caches.size() || index.row() < 0)
        return;
    emit activate_cache(_caches.at(index.row()));
}


void CacheTable::addCache(Cache *cache)
{
    int size = _caches.size();
    beginInsertRows(QModelIndex(), size, size);
    _caches.insert(size, cache);
    endInsertRows();
}


void CacheTable::openGPX(QDomDocument *doc)
{
    QDomElement gpx_element = doc->documentElement();
    if (gpx_element.tagName() != "gpx")
    {
        std::cerr << "Not an XML file" << std::endl;
        return;
    }

    // read data
    QDomNodeList wpt_list = gpx_element.elementsByTagName("wpt");
    for (int wpt_i = 0; wpt_i < wpt_list.count(); ++wpt_i)
    {
        QDomElement wpt_element = wpt_list.item(wpt_i).toElement();
        QDomElement cache_element = wpt_element.elementsByTagName("groundspeak:cache").item(0).toElement();
        Cache *cache = new Cache;
        cache->xmlElement = wpt_element;
        cache->selected = false;
        cache->latitude = wpt_element.attribute("lat").toDouble();
        cache->longitude = wpt_element.attribute("lon").toDouble();
        cache->number = wpt_element.elementsByTagName("name").item(0).firstChild().nodeValue();
        cache->name = cache_element.elementsByTagName("groundspeak:name").item(0).firstChild().nodeValue();
        cache->long_name = wpt_element.elementsByTagName("desc").item(0).firstChild().nodeValue();
        cache->url = wpt_element.elementsByTagName("url").item(0).firstChild().nodeValue();
        cache->url_name = wpt_element.elementsByTagName("name").item(0).firstChild().nodeValue();
        cache->placed_by = cache_element.elementsByTagName("groundspeak:placed_by").item(0).firstChild().nodeValue();
        cache->owner = cache_element.elementsByTagName("groundspeak:owner").item(0).firstChild().nodeValue();
        cache->type = cache_element.elementsByTagName("groundspeak:type").item(0).firstChild().nodeValue();
        cache->container = cache_element.elementsByTagName("groundspeak:container").item(0).firstChild().nodeValue();
        cache->difficulty = cache_element.elementsByTagName("groundspeak:difficulty").item(0).firstChild().nodeValue().toFloat();
        cache->terrain = cache_element.elementsByTagName("groundspeak:terrain").item(0).firstChild().nodeValue().toFloat();
        QDomElement short_description_element = cache_element.elementsByTagName("groundspeak:short_description").item(0).toElement();
        cache->desc_short_html = short_description_element.attribute("html", "False") == "True";
        cache->desc_short = short_description_element.firstChild().nodeValue();
        QDomElement long_description_element = cache_element.elementsByTagName("groundspeak:long_description").item(0).toElement();
        cache->desc_long_html = long_description_element.attribute("html", "False") == "True";
        cache->desc_long = long_description_element.firstChild().nodeValue();
        cache->hint = cache_element.elementsByTagName("groundspeak:encoded_hints").item(0).firstChild().nodeValue();
        QDomNodeList cache_log_list = cache_element.elementsByTagName("groundspeak:logs").item(0).toElement().elementsByTagName("groundspeak:log");
        for (int cache_log_i = 0; cache_log_i < cache_log_list.count(); ++cache_log_i)
        {
            QDomElement log_element = cache_log_list.item(cache_log_i).toElement();
            CacheLog *log = new CacheLog;
            log->datetime = QDateTime::fromString(log_element.elementsByTagName("groundspeak:date").item(0).firstChild().nodeValue());
            log->type = log_element.elementsByTagName("groundspeak:type").item(0).firstChild().nodeValue();
            log->poster = log_element.elementsByTagName("groundspeak:finder").item(0).firstChild().nodeValue();
            QDomElement log_text_element = log_element.elementsByTagName("groundspeak:text").item(0).toElement();
            log->text_encoded = log_text_element.attribute("encoded", "False") == "True";
            log->text = log_text_element.nodeValue();
            cache->logs.append(log);
        }
        addCache(cache);
        emit cache_added(cache);
    }
}


QList<Cache*> CacheTable::selected_caches()
{
    QList<Cache*> selected;
    Cache *cache;
    for (int i = 0; i < _caches.count(); ++i) {
        cache = _caches.at(i);
        if (cache->selected)
            selected.append(cache);
    }
    return selected;
}

Cache *CacheTable::cacheByNumber(QString number)
{
    Cache *cache;
    for (int i=0; i < _caches.count(); ++ i) {
        cache = _caches.at(i);
        if (cache->number == number)
            return cache;
    }
    return NULL;
}

QDomDocument *CacheTable::genGPX()
{
    // create gpx structure
    QList<Cache*> caches = selected_caches();
    if (caches.empty())
        return NULL;
    Cache *cache = caches.at(0);
    double minlat = cache->latitude;
    double minlon = cache->longitude;
    double maxlat = minlat;
    double maxlon = minlon;
    if (caches.count() > 1) {
        for (int i = 1; i < caches.count(); ++i) {
            cache = caches.at(i);
            if (cache->latitude < minlat) {
                minlat = cache->latitude;
            }
            if (cache->latitude > maxlat) {
                maxlat = cache->latitude;
            }
            if (cache->longitude < minlon) {
                minlon = cache->longitude;
            }
            if (cache->longitude > maxlon) {
                maxlon = cache->longitude;
            }
        }
    }
    QDomDocument *doc = new QDomDocument("Gpx");
    QDomElement gpx = doc->createElement("gpx");
    gpx.setAttribute("xmlns:xsi", "http://www.w3.org/2010/XMLSchema-instance");
    gpx.setAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
    gpx.setAttribute("version", "1.0");
    gpx.setAttribute("creator", "qgeoview");
    gpx.setAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd http://www.groundspeak.com/cache/1/0 http://www.groundspeak.com/cache/1/0/cache.xsd");
    gpx.setAttribute("xmlns", "http://www.topografix.com/GPS/1/0");
    QDomElement name = doc->createElement("name");
    name.appendChild(doc->createTextNode("New Query"));
    gpx.appendChild(name);
    QDomElement desc = doc->createElement("desc");
    desc.appendChild(doc->createTextNode("Geocaching file modified by qgeoview"));
    gpx.appendChild(desc);
    QDomElement author = doc->createElement("author");
    author.appendChild(doc->createTextNode("Doug Penner"));
    gpx.appendChild(author);
    QDomElement email = doc->createElement("email");
    email.appendChild(doc->createTextNode("darwinsurvivor@gmail.com"));
    gpx.appendChild(email);
    QDomElement time = doc->createElement("time");
    time.appendChild(doc->createTextNode("2010-06-18T14:37:42.2184239Z"));    // TODO: add actual time
    gpx.appendChild(time);
    QDomElement keywords = doc->createElement("keywords");
    keywords.appendChild(doc->createTextNode("cache, geocache, groundspeak"));
    gpx.appendChild(keywords);
    QDomElement bounds = doc->createElement("bounds");
    bounds.setAttribute("minlat", minlat);
    bounds.setAttribute("minlon", minlon);
    bounds.setAttribute("maxlat", maxlat);
    bounds.setAttribute("maxlon", maxlon);
    gpx.appendChild(bounds);

    // add caches
    for (int i = 0; i < caches.count(); ++i) {
        cache = caches.at(i);
        gpx.appendChild(cache->xmlElement);
    }
    doc->appendChild(gpx);
    return doc;
}
