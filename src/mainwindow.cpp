#include "mainwindow.h"
#include "browserpage.h"
#include "settingsdialog.h"
#include "translationmanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QShortcut>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QStyle>
#include <QTimer>
#include <QLabel>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_settings        = new QSettings("StellarNexusBrowser", "Stellar", this);
    m_bookmarkManager = new BookmarkManager(this);
    m_downloadManager = new DownloadManager(this);
    m_historyManager  = new HistoryManager(this);

    // Load language setting
    QString savedLanguage = m_settings->value("app/language", "English").toString();
    TranslationManager::instance().setLanguage(savedLanguage);

    setupUi();
    setupConnections();
    applyTheme();

    // Start with home tab
    newTab();

    resize(m_settings->value("window/size", QSize(1280, 800)).toSize());
    if (m_settings->value("window/maximized", false).toBool())
        showMaximized();
}

MainWindow::~MainWindow() {
    saveSession();
}

void MainWindow::setupUi() {
    setWindowTitle("Nexus");

    // Use a frameless window so we can render our own titlebar-like controls in the tab bar.
    // This removes the native title bar (minimize/maximize/close) so the tab bar buttons take over.
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    setMinimumSize(800, 500);

    // Remove default menu bar for a cleaner look
    menuBar()->hide();
    statusBar()->hide();

    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    auto *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Tab bar
    m_tabBar = new NexusTabBar(this);
    m_tabBar->setFramelessMode(true); // Enable dragging from the tab bar and use its window control buttons
    mainLayout->addWidget(m_tabBar);

    // Navigation bar
    m_navBar = new NavBar(this);
    mainLayout->addWidget(m_navBar);

    // Page stack
    m_pageStack = new QStackedWidget(this);
    mainLayout->addWidget(m_pageStack);

    // Keyboard shortcuts
    new QShortcut(QKeySequence("Ctrl+T"),      this, [this]{ newTab(); });
    new QShortcut(QKeySequence("Ctrl+W"),      this, [this]{ closeTab(m_tabBar->currentIndex()); });
    new QShortcut(QKeySequence("Ctrl+L"),      this, [this]{ m_navBar->focusUrlBar(); });
    new QShortcut(QKeySequence("Alt+Left"),    this, [this]{ onBack(); });
    new QShortcut(QKeySequence("Alt+Right"),   this, [this]{ onForward(); });
    new QShortcut(QKeySequence("F5"),          this, [this]{ onReload(); });
    new QShortcut(QKeySequence("Ctrl+R"),      this, [this]{ onReload(); });
    new QShortcut(QKeySequence("F11"),         this, [this]{ toggleFullScreen(); });
    new QShortcut(QKeySequence("Ctrl+H"),      this, [this]{ showHistory(); });
    new QShortcut(QKeySequence("Ctrl+D"),      this, [this]{ addBookmark(); });
    new QShortcut(QKeySequence("Ctrl+B"),      this, [this]{ showBookmarks(); });
    new QShortcut(QKeySequence("Ctrl+J"),      this, [this]{ showDownloads(); });
    new QShortcut(QKeySequence("Ctrl+,"),      this, [this]{ showSettings(); });
    new QShortcut(QKeySequence("Ctrl+Tab"),    this, [this]{
        int next = (m_tabBar->currentIndex() + 1) % m_tabBar->count();
        m_tabBar->setCurrentIndex(next);
    });
    new QShortcut(QKeySequence("Ctrl+Shift+Tab"), this, [this]{
        int prev = (m_tabBar->currentIndex() - 1 + m_tabBar->count()) % m_tabBar->count();
        m_tabBar->setCurrentIndex(prev);
    });
}

void MainWindow::setupConnections() {
    connect(m_tabBar, &NexusTabBar::currentChanged,   this, &MainWindow::onTabChanged);
    connect(m_tabBar, &NexusTabBar::tabCloseRequested,this, &MainWindow::closeTab);
    connect(m_tabBar, &NexusTabBar::newTabRequested,  this, [this]{ newTab(); });
    connect(m_tabBar, &NexusTabBar::minimizeRequested,this, &MainWindow::showMinimized);
    connect(m_tabBar, &NexusTabBar::maximizeRequested,this, [this]{
        isMaximized() ? showNormal() : showMaximized();
    });
    connect(m_tabBar, &NexusTabBar::closeRequested,   this, &MainWindow::close);

    connect(m_navBar, &NavBar::navigate,    this, &MainWindow::navigateTo);
    connect(m_navBar, &NavBar::backClicked, this, &MainWindow::onBack);
    connect(m_navBar, &NavBar::forwardClicked, this, &MainWindow::onForward);
    connect(m_navBar, &NavBar::reloadClicked,  this, &MainWindow::onReload);
    connect(m_navBar, &NavBar::homeClicked,    this, &MainWindow::onHome);
    connect(m_navBar, &NavBar::bookmarkClicked,this, &MainWindow::addBookmark);
    connect(m_navBar, &NavBar::translateClicked, this, &MainWindow::onTranslate);
    connect(m_navBar, &NavBar::showBookmarks,  this, &MainWindow::showBookmarks);
    connect(m_navBar, &NavBar::showDownloads,  this, &MainWindow::showDownloads);
    connect(m_navBar, &NavBar::showSettings,   this, &MainWindow::showSettings);
}

