#pragma once
#include <QObject>
#include <QDialog>
#include <QList>
#include <QUrl>
#include <QString>
#include <QDateTime>
#include <QSettings>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

struct Bookmark {
    QUrl      url;
    QString   title;
    QDateTime addedAt;
    QString   folder;
};

class BookmarkManager : public QObject {
    Q_OBJECT
public:
    explicit BookmarkManager(QObject *parent = nullptr);

    void addBookmark(const QUrl &url, const QString &title, const QString &folder = "");
    void removeBookmark(int index);
    QList<Bookmark> bookmarks() const { return m_bookmarks; }
    bool isBookmarked(const QUrl &url) const;
    void showDialog(QWidget *parent);

signals:
    void bookmarksChanged();

private:
    void load();
    void save();
    QList<Bookmark> m_bookmarks;
    QSettings *m_settings;
};
