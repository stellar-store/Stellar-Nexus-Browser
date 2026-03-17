#include "historymanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDesktopServices>

HistoryManager::HistoryManager(QObject *parent) : QObject(parent) {
    m_settings = new QSettings("StellarNexusBrowser", "Stellar", this);
    load();
}

void HistoryManager::addEntry(const QUrl &url, const QString &title) {
    if (url.scheme() == "nexus") return;
    // Avoid duplicates in sequence
    if (!m_entries.isEmpty() && m_entries.first().url == url) return;

    HistoryEntry e;
    e.url       = url;
    e.title     = title.isEmpty() ? url.toString() : title;
    e.visitedAt = QDateTime::currentDateTime();
    m_entries.prepend(e);

    // Keep last 1000
    while (m_entries.size() > 1000) m_entries.removeLast();
    save();
}

void HistoryManager::clear() {
    m_entries.clear();
    save();
}

void HistoryManager::load() {
    QStringList urls   = m_settings->value("history/urls").toStringList();
    QStringList titles = m_settings->value("history/titles").toStringList();
    QStringList dates  = m_settings->value("history/dates").toStringList();
    for (int i = 0; i < urls.size(); ++i) {
        HistoryEntry e;
        e.url       = QUrl(urls[i]);
        e.title     = i < titles.size() ? titles[i] : urls[i];
        e.visitedAt = i < dates.size()
                      ? QDateTime::fromString(dates[i], Qt::ISODate)
                      : QDateTime::currentDateTime();
        m_entries.append(e);
    }
}

void HistoryManager::save() {
    QStringList urls, titles, dates;
    for (const auto &e : m_entries) {
        urls   << e.url.toString();
        titles << e.title;
        dates  << e.visitedAt.toString(Qt::ISODate);
    }
    m_settings->setValue("history/urls",   urls);
    m_settings->setValue("history/titles", titles);
    m_settings->setValue("history/dates",  dates);
}

void HistoryManager::showDialog(QWidget *parent) {
    auto *dlg = new QDialog(parent, Qt::Dialog);
    dlg->setWindowTitle("History");
    dlg->resize(580, 520);
    dlg->setModal(false);

    auto *layout = new QVBoxLayout(dlg);
    layout->setContentsMargins(16,16,16,16);
    layout->setSpacing(10);

    auto *header = new QLabel("◷  History", dlg);
    header->setStyleSheet("font-size:16px; font-weight:bold; letter-spacing:2px;");
    layout->addWidget(header);

    auto *searchBar = new QLineEdit(dlg);
    searchBar->setPlaceholderText("Search history…");
    layout->addWidget(searchBar);

    auto *list = new QListWidget(dlg);
    list->setSpacing(1);
    layout->addWidget(list, 1);

    auto refresh = [this, list, searchBar]() {
        list->clear();
        QString f = searchBar->text().toLower();
        QString prevDate;
        for (const auto &e : m_entries) {
            if (!f.isEmpty() &&
                !e.title.toLower().contains(f) &&
                !e.url.toString().toLower().contains(f)) continue;

            QString dateLabel = e.visitedAt.toString("yyyy-MM-dd");
            if (dateLabel != prevDate) {
                auto *sep = new QListWidgetItem("  " + dateLabel);
                sep->setFlags(Qt::NoItemFlags);
                sep->setForeground(QColor("#58636E"));
                QFont f2 = sep->font(); f2.setBold(true); sep->setFont(f2);
                list->addItem(sep);
                prevDate = dateLabel;
            }

            QString time = e.visitedAt.toString("HH:mm");
            auto *item = new QListWidgetItem(
                QString("  %1  •  %2\n  %3").arg(time, e.title, e.url.toString()));
            item->setData(Qt::UserRole, e.url.toString());
            list->addItem(item);
        }
    };
    refresh();
    connect(searchBar, &QLineEdit::textChanged, dlg, [refresh]{ refresh(); });

    auto *btnRow = new QHBoxLayout;
    auto *openBtn  = new QPushButton("Open", dlg);
    auto *clearBtn = new QPushButton("Clear All", dlg);
    auto *closeBtn = new QPushButton("Close", dlg);

    connect(openBtn, &QPushButton::clicked, dlg, [list]{
        auto *item = list->currentItem();
        if (!item || item->data(Qt::UserRole).isNull()) return;
        QDesktopServices::openUrl(QUrl(item->data(Qt::UserRole).toString()));
    });

    connect(list, &QListWidget::itemDoubleClicked, dlg, [](QListWidgetItem *item){
        if (!item->data(Qt::UserRole).isNull())
            QDesktopServices::openUrl(QUrl(item->data(Qt::UserRole).toString()));
    });

    connect(clearBtn, &QPushButton::clicked, dlg, [this, &refresh, dlg]{
        clear();
        refresh();
    });

    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);

    btnRow->addWidget(openBtn);
    btnRow->addWidget(clearBtn);
    btnRow->addStretch();
    btnRow->addWidget(closeBtn);
    layout->addLayout(btnRow);

    dlg->show();
}
