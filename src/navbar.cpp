#include "navbar.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QSettings>
#include <QHBoxLayout>
#include <QTimer>
#include <QApplication>

// ──────────────────────────────────────────────────────────────────
// NavButton
// ──────────────────────────────────────────────────────────────────
NavButton::NavButton(const QIcon &icon, const QString &tooltip, QWidget *parent)
    : QWidget(parent), m_icon(icon) {
    setFixedSize(36, 36);
    setToolTip(tooltip);
    setCursor(Qt::PointingHandCursor);
}

void NavButton::setEnabled(bool en) {
    m_enabled = en;
    m_opacity = en ? 0.6 : 0.25;
    setCursor(en ? Qt::PointingHandCursor : Qt::ArrowCursor);
    update();
}

void NavButton::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);

    QSettings s("StellarNexusBrowser", "Stellar");
    bool dark   = s.value("theme/dark", true).toBool();
    QString acc = s.value("theme/accent", "#4FC3F7").toString();

    QColor fg   = dark ? QColor("#E6EDF3") : QColor("#1A2332");
    QColor accC = QColor(acc);

    // Hover/press background
    if (m_pressed && m_enabled) {
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(accC.red(), accC.green(), accC.blue(), 60));
        p.drawRoundedRect(rect().adjusted(2,2,-2,-2), 8, 8);
    } else if (m_hovered && m_enabled) {
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(fg.red(), fg.green(), fg.blue(), 20));
        p.drawRoundedRect(rect().adjusted(2,2,-2,-2), 8, 8);
    }

    // Icon
    if (m_icon.isNull()) {
        p.setPen(Qt::red);
        p.drawText(rect(), Qt::AlignCenter, "X");
    } else {
        QPixmap pix = m_icon.pixmap(QSize(20, 20));
        p.setOpacity(m_opacity);
        p.drawPixmap(rect().center() - QPoint(10, 10), pix);
    }
}

void NavButton::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton && m_enabled) {
        m_pressed = true; update();
    }
}

void NavButton::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton && m_enabled && m_pressed) {
        m_pressed = false; update();
        emit clicked();
    }
    m_pressed = false;
}

void NavButton::enterEvent(QEnterEvent *) { m_hovered = true;  update(); }
void NavButton::leaveEvent(QEvent *)      { m_hovered = false; m_pressed = false; update(); }

// ──────────────────────────────────────────────────────────────────
// UrlBar
// ──────────────────────────────────────────────────────────────────
UrlBar::UrlBar(QWidget *parent) : QLineEdit(parent) {
    setPlaceholderText("Search or enter address…");
    setFrame(false);
    setClearButtonEnabled(true);
}

void UrlBar::setSecure(bool secure) { m_secure = secure; update(); }

void UrlBar::focusInEvent(QFocusEvent *e) {
    m_focused = true;
    selectAll();
    QLineEdit::focusInEvent(e);
}

void UrlBar::focusOutEvent(QFocusEvent *e) {
    m_focused = false;
    QLineEdit::focusOutEvent(e);
}

void UrlBar::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape) {
        clearFocus();
        return;
    }
    QLineEdit::keyPressEvent(e);
}

void UrlBar::paintEvent(QPaintEvent *e) {
    QLineEdit::paintEvent(e);
    // Draw lock icon if secure
    if (m_secure && !m_focused) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        QSettings s("StellarNexusBrowser", "Stellar");
        QString acc = s.value("theme/accent", "#4FC3F7").toString();
        p.setPen(QColor(acc));
        QFont f = p.font();
        f.setPixelSize(12);
        p.setFont(f);
        p.drawText(QRect(6, 0, 20, height()), Qt::AlignVCenter | Qt::AlignLeft, "🔒");
    }
}

// ──────────────────────────────────────────────────────────────────
// NavBar
// ──────────────────────────────────────────────────────────────────
NavBar::NavBar(QWidget *parent) : QWidget(parent) {
    setFixedHeight(52);
    setupLayout();

    m_pulseTimer = new QTimer(this);
    m_pulseTimer->setInterval(600);
    connect(m_pulseTimer, &QTimer::timeout, this, [this]{
        m_bookmarkPulse = false;
        m_pulseTimer->stop();
        m_bookmark->update();
    });
}

