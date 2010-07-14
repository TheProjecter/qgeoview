#include <QDomDocument>
#include <QFile>
#include <iostream>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _cacheTableProxy(new QSortFilterProxyModel(this)),
    _cacheTable(new CacheTable(ui->caches_list, _cacheTableProxy))
{
    ui->setupUi(this);

    _cacheTableProxy->setSourceModel(_cacheTable);
    _cacheTableProxy->setDynamicSortFilter(true);

    ui->caches_list->setModel(_cacheTableProxy);

    // TODO: Remove next line
    //openFile("test.gpx");

    connect(ui->caches_list, SIGNAL(clicked(QModelIndex)), this, SLOT(view_row_selected(QModelIndex)));
    connect(this, SIGNAL(row_selected(QModelIndex)), _cacheTable, SLOT(row_selected(QModelIndex)));
    connect(_cacheTable, SIGNAL(cache_selected(Cache*)), this, SLOT(cache_selected(Cache*)));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::on_action_Quit_triggered()
{
    emit quit();
}


void MainWindow::cache_selected(Cache *cache)
{
    emit cache_changed(cache);
    emit cache_lat_changed(cache->latitude);
    emit cache_lon_changed(cache->longitude);
    emit cache_number_changed(cache->number);
    emit cache_name_changed(cache->name);
    emit cache_long_name_changed(cache->long_name);
    emit cache_url_changed(cache->url);
    emit cache_url_name_changed(cache->url_name);
    emit cache_placed_by_changed(cache->placed_by);
    emit cache_owner_changed(cache->owner);
    emit cache_terrain_changed(cache->terrain);
    emit cache_type_changed(cache->type);
    emit cache_container_changed(cache->container);
    emit cache_difficulty_changed(cache->difficulty);
    if (cache->desc_long_html)
        emit cache_desc_long_html_changed(cache->desc_long);
    else
        emit cache_desc_long_changed(cache->desc_long);
    if (cache->desc_long_html)
        emit cache_desc_short_html_changed(cache->desc_short);
    else
        emit cache_desc_short_changed(cache->desc_short);
    emit cache_hint_changed(cache->hint);
    ui->cache_page->setUrl(cache->url);
    ui->map->setUrl(tr("http://local.google.ca/?ll=%1,%2").arg(QString::number(cache->latitude), QString::number(cache->longitude)));
}


void MainWindow::on_actionTest_triggered()
{
}


void MainWindow::view_row_selected(const QModelIndex & index)
{
    if (!index.isValid())
        return;
    emit row_selected(_cacheTableProxy->mapToSource(index));
}

void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isNull())
        return;
    openFile(filename);
}


void MainWindow::openFile(QString filename)
{
    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }

    if (!doc.setContent(&file))
    {
        std::cerr << "Unusable file" << std::endl;
        file.close();
        return;
    }
    file.close();
    _cacheTable->openGPX(&doc);
}
