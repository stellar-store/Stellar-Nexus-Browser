#pragma once
#include <QObject>
#include <QDialog>
#include <QList>
#include <QUrl>
#include <QString>
#include <QDateTime>
#include <QSettings>
#include <QWidget>

struct HistoryEntry {
    QUrl      url;
    QString   title;
    QDateTime visitedAt;
};

class HistoryManager : public QObject {
    Q_OBJECT
public:
    explicit HistoryManager(QObject *parent = nullptr);
    void addEntry(const QUrl &url, const QString &title);
    void clear();
    QList<HistoryEntry> entries() const { return m_entries; }
    void showDialog(QWidget *parent);

private:
    void load();
    void save();
    QList<HistoryEntry> m_entries;
    QSettings *m_settings;
};
