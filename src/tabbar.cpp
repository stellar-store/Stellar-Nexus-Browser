#include "tabbar.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QSettings>
#include <QApplication>

NexusTabBar::NexusTabBar(QWidget *parent) : QWidget(parent) {
    setFixedHeight(TAB_H + 2);
    setMouseTracking(true);
}

int NexusTabBar::addNexusTab(const QString &title) {
    Tab t; t.title = title;
    m_tabs.append(t);
    recalcLayout();
    update();
    return m_tabs.size() - 1;
}

void NexusTabBar::removeTab(int index) {
    if (index < 0 || index >= m_tabs.size()) return;
    m_tabs.removeAt(index);
    if (m_current >= m_tabs.size()) m_current = m_tabs.size() - 1;
    recalcLayout();
    update();
    emit currentChanged(m_current);
}

int  NexusTabBar::currentIndex() const { return m_current; }
int  NexusTabBar::count()        const { return m_tabs.size(); }

void NexusTabBar::setCurrentIndex(int index) {
    if (index < 0 || index >= m_tabs.size() || index == m_current) return;
    m_current = index;
    update();
    emit currentChanged(m_current);
}

void NexusTabBar::setTabText(int index, const QString &text) {
    if (index < 0 || index >= m_tabs.size()) return;
    m_tabs[index].title = text; update();
}
void NexusTabBar::setTabIcon(int index, const QIcon &icon) {
    if (index < 0 || index >= m_tabs.size()) return;
    m_tabs[index].icon = icon; update();
}
QString NexusTabBar::tabText(int index) const {
    if (index < 0 || index >= m_tabs.size()) return {};
    return m_tabs[index].title;
}

// Layout helpers
int NexusTabBar::winButtonsWidth() const { return WIN_BTN * 3 + 8; }

void NexusTabBar::recalcLayout() {
    if (m_tabs.isEmpty()) { m_tabWidth = TAB_MAXW; return; }
    int avail = width() - NEW_BTN - 8 - winButtonsWidth();
    m_tabWidth = qBound(TAB_MINW, avail / m_tabs.size(), TAB_MAXW);
}

QRect NexusTabBar::tabRect(int index) const {
    return QRect(index * m_tabWidth, 0, m_tabWidth, TAB_H);
}

QRect NexusTabBar::closeButtonRect(int index) const {
    QRect r = tabRect(index);
    return QRect(r.right()-CLOSE_SZ-6, r.top()+(TAB_H-CLOSE_SZ)/2, CLOSE_SZ, CLOSE_SZ);
}

QRect NexusTabBar::newTabButtonRect() const {
    int x = m_tabs.size() * m_tabWidth + 6;
    return QRect(x, (TAB_H-26)/2, 26, 26);
}

QRect NexusTabBar::winButtonRect(WinBtn btn) const {
    int startX = width() - winButtonsWidth() + 4;
    return QRect(startX + (int)btn * WIN_BTN, 0, WIN_BTN, TAB_H);
}

NexusTabBar::WinBtn NexusTabBar::winButtonAt(QPoint pos) const {
    for (int b = 0; b < 3; ++b)
        if (winButtonRect((WinBtn)b).contains(pos)) return (WinBtn)b;
    return WBNone;
}

int NexusTabBar::tabAt(QPoint pos) const {
    if (pos.x() >= width() - winButtonsWidth()) return -1;
    for (int i = 0; i < m_tabs.size(); ++i)
        if (tabRect(i).contains(pos)) return i;
    return -1;
}

