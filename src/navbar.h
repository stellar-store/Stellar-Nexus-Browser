#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QTimer>

// Icon button with hover effect
class NavButton : public QWidget {
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit NavButton(const QIcon &icon, const QString &tooltip, QWidget *parent = nullptr);

    qreal opacity() const { return m_opacity; }
    void setOpacity(qreal v) { m_opacity = v; update(); }
    void setEnabled(bool en);
    bool isEnabled() const { return m_enabled; }

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void enterEvent(QEnterEvent *) override;
    void leaveEvent(QEvent *) override;

private:
    QIcon   m_icon;
    qreal   m_opacity = 0.6;
    bool    m_enabled = true;
    bool    m_pressed = false;
    bool    m_hovered = false;
};

// Animated URL bar
class UrlBar : public QLineEdit {
    Q_OBJECT

public:
    explicit UrlBar(QWidget *parent = nullptr);
    void setSecure(bool secure);

protected:
    void focusInEvent(QFocusEvent *) override;
    void focusOutEvent(QFocusEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void paintEvent(QPaintEvent *) override;

private:
    bool m_secure = false;
    bool m_focused = false;
};

// Main navigation bar
class NavBar : public QWidget {
    Q_OBJECT

public:
    explicit NavBar(QWidget *parent = nullptr);

    void setUrl(const QString &url);
    void setCanGoBack(bool can);
    void setCanGoForward(bool can);
    void setLoadProgress(int progress);
    void focusUrlBar();
    void showBookmarkAdded();

signals:
    void navigate(const QString &url);
    void backClicked();
    void forwardClicked();
    void reloadClicked();
    void homeClicked();
    void bookmarkClicked();
    void showBookmarks();
    void showDownloads();
    void showSettings();
    void translateClicked();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void setupLayout();
    void onNavigate();

    NavButton  *m_back        = nullptr;
    NavButton  *m_forward     = nullptr;
    NavButton  *m_reload      = nullptr;
    NavButton  *m_home        = nullptr;
    UrlBar     *m_urlBar      = nullptr;
    NavButton  *m_bookmark    = nullptr;
    NavButton  *m_translate   = nullptr;
    NavButton  *m_downloads   = nullptr;
    NavButton  *m_settings    = nullptr;

    int         m_progress    = 0;
    bool        m_bookmarkPulse = false;
    QTimer     *m_pulseTimer  = nullptr;
};
