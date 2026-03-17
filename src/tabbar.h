#pragma once
#include <QWidget>
#include <QTabBar>
#include <QHBoxLayout>
#include <QList>
#include <QIcon>
#include <QPoint>

// Custom tab bar with Nexus styling + integrated window controls
class NexusTabBar : public QWidget {
    Q_OBJECT

public:
    explicit NexusTabBar(QWidget *parent = nullptr);

    int  addNexusTab(const QString &title);
    void removeTab(int index);
    int  currentIndex() const;
    void setCurrentIndex(int index);
    int  count() const;
    void setTabText(int index, const QString &text);
    void setTabIcon(int index, const QIcon &icon);
    QString tabText(int index) const;

    void setFramelessMode(bool frameless) { m_frameless = frameless; }

signals:
    void currentChanged(int index);
    void tabCloseRequested(int index);
    void newTabRequested();
    void minimizeRequested();
    void maximizeRequested();
    void closeRequested();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    enum WinBtn { WBNone = -1, WBMinimize = 0, WBMaximize = 1, WBClose = 2 };

    struct Tab {
        QString title;
        QIcon   icon;
        bool    active = false;
    };

    void   recalcLayout();
    QRect  tabRect(int index) const;
    QRect  closeButtonRect(int index) const;
    QRect  newTabButtonRect() const;
    QRect  winButtonRect(WinBtn btn) const;
    int    winButtonsWidth() const;
    WinBtn winButtonAt(QPoint pos) const;
    int    tabAt(QPoint pos) const;

    QList<Tab> m_tabs;
    int        m_current    = -1;
    int        m_hovered    = -1;
    int        m_closeHover = -1;
    WinBtn     m_winHover   = WBNone;
    bool       m_frameless  = false;
    bool       m_dragging   = false;
    QPoint     m_dragStart;

    static constexpr int TAB_H    = 38;
    static constexpr int TAB_MAXW = 220;
    static constexpr int TAB_MINW = 80;
    static constexpr int CLOSE_SZ = 16;
    static constexpr int NEW_BTN  = 32;
    static constexpr int WIN_BTN  = 42;
    int m_tabWidth = 200;
};
