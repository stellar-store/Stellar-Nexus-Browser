#pragma once
#include <QObject>
#include <QDialog>
#include <QList>
#include <QWebEngineDownloadRequest>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QDateTime>
#include <QFileInfo>
#include <QPoint>
#include <QMouseEvent>
#include <QTimer>
#include <QMap>

struct DownloadItem {
    QWebEngineDownloadRequest *request = nullptr;
    QString filePath;
    qint64  totalBytes    = 0;
    qint64  receivedBytes = 0;
    bool    finished      = false;
    bool    failed        = false;
    QDateTime startTime;
};

class DownloadDialog : public QDialog {
    Q_OBJECT
public:
    explicit DownloadDialog(class DownloadManager *manager, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void buildUI();
    void updateDownloads();
    void rebuildDownloadsList();
    
    QPoint m_dragPosition;
    DownloadManager *m_manager = nullptr;
    QMap<int, QProgressBar*> m_progressBars;
    QMap<int, QLabel*> m_sizeLabels;
    QWidget *m_scrollContent = nullptr;
    QVBoxLayout *m_scrollLayout = nullptr;
};

class DownloadManager : public QObject {
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = nullptr);

    void addDownload(QWebEngineDownloadRequest *download);
    void showDialog(QWidget *parent);
    int  activeCount() const;
    void clearCompleted();
    
    const QList<DownloadItem> &getDownloads() const { return m_downloads; }

signals:
    void downloadStarted(const QString &filename);
    void downloadFinished(const QString &filename);

private:
    QList<DownloadItem> m_downloads;
};