void MainWindow::newTab(const QUrl &url) {
    auto *page = new BrowserPage(this);
    connectPage(page);

    int idx = m_pageStack->addWidget(page);
    m_tabBar->addNexusTab("New Tab");
    m_tabBar->setCurrentIndex(m_tabBar->count() - 1);
    m_pageStack->setCurrentIndex(idx);

    page->load(url);
}

void MainWindow::connectPage(BrowserPage *page) {
    connect(page, &BrowserPage::urlChanged,      this, &MainWindow::onUrlChanged);
    connect(page, &BrowserPage::titleChanged,    this, &MainWindow::onTitleChanged);
    connect(page, &BrowserPage::loadProgress,    this, &MainWindow::onLoadProgress);
    connect(page, &BrowserPage::loadFinished,    this, &MainWindow::onLoadFinished);
    connect(page, &BrowserPage::iconChanged,     this, [this, page](const QIcon &icon){
        int idx = m_pageStack->indexOf(page);
        if (idx >= 0) m_tabBar->setTabIcon(idx, icon);
    });
    connect(page, &BrowserPage::newTabRequested, this, [this](const QUrl &u){ newTab(u); });
    connect(page, &BrowserPage::downloadRequested, m_downloadManager, &DownloadManager::addDownload);
}

void MainWindow::closeTab(int index) {
    if (m_tabBar->count() <= 1) {
        qApp->quit();
        return;
    }
    auto *page = pageAt(index);
    m_tabBar->removeTab(index);
    m_pageStack->removeWidget(page);
    page->deleteLater();
}

void MainWindow::navigateTo(const QString &urlStr) {
    auto *page = currentPage();
    if (!page) return;

    QString trimmed = urlStr.trimmed();
    QUrl url;

    if (trimmed.startsWith("nexus://")) {
        url = QUrl(trimmed);
    } else if (trimmed.contains(' ') || !trimmed.contains('.')) {
        // Search query
        QString engine = m_settings->value("search/engine",
            "https://duckduckgo.com/?q=").toString();
        url = QUrl(engine + QUrl::toPercentEncoding(trimmed));
    } else {
        if (!trimmed.startsWith("http://") && !trimmed.startsWith("https://"))
            trimmed = "https://" + trimmed;
        url = QUrl(trimmed);
    }

    page->load(url);
    m_historyManager->addEntry(url, page->title());
}

void MainWindow::onBack()    { if (auto *p = currentPage()) p->back(); }
void MainWindow::onForward() { if (auto *p = currentPage()) p->forward(); }
void MainWindow::onReload()  { if (auto *p = currentPage()) p->reload(); }
void MainWindow::onHome()    { navigateTo("nexus://home"); }
void MainWindow::onTranslate() { if (auto *p = currentPage()) p->toggleTranslate(); }

void MainWindow::onTabChanged(int index) {
    m_pageStack->setCurrentIndex(index);
    auto *page = currentPage();
    if (!page) return;

    m_navBar->setUrl(page->url().toString());
    m_navBar->setCanGoBack(page->canGoBack());
    m_navBar->setCanGoForward(page->canGoForward());
    updateWindowTitle(page->title());
}

void MainWindow::onUrlChanged(const QUrl &url) {
    auto *page = qobject_cast<BrowserPage*>(sender());
    if (page == currentPage()) {
        m_navBar->setUrl(url.toString() == "nexus://home" ? "" : url.toString());
        m_navBar->setCanGoBack(page->canGoBack());
        m_navBar->setCanGoForward(page->canGoForward());
    }
}

void MainWindow::onTitleChanged(const QString &title) {
    auto *page = qobject_cast<BrowserPage*>(sender());
    int idx = m_pageStack->indexOf(page);
    if (idx >= 0) {
        QString display = title.isEmpty() ? "New Tab" : title;
        m_tabBar->setTabText(idx, display);
        if (page == currentPage()) updateWindowTitle(display);
    }
}

void MainWindow::onLoadProgress(int progress) {
    auto *page = qobject_cast<BrowserPage*>(sender());
    if (page == currentPage()) {
        m_navBar->setLoadProgress(progress);
    }
}

void MainWindow::onLoadFinished(bool ok) {
    auto *page = qobject_cast<BrowserPage*>(sender());
    if (page == currentPage()) {
        m_navBar->setLoadProgress(0);
        m_navBar->setCanGoBack(page->canGoBack());
        m_navBar->setCanGoForward(page->canGoForward());
        Q_UNUSED(ok)
    }
}

void MainWindow::updateWindowTitle(const QString &title) {
    setWindowTitle(title.isEmpty() ? "Stellar Nexus" : title + " — Stellar Nexus");
}

