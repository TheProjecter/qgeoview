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
                cache->selected = value.toBool();
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
    emit cache_selected(_caches.at(index.row()));
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

