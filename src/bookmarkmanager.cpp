#include "bookmarkmanager.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QDesktopServices>

BookmarkManager::BookmarkManager(QObject *parent) : QObject(parent) {
    m_settings = new QSettings("StellarNexusBrowser", "Stellar", this);
    load();
}

void BookmarkManager::addBookmark(const QUrl &url, const QString &title, const QString &folder) {
    // Check if already bookmarked
    for (auto &b : m_bookmarks) {
        if (b.url == url) return;
    }
    Bookmark bm;
    bm.url     = url;
    bm.title   = title.isEmpty() ? url.toString() : title;
    bm.addedAt = QDateTime::currentDateTime();
    bm.folder  = folder;
    m_bookmarks.prepend(bm);
    save();
    emit bookmarksChanged();
}

void BookmarkManager::removeBookmark(int index) {
    if (index < 0 || index >= m_bookmarks.size()) return;
    m_bookmarks.removeAt(index);
    save();
    emit bookmarksChanged();
}

bool BookmarkManager::isBookmarked(const QUrl &url) const {
    for (const auto &b : m_bookmarks)
        if (b.url == url) return true;
    return false;
}

void BookmarkManager::load() {
    QStringList urls    = m_settings->value("bookmarks/urls").toStringList();
    QStringList titles  = m_settings->value("bookmarks/titles").toStringList();
    QStringList dates   = m_settings->value("bookmarks/dates").toStringList();

    m_bookmarks.clear();
    for (int i = 0; i < urls.size(); ++i) {
        Bookmark bm;
        bm.url     = QUrl(urls[i]);
        bm.title   = i < titles.size() ? titles[i] : urls[i];
        bm.addedAt = i < dates.size()
                     ? QDateTime::fromString(dates[i], Qt::ISODate)
                     : QDateTime::currentDateTime();
        m_bookmarks.append(bm);
    }
}

void BookmarkManager::save() {
    QStringList urls, titles, dates;
    for (const auto &bm : m_bookmarks) {
        urls   << bm.url.toString();
        titles << bm.title;
        dates  << bm.addedAt.toString(Qt::ISODate);
    }
    m_settings->setValue("bookmarks/urls",   urls);
    m_settings->setValue("bookmarks/titles", titles);
    m_settings->setValue("bookmarks/dates",  dates);
}

// ──────────────────────────────────────────────────────────────────
// Bookmark Dialog
// ──────────────────────────────────────────────────────────────────
void BookmarkManager::showDialog(QWidget *parent) {
    auto *dlg = new QDialog(parent, Qt::Dialog);
    dlg->setWindowTitle("Bookmarks");
    dlg->resize(560, 480);
    dlg->setModal(false);

    auto *layout = new QVBoxLayout(dlg);
    layout->setSpacing(10);
    layout->setContentsMargins(16, 16, 16, 16);

    // Header
    auto *header = new QLabel("★  Bookmarks", dlg);
    header->setStyleSheet("font-size:16px; font-weight:bold; letter-spacing:2px;");
    layout->addWidget(header);

    // Search filter
    auto *search = new QLineEdit(dlg);
    search->setPlaceholderText("Filter bookmarks…");
    layout->addWidget(search);

    // List
    auto *list = new QListWidget(dlg);
    list->setAlternatingRowColors(false);
    list->setSpacing(2);
    layout->addWidget(list);

    auto refreshList = [this, list, search]() {
        list->clear();
        QString filter = search->text().toLower();
        for (int i = 0; i < m_bookmarks.size(); ++i) {
            const auto &bm = m_bookmarks[i];
            if (!filter.isEmpty() &&
                !bm.title.toLower().contains(filter) &&
                !bm.url.toString().toLower().contains(filter))
                continue;
            auto *item = new QListWidgetItem(
                QString("  %1\n  %2").arg(bm.title, bm.url.toString()), list);
            item->setData(Qt::UserRole, i);
            item->setData(Qt::UserRole+1, bm.url.toString());
            list->addItem(item);
        }
    };
    refreshList();

    connect(search, &QLineEdit::textChanged, dlg, [refreshList]{ refreshList(); });

    // Bottom buttons
    auto *btnRow = new QHBoxLayout;
    auto *btnOpen   = new QPushButton("Open", dlg);
    auto *btnDelete = new QPushButton("Delete", dlg);
    auto *btnClose  = new QPushButton("Close", dlg);
    btnRow->addWidget(btnOpen);
    btnRow->addWidget(btnDelete);
    btnRow->addStretch();
    btnRow->addWidget(btnClose);
    layout->addLayout(btnRow);

    connect(btnOpen, &QPushButton::clicked, dlg, [list, parent]{
        auto *item = list->currentItem();
        if (!item) return;
        QDesktopServices::openUrl(QUrl(item->data(Qt::UserRole+1).toString()));
    });

    connect(btnDelete, &QPushButton::clicked, dlg, [this, list, &refreshList]{
        auto *item = list->currentItem();
        if (!item) return;
        int idx = item->data(Qt::UserRole).toInt();
        removeBookmark(idx);
        refreshList();
    });

    connect(list, &QListWidget::itemDoubleClicked, dlg, [list, parent](QListWidgetItem *item){
        QDesktopServices::openUrl(QUrl(item->data(Qt::UserRole+1).toString()));
    });

    connect(btnClose, &QPushButton::clicked, dlg, &QDialog::accept);

    dlg->show();
}