void NavBar::setupLayout() {
    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 8, 10, 8);
    layout->setSpacing(4);

    m_back     = new NavButton(QIcon(":/back.png"), "Back",     this);
    m_forward  = new NavButton(QIcon(":/forward.png"), "Forward",  this);
    m_reload   = new NavButton(QIcon(":/reload.png"), "Reload",   this);
    m_home     = new NavButton(QIcon(":/home.png"), "Home",     this);
    m_urlBar   = new UrlBar(this);
    m_bookmark = new NavButton(QIcon(":/star.png"), "Bookmark", this);
    m_translate= new NavButton(QIcon(":/traductor.png"), "Translate", this);
    m_downloads= new NavButton(QIcon(":/download.png"), "Downloads",this);
    m_settings = new NavButton(QIcon(":/menu.png"), "Settings", this);

    m_back->setEnabled(false);
    m_forward->setEnabled(false);

    layout->addWidget(m_back);
    layout->addWidget(m_forward);
    layout->addWidget(m_reload);
    layout->addWidget(m_home);
    layout->addSpacing(6);
    layout->addWidget(m_urlBar, 1);
    layout->addSpacing(6);
    layout->addWidget(m_bookmark);
    layout->addWidget(m_translate);
    layout->addWidget(m_downloads);
    layout->addWidget(m_settings);

    connect(m_back,      &NavButton::clicked, this, &NavBar::backClicked);
    connect(m_forward,   &NavButton::clicked, this, &NavBar::forwardClicked);
    connect(m_reload,    &NavButton::clicked, this, &NavBar::reloadClicked);
    connect(m_home,      &NavButton::clicked, this, &NavBar::homeClicked);
    connect(m_bookmark,  &NavButton::clicked, this, &NavBar::bookmarkClicked);
    connect(m_translate, &NavButton::clicked, this, &NavBar::translateClicked);
    connect(m_downloads, &NavButton::clicked, this, &NavBar::showDownloads);
    connect(m_settings,  &NavButton::clicked, this, &NavBar::showSettings);

    connect(m_urlBar, &QLineEdit::returnPressed, this, &NavBar::onNavigate);
}

void NavBar::onNavigate() {
    emit navigate(m_urlBar->text().trimmed());
    m_urlBar->clearFocus();
}

void NavBar::setUrl(const QString &url) {
    if (!m_urlBar->hasFocus()) {
        m_urlBar->setText(url);
        m_urlBar->setSecure(url.startsWith("https://"));
    }
}

void NavBar::setCanGoBack(bool can)    { m_back->setEnabled(can); }
void NavBar::setCanGoForward(bool can) { m_forward->setEnabled(can); }

void NavBar::setLoadProgress(int progress) {
    m_progress = progress;
    // Swap reload ↔ stop
    if (progress > 0 && progress < 100) {
        m_reload->setToolTip("Stop");
    } else {
        m_reload->setToolTip("Reload");
    }
    update();
}

void NavBar::focusUrlBar() {
    m_urlBar->setFocus();
    m_urlBar->selectAll();
}

void NavBar::showBookmarkAdded() {
    m_bookmark->setToolTip("Bookmarked! ★");
    m_bookmarkPulse = true;
    m_pulseTimer->start();
    update();
}

void NavBar::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QSettings s("StellarNexusBrowser", "Stellar");
    bool dark   = s.value("theme/dark", true).toBool();
    QString acc = s.value("theme/accent", "#4FC3F7").toString();

    QColor bg  = dark ? QColor("#161B22") : QColor("#FFFFFF");
    QColor border = dark ? QColor("#30363D") : QColor("#D0D7DE");
    QColor accC = QColor(acc);

    p.fillRect(rect(), bg);

    // Bottom border
    p.setPen(border);
    p.drawLine(0, height()-1, width(), height()-1);

    // Load progress bar (thin line at bottom)
    if (m_progress > 0 && m_progress < 100) {
        QLinearGradient grad(0, 0, width(), 0);
        grad.setColorAt(0, accC);
        grad.setColorAt(1, accC.lighter(140));
        p.setPen(Qt::NoPen);
        p.setBrush(grad);
        double w = width() * m_progress / 100.0;
        p.drawRoundedRect(QRectF(0, height()-2, w, 2), 1, 1);
    }
}
