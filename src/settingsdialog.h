#pragma once
#include <QDialog>
#include <QSettings>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QColorDialog>
#include <QMessageBox>
#include <QListWidget>
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QRegularExpression>
#include <QDir>
#include "translationmanager.h"

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(QSettings *settings, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void languageChanged(const QString &lang);

private:
    void buildGeneralTab(QTabWidget *tabs);
    void buildAppearanceTab(QTabWidget *tabs);
    void buildPrivacyTab(QTabWidget *tabs);
    void buildHistoryTab(QTabWidget *tabs);
    void buildAboutTab(QTabWidget *tabs);
    void buildFavoritesTab(QTabWidget *tabs);
    void buildLanguageTab(QTabWidget *tabs);
    void applyTheme();
    void retranslateUi();
    void saveAndClose();

    QSettings *m_settings;
    QString    m_chosenAccent;
    bool       m_historyCleared = false;
    QString    m_selectedLanguage;
    QPoint     m_dragPosition;
    QTabWidget *m_tabs = nullptr;
    QLabel    *m_header = nullptr;
    QLabel    *m_accentSwatch = nullptr;
    QComboBox *m_searchCombo  = nullptr;
    QComboBox *m_languageCombo = nullptr;
    QListWidget *m_favoritesList = nullptr;
    QLineEdit *m_homeEdit     = nullptr;
    QCheckBox *m_darkCheck    = nullptr;
    QCheckBox *m_jsCheck      = nullptr;
    QCheckBox *m_cookieCheck  = nullptr;
    QPushButton *m_cancelBtn = nullptr;
    QPushButton *m_saveBtn = nullptr;
    QPushButton *m_closeBtn = nullptr;
    QGroupBox *m_searchGroup = nullptr;
    QGroupBox *m_homeGroup = nullptr;
    QGroupBox *m_langGroup = nullptr;
    QLabel *m_langLabel = nullptr;
    QLabel *m_langNoteLabel = nullptr;
};
