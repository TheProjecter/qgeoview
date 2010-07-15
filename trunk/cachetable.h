#ifndef CACHETABLE_H
#define CACHETABLE_H

#include <QDateTime>
#include <QTableView>
#include <QAbstractTableModel>
#include <QDomDocument>
#include <QSortFilterProxyModel>

#define CACHETABLE_COLUMN_SELECTED 0
#define CACHETABLE_COLUMN_NUMBER 1
#define CACHETABLE_COLUMN_NAME 2
#define CACHETABLE_COLUMNS 3

typedef struct {
    QDateTime datetime;
    QString type;
    QString poster;
    bool text_encoded;
    QString text;
} CacheLog;

typedef struct {
    QDomElement xmlElement;
    bool selected;
    double latitude;
    double longitude;
    QString number;
    QString name;
    QString long_name;
    QString url;
    QString url_name;
    QString placed_by;
    QString owner;
    float terrain;
    QString type;
    QString container;
    float difficulty;
    bool desc_short_html;
    QString desc_short;
    bool desc_long_html;
    QString desc_long;
    QString hint;
    QList<CacheLog*> logs;
} Cache;

class CacheTable : public QAbstractTableModel
{
Q_OBJECT
public:
    CacheTable(QObject *parent = 0);
    CacheTable(QTableView *view, QSortFilterProxyModel *proxy, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int position, int rows, const QModelIndex &index);
    bool removeRows(int position, int rows, const QModelIndex &index);
    void addCache(Cache *cache);
    void openGPX(QDomDocument *doc);
    QList<Cache*> selected_caches();

private:
    QList<Cache*> _caches;
    QTableView *_view;
    QSortFilterProxyModel *_proxy;

signals:
    void cache_selected(Cache *cache);

public slots:
    void row_selected(const QModelIndex & index);

};

#endif // CACHETABLE_H