BrowserPage* MainWindow::currentPage() const {
    return qobject_cast<BrowserPage*>(m_pageStack->currentWidget());
}

BrowserPage* MainWindow::pageAt(int index) const {
    return qobject_cast<BrowserPage*>(m_pageStack->widget(index));
}

void MainWindow::addBookmark() {
    auto *page = currentPage();
    if (!page) return;
    m_bookmarkManager->addBookmark(page->url(), page->title());
    m_navBar->showBookmarkAdded();
}

void MainWindow::showBookmarks() {
    m_bookmarkManager->showDialog(this);
}

void MainWindow::showDownloads() {
    m_downloadManager->showDialog(this);
}

void MainWindow::showSettings() {
    SettingsDialog dlg(m_settings, this);
    // Connect language change signal
    connect(&dlg, &SettingsDialog::languageChanged, this, [this](const QString &lang) {
        m_settings->setValue("app/language", lang);
    });
    dlg.exec();
    applyTheme();
}

void MainWindow::showHistory() {
    m_historyManager->showDialog(this);
}

void MainWindow::toggleFullScreen() {
    if (isFullScreen()) showNormal();
    else showFullScreen();
}

void MainWindow::openUrl(const QUrl &url) {
    if (m_tabBar->count() == 0) {
        newTab(url);
    } else {
        currentPage()->load(url);
        m_navBar->setUrl(url.toString());
    }
}

void MainWindow::applyTheme() {
    QString accent = m_settings->value("theme/accent", "#4FC3F7").toString();
    bool dark = m_settings->value("theme/dark", true).toBool();

    QString bg     = dark ? "#0D1117" : "#F0F4F8";
    QString bg2    = dark ? "#161B22" : "#FFFFFF";
    QString bg3    = dark ? "#1C2330" : "#E8EDF3";
    QString text   = dark ? "#E6EDF3" : "#1A2332";
    QString border = dark ? "#30363D" : "#D0D7DE";
    QString muted  = dark ? "#8B949E" : "#656D76";

    QString qss = QString(R"(
        QMainWindow, QWidget#centralWidget {
            background: %1;
        }
        QWidget {
            font-family: 'JetBrains Mono', 'Fira Code', 'Consolas', monospace;
            font-size: 13px;
            color: %4;
        }
        QDialog {
            background: %2;
            color: %4;
        }
        QLabel {
            color: %4;
        }
        QLineEdit {
            background: %3;
            border: 1px solid %5;
            border-radius: 6px;
            padding: 4px 10px;
            color: %4;
            selection-background-color: %6;
        }
        QLineEdit:focus {
            border: 1px solid %6;
        }
        QPushButton {
            background: %3;
            border: 1px solid %5;
            border-radius: 6px;
            padding: 6px 14px;
            color: %4;
        }
        QPushButton:hover {
            background: %6;
            color: #000;
            border-color: %6;
        }
        QPushButton:pressed {
            opacity: 0.8;
        }
        QScrollBar:vertical {
            background: %1;
            width: 8px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: %5;
            border-radius: 4px;
            min-height: 20px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
        QListWidget {
            background: %2;
            border: 1px solid %5;
            border-radius: 8px;
            color: %4;
            outline: none;
        }
        QListWidget::item:selected {
            background: %6;
            color: #000;
            border-radius: 4px;
        }
        QListWidget::item:hover {
            background: %3;
            border-radius: 4px;
        }
        QTabWidget::pane {
            border: none;
        }
        QTreeWidget {
            background: %2;
            border: 1px solid %5;
            color: %4;
        }
        QTreeWidget::item:selected {
            background: %6;
            color: #000;
        }
        QCheckBox {
            color: %4;
        }
        QCheckBox::indicator {
            width: 16px; height: 16px;
            border: 1px solid %5;
            border-radius: 3px;
            background: %3;
        }
        QCheckBox::indicator:checked {
            background: %6;
            border-color: %6;
        }
        QComboBox {
            background: %3;
            border: 1px solid %5;
            border-radius: 6px;
            padding: 4px 10px;
            color: %4;
        }
        QComboBox::drop-down { border: none; }
        QComboBox QAbstractItemView {
            background: %2;
            selection-background-color: %6;
            color: %4;
        }
        QSplitter::handle {
            background: %5;
        }
        QGroupBox {
            border: 1px solid %5;
            border-radius: 8px;
            margin-top: 12px;
            padding-top: 8px;
            color: %7;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            color: %7;
        }
    )").arg(bg, bg2, bg3, text, border, accent, muted);

    qApp->setStyleSheet(qss);
}

void MainWindow::loadSession() {
    // Future: restore tabs from last session
}

void MainWindow::saveSession() {
    m_settings->setValue("window/size", size());
    m_settings->setValue("window/maximized", isMaximized());
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveSession();
    event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    QMainWindow::keyPressEvent(event);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    return QMainWindow::eventFilter(obj, event);
}
