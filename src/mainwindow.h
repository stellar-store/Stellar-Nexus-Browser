#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <QStackedWidget>
#include <QSettings>
#include <QSystemTrayIcon>
#include "navbar.h"
#include "tabbar.h"
#include "bookmarkmanager.h"
#include "downloadmanager.h"
#include "historymanager.h"

class BrowserPage;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openUrl(const QUrl &url);
    BrowserPage* currentPage() const;
    BrowserPage* pageAt(int index) const;
    DownloadManager* downloadManager() { return m_downloadManager; }
    BookmarkManager* bookmarkManager() { return m_bookmarkManager; }
    HistoryManager* historyManager() { return m_historyManager; }
    QSettings* settings() { return m_settings; }

public slots:
    void newTab(const QUrl &url = QUrl("nexus://home"));
    void closeTab(int index);
    void navigateTo(const QString &urlStr);
    void onBack();
    void onForward();
    void onReload();
    void onHome();
    void onTranslate();
    void onTabChanged(int index);
    void onUrlChanged(const QUrl &url);
    void onTitleChanged(const QString &title);
    void onLoadProgress(int progress);
    void onLoadFinished(bool ok);
    void showBookmarks();
    void showDownloads();
    void showSettings();
    void showHistory();
    void toggleFullScreen();
    void addBookmark();

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void setupUi();
    void setupConnections();
    void applyTheme();
    void loadSession();
    void saveSession();
    void updateWindowTitle(const QString &title);
    void connectPage(BrowserPage *page);

    NexusTabBar       *m_tabBar       = nullptr;
    NavBar            *m_navBar       = nullptr;
    QWidget           *m_centralWidget= nullptr;
    QStackedWidget    *m_pageStack    = nullptr;  // holds BrowserPage widgets

    BookmarkManager   *m_bookmarkManager = nullptr;
    DownloadManager   *m_downloadManager = nullptr;
    HistoryManager    *m_historyManager  = nullptr;
    QSettings         *m_settings        = nullptr;

    QAction *m_fullScreenAction = nullptr;
};