void NexusTabBar::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QSettings s("StellarNexusBrowser", "Stellar");
    bool dark   = s.value("theme/dark", true).toBool();
    QString acc = s.value("theme/accent", "#4FC3F7").toString();

    QColor bgBase  = dark ? QColor("#0D1117") : QColor("#E8EDF3");
    QColor bgTab   = dark ? QColor("#161B22") : QColor("#FFFFFF");
    QColor bgHover = dark ? QColor("#1C2330") : QColor("#F0F4F8");
    QColor fgText  = dark ? QColor("#C9D1D9") : QColor("#24292F");
    QColor fgMuted = dark ? QColor("#58636E") : QColor("#A0A8B0");
    QColor accentC = QColor(acc);
    QColor border  = dark ? QColor("#30363D") : QColor("#D0D7DE");

    p.fillRect(rect(), bgBase);
    p.setPen(border);
    p.drawLine(0, TAB_H, width(), TAB_H);

    QFont font = p.font();
    font.setFamily("JetBrains Mono, Fira Code, Consolas, monospace");
    font.setPixelSize(12);
    p.setFont(font);

    // Draw tabs
    for (int i = 0; i < m_tabs.size(); ++i) {
        QRect r     = tabRect(i);
        bool active = (i == m_current);
        bool hov    = (i == m_hovered);

        QPainterPath path;
        int rad = 8;
        path.moveTo(r.left()+rad, r.top());
        path.lineTo(r.right()-rad, r.top());
        path.quadTo(r.right(), r.top(), r.right(), r.top()+rad);
        path.lineTo(r.right(), r.bottom());
        path.lineTo(r.left(),  r.bottom());
        path.lineTo(r.left(),  r.top()+rad);
        path.quadTo(r.left(), r.top(), r.left()+rad, r.top());
        path.closeSubpath();

        if (active) {
            p.fillPath(path, bgTab);
            p.setPen(Qt::NoPen);
            p.setBrush(accentC);
            p.drawRoundedRect(QRect(r.left()+8, r.top(), r.width()-16, 2), 1, 1);
            p.fillRect(QRect(r.left(), r.bottom(), r.width(), 2), bgTab);
        } else if (hov) {
            p.fillPath(path, bgHover);
        }

        if (!active && i > 0 && (i-1) != m_current) {
            p.setPen(border);
            p.drawLine(r.left(), r.top()+8, r.left(), r.bottom()-8);
        }

        int iconX = r.left()+10, iconY = r.top()+(TAB_H-16)/2;
        if (!m_tabs[i].icon.isNull()) {
            m_tabs[i].icon.paint(&p, QRect(iconX, iconY, 16, 16));
        } else {
            p.setPen(Qt::NoPen); p.setBrush(fgMuted);
            p.drawEllipse(iconX+4, iconY+4, 8, 8);
        }

        QRect textRect(r.left()+32, r.top(), r.width()-32-CLOSE_SZ-10, TAB_H);
        p.setPen(active ? fgText : fgMuted);
        p.drawText(textRect, Qt::AlignVCenter|Qt::AlignLeft,
                   p.fontMetrics().elidedText(m_tabs[i].title, Qt::ElideRight, textRect.width()));

        if (active || hov) {
            QRect cb = closeButtonRect(i);
            bool chov = (m_closeHover == i);
            if (chov) {
                p.setPen(Qt::NoPen);
                p.setBrush(QColor(255,80,80,180));
                p.drawEllipse(cb);
            }
            p.setPen(QPen(chov ? QColor(Qt::white) : fgMuted, 1.5f));
            p.drawLine(cb.left()+4, cb.top()+4, cb.right()-4, cb.bottom()-4);
            p.drawLine(cb.right()-4, cb.top()+4, cb.left()+4, cb.bottom()-4);
        }
    }

    // New-tab button
    QRect nb   = newTabButtonRect();
    bool nbHov = nb.contains(mapFromGlobal(QCursor::pos()));
    p.setPen(Qt::NoPen);
    p.setBrush(nbHov ? accentC : bgTab);
    p.drawRoundedRect(nb, 6, 6);
    p.setPen(QPen(nbHov ? QColor("#000") : fgMuted, 1.8f));
    p.drawLine(nb.center().x()-6, nb.center().y(), nb.center().x()+6, nb.center().y());
    p.drawLine(nb.center().x(), nb.center().y()-6, nb.center().x(), nb.center().y()+6);

    // ── Window control buttons ──────────────────────────────────────
    // Separator
    int sepX = width() - winButtonsWidth();
    p.setPen(QPen(border, 1));
    p.drawLine(sepX, 15, sepX, TAB_H-15);

    // Define colors for macOS-style buttons
    QColor minimizeColor = QColor("#0379da"); // Light blue (azul blanco)
    QColor maximizeColor = QColor("#0379da"); // Sky blue (azul claro)
    QColor closeColor    = QColor("#4103d3"); // Dark blue (azul oscuro brillante)

    for (int b = 0; b < 3; ++b) {
        QRect  r   = winButtonRect((WinBtn)b);
        bool   hov = (m_winHover == (WinBtn)b);

        // Draw circular button
        QRect circleRect = r.adjusted(12, 12, -12, -12); // Make it smaller and centered
        QColor btnColor;
        if (b == 0) btnColor = minimizeColor;
        else if (b == 1) btnColor = maximizeColor;
        else btnColor = closeColor;

        if (hov) {
            // Slightly brighter on hover
            btnColor = btnColor.lighter(120);
        }

        p.setPen(Qt::NoPen);
        p.setBrush(btnColor);
        p.drawEllipse(circleRect);
    }

    p.setFont(font);
}

void NexusTabBar::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (winButtonAt(event->pos()) != WBNone) return; // handled on release
        if (newTabButtonRect().contains(event->pos())) { emit newTabRequested(); return; }
        for (int i = 0; i < m_tabs.size(); ++i)
            if (closeButtonRect(i).contains(event->pos())) { emit tabCloseRequested(i); return; }
        int idx = tabAt(event->pos());
        if (idx >= 0) { setCurrentIndex(idx); return; }
        // Drag window
        if (m_frameless) {
            m_dragging = true;
            m_dragStart = event->globalPosition().toPoint() - window()->frameGeometry().topLeft();
        }
    } else if (event->button() == Qt::MiddleButton) {
        int idx = tabAt(event->pos());
        if (idx >= 0) emit tabCloseRequested(idx);
    }
}

void NexusTabBar::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        switch (winButtonAt(event->pos())) {
            case WBMinimize: emit minimizeRequested(); break;
            case WBMaximize: emit maximizeRequested(); break;
            case WBClose:    emit closeRequested();    break;
            default: break;
        }
    }
}

void NexusTabBar::mouseDoubleClickEvent(QMouseEvent *event) {
    if (m_frameless && event->button() == Qt::LeftButton &&
        winButtonAt(event->pos()) == WBNone &&
        tabAt(event->pos()) < 0 &&
        !newTabButtonRect().contains(event->pos())) {
        emit maximizeRequested();
    }
}

void NexusTabBar::mouseMoveEvent(QMouseEvent *event) {
    if (m_dragging && m_frameless) {
        window()->move(event->globalPosition().toPoint() - m_dragStart);
        return;
    }
    int    ph = m_hovered, pc = m_closeHover; WinBtn pw = m_winHover;
    m_hovered    = tabAt(event->pos());
    m_closeHover = -1;
    m_winHover   = winButtonAt(event->pos());
    for (int i = 0; i < m_tabs.size(); ++i)
        if (closeButtonRect(i).contains(event->pos())) { m_closeHover = i; break; }
    if (ph != m_hovered || pc != m_closeHover || pw != m_winHover) update();
}

void NexusTabBar::resizeEvent(QResizeEvent *) { recalcLayout(); }
void NexusTabBar::enterEvent(QEnterEvent *)   { update(); }
void NexusTabBar::leaveEvent(QEvent *)        { m_hovered=-1; m_closeHover=-1; m_winHover=WBNone; update(); }
