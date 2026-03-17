#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineDownloadRequest>
#include <QWebEngineHistory>
#include <QUrl>
#include <QIcon>

class BrowserPage : public QWidget {
    Q_OBJECT

public:
    explicit BrowserPage(QWidget *parent = nullptr);

    void load(const QUrl &url);
    void back();
    void forward();
    void reload();
    void toggleTranslate();
    bool canGoBack() const;
    bool canGoForward() const;
    QUrl url() const;
    QString title() const;
    QWebEngineView* view() const { return m_view; }

signals:
    void urlChanged(const QUrl &url);
    void titleChanged(const QString &title);
    void loadProgress(int progress);
    void loadFinished(bool ok);
    void iconChanged(const QIcon &icon);
    void newTabRequested(const QUrl &url);
    void downloadRequested(QWebEngineDownloadRequest *download);

private:
    void setupHomePage();
    void showHomePage();

    QWebEngineView    *m_view    = nullptr;
    QVBoxLayout       *m_layout  = nullptr;
    bool               m_isHome  = false;
};

// Custom page to intercept new tab requests
class NexusWebPage : public QWebEnginePage {
    Q_OBJECT

public:
    explicit NexusWebPage(QWebEngineProfile *profile, QObject *parent = nullptr);

signals:
    void newWindowRequested(const QUrl &url);

protected:
    QWebEnginePage* createWindow(WebWindowType type) override;

private:
    QUrl m_pendingUrl;
};
