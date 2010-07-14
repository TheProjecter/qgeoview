
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QSortFilterProxyModel>
#include "cachetable.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void openFile(QString filename);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QSortFilterProxyModel *_cacheTableProxy;
    CacheTable *_cacheTable;

private slots:
    void on_action_Open_triggered();
    void on_actionTest_triggered();
    void on_action_Quit_triggered();

public slots:
    void view_row_selected(const QModelIndex & index);
    void cache_selected(Cache *cache);

signals:
    void row_selected(const QModelIndex & index);
    void cache_changed(Cache *);
    void cache_lat_changed(double);
    void cache_lon_changed(double);
    void cache_number_changed(QString);
    void cache_name_changed(QString);
    void cache_long_name_changed(QString);
    void cache_url_changed(QString);
    void cache_url_name_changed(QString);
    void cache_placed_by_changed(QString);
    void cache_owner_changed(QString);
    void cache_terrain_changed(double);
    void cache_type_changed(QString);
    void cache_container_changed(QString);
    void cache_difficulty_changed(double);
    void cache_desc_long_changed(QString);
    void cache_desc_long_html_changed(QString);
    void cache_desc_short_changed(QString);
    void cache_desc_short_html_changed(QString);
    void cache_hint_changed(QString);
    void quit();
};

#endif // MAINWINDOW_H
