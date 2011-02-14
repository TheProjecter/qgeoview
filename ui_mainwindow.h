/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Feb 14 06:55:47 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>
#include "MarbleWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Quit;
    QAction *actionTest;
    QAction *action_Open;
    QAction *actionSave;
    QAction *action_Waypoints;
    QAction *action_Tracks;
    QAction *action_Routes;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QTreeView *tree;
    QTabWidget *tabWidget;
    QWidget *map_tab;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *map_view_selector;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *map_source_selector_2;
    Marble::MarbleWidget *map;
    QWidget *tab_info;
    QVBoxLayout *verticalLayout_6;
    QFrame *blank_info;
    QVBoxLayout *verticalLayout_10;
    QTextBrowser *blank_info_text;
    QFrame *waypoint_info;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *cache_info_name_2;
    QLabel *cache_info_gc_2;
    QTextBrowser *cache_info_description_2;
    QFrame *track_info;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *track_info_text;
    QFrame *route_info;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *route_info_text;
    QWidget *tab_cache_page;
    QVBoxLayout *verticalLayout_4;
    QWebView *cache_page;
    QMenuBar *menuBar;
    QMenu *menu_Application;
    QMenu *menu_View;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(601, 564);
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        MainWindow->setFont(font);
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        QFont font1;
        action_Quit->setFont(font1);
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QString::fromUtf8("actionTest"));
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        action_Waypoints = new QAction(MainWindow);
        action_Waypoints->setObjectName(QString::fromUtf8("action_Waypoints"));
        action_Waypoints->setCheckable(true);
        action_Tracks = new QAction(MainWindow);
        action_Tracks->setObjectName(QString::fromUtf8("action_Tracks"));
        action_Tracks->setCheckable(true);
        action_Routes = new QAction(MainWindow);
        action_Routes->setObjectName(QString::fromUtf8("action_Routes"));
        action_Routes->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setFont(font);
        centralWidget->setMouseTracking(false);
        centralWidget->setAcceptDrops(false);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        tree = new QTreeView(layoutWidget);
        tree->setObjectName(QString::fromUtf8("tree"));
        tree->setFont(font);

        verticalLayout->addWidget(tree);

        splitter->addWidget(layoutWidget);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setFont(font);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        map_tab = new QWidget();
        map_tab->setObjectName(QString::fromUtf8("map_tab"));
        verticalLayout_9 = new QVBoxLayout(map_tab);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        map_view_selector = new QComboBox(map_tab);
        map_view_selector->setObjectName(QString::fromUtf8("map_view_selector"));

        horizontalLayout_4->addWidget(map_view_selector);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        map_source_selector_2 = new QComboBox(map_tab);
        map_source_selector_2->setObjectName(QString::fromUtf8("map_source_selector_2"));
        map_source_selector_2->setMinimumSize(QSize(0, 0));

        horizontalLayout_4->addWidget(map_source_selector_2);


        verticalLayout_9->addLayout(horizontalLayout_4);

        map = new Marble::MarbleWidget(map_tab);
        map->setObjectName(QString::fromUtf8("map"));

        verticalLayout_9->addWidget(map);

        tabWidget->addTab(map_tab, QString());
        tab_info = new QWidget();
        tab_info->setObjectName(QString::fromUtf8("tab_info"));
        verticalLayout_6 = new QVBoxLayout(tab_info);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        blank_info = new QFrame(tab_info);
        blank_info->setObjectName(QString::fromUtf8("blank_info"));
        blank_info->setFrameShape(QFrame::StyledPanel);
        blank_info->setFrameShadow(QFrame::Raised);
        verticalLayout_10 = new QVBoxLayout(blank_info);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        blank_info_text = new QTextBrowser(blank_info);
        blank_info_text->setObjectName(QString::fromUtf8("blank_info_text"));

        verticalLayout_10->addWidget(blank_info_text);


        verticalLayout_6->addWidget(blank_info);

        waypoint_info = new QFrame(tab_info);
        waypoint_info->setObjectName(QString::fromUtf8("waypoint_info"));
        waypoint_info->setEnabled(true);
        waypoint_info->setFrameShape(QFrame::StyledPanel);
        waypoint_info->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(waypoint_info);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cache_info_name_2 = new QLabel(waypoint_info);
        cache_info_name_2->setObjectName(QString::fromUtf8("cache_info_name_2"));

        horizontalLayout_2->addWidget(cache_info_name_2);

        cache_info_gc_2 = new QLabel(waypoint_info);
        cache_info_gc_2->setObjectName(QString::fromUtf8("cache_info_gc_2"));
        cache_info_gc_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(cache_info_gc_2);


        verticalLayout_7->addLayout(horizontalLayout_2);

        cache_info_description_2 = new QTextBrowser(waypoint_info);
        cache_info_description_2->setObjectName(QString::fromUtf8("cache_info_description_2"));
        cache_info_description_2->setFont(font);

        verticalLayout_7->addWidget(cache_info_description_2);


        verticalLayout_6->addWidget(waypoint_info);

        track_info = new QFrame(tab_info);
        track_info->setObjectName(QString::fromUtf8("track_info"));
        track_info->setFrameShape(QFrame::StyledPanel);
        track_info->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(track_info);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        track_info_text = new QTextEdit(track_info);
        track_info_text->setObjectName(QString::fromUtf8("track_info_text"));

        verticalLayout_2->addWidget(track_info_text);


        verticalLayout_6->addWidget(track_info);

        route_info = new QFrame(tab_info);
        route_info->setObjectName(QString::fromUtf8("route_info"));
        route_info->setFrameShape(QFrame::StyledPanel);
        route_info->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(route_info);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        route_info_text = new QTextEdit(route_info);
        route_info_text->setObjectName(QString::fromUtf8("route_info_text"));

        verticalLayout_3->addWidget(route_info_text);


        verticalLayout_6->addWidget(route_info);

        tabWidget->addTab(tab_info, QString());
        tab_cache_page = new QWidget();
        tab_cache_page->setObjectName(QString::fromUtf8("tab_cache_page"));
        verticalLayout_4 = new QVBoxLayout(tab_cache_page);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        cache_page = new QWebView(tab_cache_page);
        cache_page->setObjectName(QString::fromUtf8("cache_page"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cache_page->sizePolicy().hasHeightForWidth());
        cache_page->setSizePolicy(sizePolicy);
        cache_page->setFont(font);
        cache_page->setUrl(QUrl("http://www.geocaching.com/"));

        verticalLayout_4->addWidget(cache_page);

        tabWidget->addTab(tab_cache_page, QString());
        splitter->addWidget(tabWidget);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 601, 21));
        menu_Application = new QMenu(menuBar);
        menu_Application->setObjectName(QString::fromUtf8("menu_Application"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMinimumSize(QSize(0, 27));
        mainToolBar->setMaximumSize(QSize(16777215, 16777215));
        mainToolBar->setFont(font);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Application->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menu_Application->addAction(action_Open);
        menu_Application->addAction(actionSave);
        menu_Application->addAction(action_Quit);
        menu_View->addAction(action_Waypoints);
        menu_View->addAction(action_Tracks);
        menu_View->addAction(action_Routes);
        mainToolBar->addAction(action_Quit);
        mainToolBar->addAction(action_Open);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionTest);

        retranslateUi(MainWindow);
        QObject::connect(map_source_selector_2, SIGNAL(currentIndexChanged(QString)), MainWindow, SLOT(MapSourceChanged(QString)));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GSDS", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Quit->setToolTip(QApplication::translate("MainWindow", "Quit The Application", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionTest->setText(QApplication::translate("MainWindow", "Test", 0, QApplication::UnicodeUTF8));
        actionTest->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        action_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        action_Waypoints->setText(QApplication::translate("MainWindow", "&Waypoints", 0, QApplication::UnicodeUTF8));
        action_Tracks->setText(QApplication::translate("MainWindow", "&Tracks", 0, QApplication::UnicodeUTF8));
        action_Routes->setText(QApplication::translate("MainWindow", "&Routes", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "All", 0, QApplication::UnicodeUTF8)
        );
        map_view_selector->clear();
        map_view_selector->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ALL", 0, QApplication::UnicodeUTF8)
        );
        map_source_selector_2->clear();
        map_source_selector_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Open Street Map", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Plain", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Blue Marble", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        map->setToolTip(QApplication::translate("MainWindow", "The Earth", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        map->setWhatsThis(QApplication::translate("MainWindow", "The Marble widget displays a virtual globe.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        map->setProperty("mapThemeId", QVariant(QApplication::translate("MainWindow", "earth/openstreetmap/openstreetmap.dgml", 0, QApplication::UnicodeUTF8)));
        tabWidget->setTabText(tabWidget->indexOf(map_tab), QApplication::translate("MainWindow", "Map", 0, QApplication::UnicodeUTF8));
        blank_info_text->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Please select an item in the list on the left.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        cache_info_name_2->setText(QApplication::translate("MainWindow", "Cache Name", 0, QApplication::UnicodeUTF8));
        cache_info_gc_2->setText(QApplication::translate("MainWindow", "GC000000", 0, QApplication::UnicodeUTF8));
        cache_info_description_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Description</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_info), QApplication::translate("MainWindow", "Info", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_cache_page), QApplication::translate("MainWindow", "Web Page", 0, QApplication::UnicodeUTF8));
        menu_Application->setTitle(QApplication::translate("MainWindow", "&Application", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
