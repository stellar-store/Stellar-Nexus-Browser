#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QSettings *settings, QWidget *parent)
    : QDialog(parent, Qt::Dialog), m_settings(settings) {
    setWindowTitle("Settings — Nexus");
    setFixedSize(800, 580);
    setModal(true);
    
    // Quitar la barra del sistema
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    m_chosenAccent = m_settings->value("theme/accent", "#4FC3F7").toString();
    m_selectedLanguage = m_settings->value("app/language", "English").toString();
    TranslationManager::instance().setLanguage(m_selectedLanguage);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    // Header con título y botón de cerrar
    auto *headerRow = new QHBoxLayout;
    m_header = new QLabel("⚙  Settings", this);
    m_header->setStyleSheet("font-size:16px; font-weight:bold; letter-spacing:2px;");
    headerRow->addWidget(m_header);
    headerRow->addStretch();
    
    m_closeBtn = new QPushButton("✕", this);
    m_closeBtn->setFixedSize(32, 32);
    m_closeBtn->setObjectName("m_closeBtn");
    m_closeBtn->setCursor(Qt::PointingHandCursor);
    m_closeBtn->setToolTip(TRANSLATE("UI", "Close"));
    headerRow->addWidget(m_closeBtn);
    layout->addLayout(headerRow);

    m_tabs = new QTabWidget(this);
    m_tabs->setDocumentMode(true);
    layout->addWidget(m_tabs, 1);

    buildGeneralTab(m_tabs);
    buildAppearanceTab(m_tabs);
    buildPrivacyTab(m_tabs);
    buildHistoryTab(m_tabs);
    buildFavoritesTab(m_tabs);
    buildLanguageTab(m_tabs);
    buildAboutTab(m_tabs);

    auto *btnRow = new QHBoxLayout;
    btnRow->addStretch();
    m_cancelBtn = new QPushButton(TRANSLATE("UI", "Cancel"), this);
    m_saveBtn   = new QPushButton(TRANSLATE("UI", "Save"), this);
    m_saveBtn->setDefault(true);
    m_cancelBtn->setObjectName("m_cancelBtn");
    m_saveBtn->setObjectName("m_saveBtn");
    m_cancelBtn->setToolTip(TRANSLATE("UI", "Cancel and discard changes"));
    m_saveBtn->setToolTip(TRANSLATE("UI", "Save settings and close"));
    btnRow->addWidget(m_cancelBtn);
    btnRow->addWidget(m_saveBtn);
    layout->addLayout(btnRow);

    connect(m_cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_saveBtn,   &QPushButton::clicked, this, &SettingsDialog::saveAndClose);
    connect(m_closeBtn,  &QPushButton::clicked, this, &QDialog::reject);

    applyTheme();
    retranslateUi();
}

void SettingsDialog::buildGeneralTab(QTabWidget *tabs) {
    auto *w      = new QWidget;
    auto *layout = new QVBoxLayout(w);
    layout->setContentsMargins(12,12,12,12);
    layout->setSpacing(14);

    // Search engine
    m_searchGroup = new QGroupBox("Search Engine", w);
    auto *seLayout = new QVBoxLayout(m_searchGroup);
    m_searchCombo = new QComboBox(m_searchGroup);
    m_searchCombo->addItem("DuckDuckGo",  "https://duckduckgo.com/?q=");
    m_searchCombo->addItem("Google",      "https://www.google.com/search?q=");
    m_searchCombo->addItem("Bing",        "https://www.bing.com/search?q=");
    m_searchCombo->addItem("Startpage",   "https://www.startpage.com/search?q=");
    m_searchCombo->addItem("Brave Search","https://search.brave.com/search?q=");
    m_searchCombo->addItem("Ecosia",      "https://www.ecosia.org/search?q=");

    QString curr = m_settings->value("search/engine", "https://duckduckgo.com/?q=").toString();
    for (int i = 0; i < m_searchCombo->count(); ++i) {
        if (m_searchCombo->itemData(i).toString() == curr) {
            m_searchCombo->setCurrentIndex(i);
            break;
        }
    }
    seLayout->addWidget(m_searchCombo);
    layout->addWidget(m_searchGroup);

    // Home page
    m_homeGroup  = new QGroupBox("Home Page", w);
    auto *homeLayout = new QVBoxLayout(m_homeGroup);
    m_homeEdit = new QLineEdit(m_settings->value("browser/home", "nexus://home").toString(), m_homeGroup);
    homeLayout->addWidget(m_homeEdit);
    layout->addWidget(m_homeGroup);

    layout->addStretch();
    tabs->addTab(w, TRANSLATE("UI", "General"));
}

void SettingsDialog::buildAppearanceTab(QTabWidget *tabs) {
    auto *w      = new QWidget;
    auto *layout = new QVBoxLayout(w);
    layout->setContentsMargins(12,12,12,12);
    layout->setSpacing(14);

    // Theme
    auto *themeGroup  = new QGroupBox(TRANSLATE("UI", "Theme"), w);
    auto *themeLayout = new QVBoxLayout(themeGroup);
    m_darkCheck = new QCheckBox(TRANSLATE("UI", "Dark mode"), themeGroup);
    m_darkCheck->setChecked(m_settings->value("theme/dark", true).toBool());
    themeLayout->addWidget(m_darkCheck);
    layout->addWidget(themeGroup);

    // Accent color
    auto *accentGroup  = new QGroupBox(TRANSLATE("UI", "Accent Color"), w);
    auto *accentLayout = new QHBoxLayout(accentGroup);

    m_accentSwatch = new QLabel(accentGroup);
    m_accentSwatch->setFixedSize(32, 32);
    m_accentSwatch->setStyleSheet(
        QString("background:%1; border-radius:6px; border:1px solid #30363D;")
        .arg(m_chosenAccent));

    auto *pickBtn = new QPushButton(TRANSLATE("UI", "Choose Color…"), accentGroup);
    pickBtn->setCursor(Qt::PointingHandCursor);
    connect(pickBtn, &QPushButton::clicked, this, [this]{
        QColor c = QColorDialog::getColor(QColor(m_chosenAccent), this, "Accent Color");
        if (c.isValid()) {
            m_chosenAccent = c.name();
            m_accentSwatch->setStyleSheet(
                QString("background:%1; border-radius:6px; border:1px solid #30363D;")
                .arg(m_chosenAccent));
        }
    });

    // Preset swatches
    QStringList presets = {"#4FC3F7","#7C4DFF","#00E676","#FF6D00",
                           "#F06292","#FFD740","#40C4FF","#E040FB"};
    auto *presetRow = new QHBoxLayout;
    for (const QString &color : presets) {
        auto *swatch = new QPushButton(accentGroup);
        swatch->setFixedSize(24, 24);
        swatch->setStyleSheet(QString(
            "QPushButton { background:%1; border-radius:12px; border:none; }"
            "QPushButton:hover { border:2px solid white; }").arg(color));
        QString col = color;
        connect(swatch, &QPushButton::clicked, this, [this, col]{
            m_chosenAccent = col;
            m_accentSwatch->setStyleSheet(
                QString("background:%1; border-radius:6px; border:1px solid #30363D;").arg(col));
        });
        presetRow->addWidget(swatch);
    }
    presetRow->addStretch();

    accentLayout->addWidget(m_accentSwatch);
    accentLayout->addWidget(pickBtn);
    accentLayout->addStretch();

    auto *accentVL = new QVBoxLayout;
    accentVL->addLayout(accentLayout);
    accentVL->addLayout(presetRow);
    // Replace accentGroup's default layout
    delete accentGroup->layout();
    accentGroup->setLayout(accentVL);

    layout->addWidget(accentGroup);
    layout->addStretch();
    tabs->addTab(w, TRANSLATE("UI", "Appearance"));
}

void SettingsDialog::buildPrivacyTab(QTabWidget *tabs) {
    auto *w      = new QWidget;
    auto *layout = new QVBoxLayout(w);
    layout->setContentsMargins(12,12,12,12);
    layout->setSpacing(14);

    auto *privGroup  = new QGroupBox(TRANSLATE("UI", "Privacy"), w);
    auto *privLayout = new QVBoxLayout(privGroup);

    m_jsCheck = new QCheckBox(TRANSLATE("UI", "Enable JavaScript"), privGroup);
    m_jsCheck->setChecked(m_settings->value("privacy/javascript", true).toBool());

    m_cookieCheck = new QCheckBox(TRANSLATE("UI", "Accept Cookies"), privGroup);
    m_cookieCheck->setChecked(m_settings->value("privacy/cookies", true).toBool());

    privLayout->addWidget(m_jsCheck);
    privLayout->addWidget(m_cookieCheck);
    layout->addWidget(privGroup);

    auto *note = new QLabel(TRANSLATE("UI", "Some settings require restarting tabs to take effect."), w);
    note->setWordWrap(true);
    note->setStyleSheet("color:#58636E; font-size:11px;");
    layout->addWidget(note);

    layout->addStretch();
    tabs->addTab(w, TRANSLATE("UI", "Privacy"));
}

void SettingsDialog::saveAndClose() {
    m_settings->setValue("search/engine",  m_searchCombo->currentData().toString());
    m_settings->setValue("browser/home",   m_homeEdit->text());
    m_settings->setValue("theme/dark",     m_darkCheck->isChecked());
    m_settings->setValue("theme/accent",   m_chosenAccent);
    m_settings->setValue("privacy/javascript", m_jsCheck->isChecked());
    m_settings->setValue("privacy/cookies",    m_cookieCheck->isChecked());
    m_settings->setValue("app/language",    m_languageCombo->currentText());

    // Save favorites
    QStringList favoritesList;
    for (int i = 0; i < m_favoritesList->count(); ++i) {
        QListWidgetItem *item = m_favoritesList->item(i);
        QString title = item->text();
        QString url = item->data(Qt::UserRole).toString();
        favoritesList.append(title + "|" + url);
    }
    m_settings->setValue("favorites/urls", favoritesList);

    accept();
}

void SettingsDialog::applyTheme() {
    QString accent = m_settings->value("theme/accent", "#4FC3F7").toString();
    bool dark = m_settings->value("theme/dark", true).toBool();

    QString bg     = dark ? "#0D1117" : "#F0F4F8";
    QString bg2    = dark ? "#161B22" : "#FFFFFF";
    QString bg3    = dark ? "#1C2330" : "#E8EDF3";
    QString text   = dark ? "#E6EDF3" : "#1A2332";
    QString border = dark ? "#30363D" : "#D0D7DE";
    QString muted  = dark ? "#8B949E" : "#656D76";

    // Stylesheet específico para todos los widgets en este diálogo
    QString qss = QString(R"(
        QDialog {
            background-color: %1;
            color: %4;
        }
        #m_cancelBtn, #m_saveBtn {
            background-color: %3;
            border: 1px solid %5;
            color: %4 !important;
            padding: 6px 14px;
            border-radius: 6px;
            font-weight: bold;
        }
        #m_cancelBtn:hover, #m_saveBtn:hover {
            background-color: %6 !important;
            color: #000 !important;
        }
        #m_cancelBtn:pressed, #m_saveBtn:pressed {
            opacity: 0.8;
        }
        QPushButton {
            background-color: %3;
            border: 1px solid %5;
            border-radius: 6px;
            padding: 6px 14px;
            color: %4 !important;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: %6;
            color: #000 !important;
            border-color: %6;
        }
        QPushButton:pressed {
            opacity: 0.8;
        }
        QLabel {
            background-color: transparent;
            color: %4 !important;
        }
        QLineEdit {
            background-color: %3;
            border: 1px solid %5;
            border-radius: 6px;
            padding: 4px 10px;
            color: %4 !important;
            selection-background-color: %6;
        }
        QLineEdit:focus {
            border: 1px solid %6;
        }
        QCheckBox {
            background-color: transparent;
            color: %4 !important;
        }
        QCheckBox::indicator {
            width: 16px; height: 16px;
            border: 1px solid %5;
            border-radius: 3px;
            background-color: %3;
        }
        QCheckBox::indicator:checked {
            background-color: %6;
            border-color: %6;
        }
        QComboBox {
            background-color: %3;
            border: 1px solid %5;
            border-radius: 6px;
            padding: 4px 10px;
            color: %4 !important;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox QAbstractItemView {
            background-color: %2;
            selection-background-color: %6;
            color: %4 !important;
        }
        QTabWidget {
            background-color: %1;
        }
        QTabWidget::pane {
            border: 1px solid %5;
        }
        QTabBar::tab {
            background-color: %3;
            border: 1px solid %5;
            border-bottom: none;
            padding: 6px 14px;
            color: %4;
            margin-right: 2px;
        }
        QTabBar::tab:selected {
            background-color: %2;
            border: 1px solid %5;
            border-bottom: 1px solid %2;
            color: %4;
        }
        QTabBar::close-button {
            background-color: %4 !important;
        }
        QTabBar::close-button:hover {
            background-color: %6 !important;
        }
        QGroupBox {
            background-color: transparent;
            border: 1px solid %5;
            border-radius: 8px;
            margin-top: 12px;
            padding-top: 8px;
            color: %7;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            color: %7;
        }
        QListWidget {
            background-color: %2;
            border: 1px solid %5;
            border-radius: 8px;
            color: %4 !important;
        }
        QListWidget::item:selected {
            background-color: %6;
            color: #000 !important;
        }
        QListWidget::item:hover {
            background-color: %3;
        }
        #m_closeBtn {
            background-color: transparent;
            border: none;
            color: %4 !important;
            font-size: 18px;
            font-weight: bold;
            padding: 4px;
            border-radius: 4px;
        }
        #m_closeBtn:hover {
            background-color: %3;
            border: none;
        }
        #m_closeBtn:pressed {
            background-color: %5;
        }
    )").arg(bg, bg2, bg3, text, border, accent, muted);

    setStyleSheet(qss);
}

void SettingsDialog::buildHistoryTab(QTabWidget *tabs) {
    auto *w      = new QWidget;
    auto *layout = new QVBoxLayout(w);
    layout->setContentsMargins(12,12,12,12);
    layout->setSpacing(14);

    // History settings
    auto *histGroup  = new QGroupBox(TRANSLATE("UI", "Settings"), w);
    auto *histLayout = new QVBoxLayout(histGroup);

    auto *descLabel = new QLabel(TRANSLATE("UI", "Manage your browsing history settings"), histGroup);
    descLabel->setStyleSheet("font-size:11px;");
    histLayout->addWidget(descLabel);

    auto *retainCheck = new QCheckBox(TRANSLATE("UI", "Keep history for 90 days"), histGroup);
    retainCheck->setChecked(m_settings->value("history/retain90days", true).toBool());
    histLayout->addWidget(retainCheck);

    // Display visited sites
    auto *sitesGroup = new QGroupBox(TRANSLATE("UI", "Visited Sites"), w);
    auto *sitesLayout = new QVBoxLayout(sitesGroup);

    auto *historyList = new QListWidget(sitesGroup);
    historyList->setStyleSheet("QListWidget { border-radius: 6px; }");

    // Load history from settings
    QStringList urls = m_settings->value("history/urls", QStringList()).toStringList();
    QStringList titles = m_settings->value("history/titles", QStringList()).toStringList();
    QStringList dates = m_settings->value("history/dates", QStringList()).toStringList();

    auto updateHistoryList = [this, historyList]() {
        historyList->clear();
        QStringList urls = m_settings->value("history/urls", QStringList()).toStringList();
        QStringList titles = m_settings->value("history/titles", QStringList()).toStringList();
        QStringList dates = m_settings->value("history/dates", QStringList()).toStringList();

        for (int i = urls.size() - 1; i >= 0; --i) {
            QString title = (i < titles.size() && !titles[i].isEmpty()) ? titles[i] : urls[i];
            QString date = (i < dates.size()) ? " — " + dates[i] : "";
            auto *item = new QListWidgetItem(title + date);
            item->setData(Qt::UserRole, urls[i]);
            historyList->addItem(item);
        }

        if (urls.isEmpty()) {
            auto *emptyItem = new QListWidgetItem(TRANSLATE("UI", "No browsing history"));
            emptyItem->setFlags(emptyItem->flags() & ~Qt::ItemIsSelectable);
            historyList->addItem(emptyItem);
        }
    };

    // Initial load
    updateHistoryList();

    auto *clearBtn = new QPushButton(TRANSLATE("UI", "Clear History"), histGroup);
    connect(clearBtn, &QPushButton::clicked, this, [this, historyList, updateHistoryList]{
        if (QMessageBox::warning(this, TRANSLATE("UI", "Clear History"), 
            TRANSLATE("UI", "Are you sure you want to clear your browsing history?"),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            // Clear history from settings
            m_settings->remove("history/urls");
            m_settings->remove("history/titles");
            m_settings->remove("history/dates");
            m_settings->sync();
            
            // Update the list
            updateHistoryList();
            m_historyCleared = true;
        }
    });
    histLayout->addWidget(clearBtn);

    layout->addWidget(histGroup);
    sitesLayout->addWidget(historyList);
    layout->addWidget(sitesGroup, 1);

    tabs->addTab(w, TRANSLATE("UI", "History"));
}

void SettingsDialog::buildAboutTab(QTabWidget *tabs) {
    auto *w      = new QWidget;
    auto *layout = new QVBoxLayout(w);
    layout->setContentsMargins(12,12,12,12);
    layout->setSpacing(14);

    // Icon
    auto *iconLabel = new QLabel(w);
    QPixmap icon(":/about.png");
    iconLabel->setPixmap(icon.scaledToWidth(80, Qt::SmoothTransformation));
    iconLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(iconLabel);

    auto *titleLabel = new QLabel(TRANSLATE("UI", "Stellar Browser"), w);
    titleLabel->setStyleSheet("font-size:18px; font-weight:bold;");
    layout->addWidget(titleLabel);

    auto *versionLabel = new QLabel(TRANSLATE("UI", "Version 1.0.0"), w);
    versionLabel->setStyleSheet("font-size:11px; color:#8B949E;");
    layout->addWidget(versionLabel);

    layout->addSpacing(12);

    auto *descLabel = new QLabel(
        "Stellar is a lightweight, high-performance web browser built with Qt and WebEngine.\n\n"
        "Features:\n"
        "• Fast and responsive browsing\n"
        "• Dark and light themes\n"
        "• Customizable search engines\n"
        "• Download manager\n"
        "• Bookmark management\n"
        "• History tracking\n\n"
        "© 2024 Stellar Browser Project", w);
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet("font-size:11px;");
    layout->addWidget(descLabel);

    layout->addStretch();
    tabs->addTab(w, TRANSLATE("UI", "About"));
}

void SettingsDialog::buildFavoritesTab(QTabWidget *tabs) {
    auto *w      = new QWidget;
    auto *layout = new QVBoxLayout(w);
    layout->setContentsMargins(12,12,12,12);
    layout->setSpacing(14);

    auto *favGroup = new QGroupBox(TRANSLATE("UI", "Saved Favorites"), w);
    auto *favLayout = new QVBoxLayout(favGroup);

    m_favoritesList = new QListWidget(favGroup);
    m_favoritesList->setMinimumHeight(200);

    // Load favorites from settings
    QStringList favorites = m_settings->value("favorites/urls", QStringList()).toStringList();
    for (const QString &url : favorites) {
        QStringList parts = url.split("|");
        if (parts.size() == 2) {
            QString title = parts[0];
            QString urlStr = parts[1];
            auto *item = new QListWidgetItem(title);
            item->setData(Qt::UserRole, urlStr);
            m_favoritesList->addItem(item);
        }
    }

    favLayout->addWidget(m_favoritesList);

    auto *btnLayout = new QHBoxLayout;
    
    auto *exportBtn = new QPushButton(TRANSLATE("UI", "Export as HTML"), favGroup);
    connect(exportBtn, &QPushButton::clicked, this, [this]{
        QString fileName = QFileDialog::getSaveFileName(this, 
            TRANSLATE("UI", "Export Favorites"), 
            QDir::homePath() + "/bookmarks.html",
            "HTML Files (*.html);;All Files (*)");
        
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                
                out << "<!DOCTYPE NETSCAPE-Bookmark-file-1>\n";
                out << "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=UTF-8\">\n";
                out << "<TITLE>Bookmarks</TITLE>\n";
                out << "<H1>Bookmarks</H1>\n";
                out << "<DL><p>\n";
                out << "    <DT><H3 ADD_DATE=\"" << QString::number(QDateTime::currentSecsSinceEpoch()) << "\">Nexus Bookmarks</H3>\n";
                out << "    <DL><p>\n";
                
                for (int i = 0; i < m_favoritesList->count(); ++i) {
                    QListWidgetItem *item = m_favoritesList->item(i);
                    QString title = item->text();
                    QString url = item->data(Qt::UserRole).toString();
                    
                    out << "        <DT><A HREF=\"" << url << "\" ADD_DATE=\""
                        << QString::number(QDateTime::currentSecsSinceEpoch()) << "\">"
                        << title << "</A>\n";
                }
                
                out << "    </DL><p>\n";
                out << "</DL><p>\n";
                
                file.close();
                QMessageBox::information(this, 
                    TRANSLATE("UI", "Export Successful"),
                    TRANSLATE("UI", "Favorites exported successfully to HTML file"));
            } else {
                QMessageBox::warning(this, 
                    TRANSLATE("UI", "Error"),
                    TRANSLATE("UI", "Could not open file for writing"));
            }
        }
    });
    
    auto *importBtn = new QPushButton(TRANSLATE("UI", "Import from HTML"), favGroup);
    connect(importBtn, &QPushButton::clicked, this, [this]{
        QString fileName = QFileDialog::getOpenFileName(this,
            TRANSLATE("UI", "Import Favorites"),
            QDir::homePath(),
            "HTML Files (*.html);;All Files (*)");
        
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString content = in.readAll();
                file.close();
                
                // Parse HTML for bookmarks
                QRegularExpression re(R"(<A\s+HREF=\"([^\"]+)\"[^>]*>([^<]+)</A>)", 
                                     QRegularExpression::CaseInsensitiveOption);
                QRegularExpressionMatchIterator i = re.globalMatch(content);
                
                int importedCount = 0;
                while (i.hasNext()) {
                    QRegularExpressionMatch match = i.next();
                    QString url = match.captured(1);
                    QString title = match.captured(2);
                    
                    // Check if already exists
                    bool exists = false;
                    for (int j = 0; j < m_favoritesList->count(); ++j) {
                        if (m_favoritesList->item(j)->data(Qt::UserRole).toString() == url) {
                            exists = true;
                            break;
                        }
                    }
                    
                    if (!exists && !url.isEmpty() && !title.isEmpty()) {
                        auto *item = new QListWidgetItem(title);
                        item->setData(Qt::UserRole, url);
                        m_favoritesList->addItem(item);
                        importedCount++;
                    }
                }
                
                QMessageBox::information(this,
                    TRANSLATE("UI", "Import Successful"),
                    TRANSLATE("UI", "Imported %1 new favorites").arg(importedCount));
            } else {
                QMessageBox::warning(this,
                    TRANSLATE("UI", "Error"),
                    TRANSLATE("UI", "Could not open file for reading"));
            }
        }
    });
    
    auto *removeBtn = new QPushButton(TRANSLATE("UI", "Remove"), favGroup);
    connect(removeBtn, &QPushButton::clicked, this, [this]{
        if (m_favoritesList->currentRow() >= 0) {
            delete m_favoritesList->takeItem(m_favoritesList->currentRow());
        }
    });
    
    btnLayout->addWidget(exportBtn);
    btnLayout->addWidget(importBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(removeBtn);
    favLayout->addLayout(btnLayout);

    layout->addWidget(favGroup);
    layout->addStretch();
    tabs->addTab(w, TRANSLATE("UI", "Favorites"));
}

void SettingsDialog::buildLanguageTab(QTabWidget *tabs) {
    auto *w      = new QWidget;
    auto *layout = new QVBoxLayout(w);
    layout->setContentsMargins(12,12,12,12);
    layout->setSpacing(14);

    // Language selection
    m_langGroup = new QGroupBox(TRANSLATE("UI", "Application Language"), w);
    auto *langLayout = new QVBoxLayout(m_langGroup);

    m_langLabel = new QLabel(TRANSLATE("UI", "Select your preferred language:"), m_langGroup);
    langLayout->addWidget(m_langLabel);

    m_languageCombo = new QComboBox(m_langGroup);
    m_languageCombo->addItem("English");
    m_languageCombo->addItem("Español");
    m_languageCombo->addItem("Português");

    int idx = m_languageCombo->findText(m_selectedLanguage);
    if (idx >= 0) {
        m_languageCombo->setCurrentIndex(idx);
    }

    langLayout->addWidget(m_languageCombo);

    m_langNoteLabel = new QLabel(TRANSLATE("UI", "Note: Language changes will take effect immediately."), m_langGroup);
    m_langNoteLabel->setWordWrap(true);
    m_langNoteLabel->setStyleSheet("font-size:10px; color:#8B949E;");
    langLayout->addWidget(m_langNoteLabel);

    // Connect language change to update UI
    connect(m_languageCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]{
        QString selectedLang = m_languageCombo->currentText();
        TranslationManager::instance().setLanguage(selectedLang);
        m_selectedLanguage = selectedLang;
        // Emit signal to notify main window
        emit languageChanged(selectedLang);
        // Update all dialog text
        retranslateUi();
    });

    layout->addWidget(m_langGroup);
    layout->addStretch();
    tabs->addTab(w, TRANSLATE("UI", "Language"));
}

void SettingsDialog::retranslateUi() {
    // Update header
    if (m_header) {
        m_header->setText("⚙  " + TRANSLATE("UI", "Settings"));
    }

    // Update button text
    if (m_cancelBtn) {
        m_cancelBtn->setText(TRANSLATE("UI", "Cancel"));
    }
    if (m_saveBtn) {
        m_saveBtn->setText(TRANSLATE("UI", "Save"));
    }

    // Update tab titles
    if (m_tabs) {
        m_tabs->setTabText(0, TRANSLATE("UI", "General"));
        m_tabs->setTabText(1, TRANSLATE("UI", "Appearance"));
        m_tabs->setTabText(2, TRANSLATE("UI", "Privacy"));
        m_tabs->setTabText(3, TRANSLATE("UI", "History"));
        m_tabs->setTabText(4, TRANSLATE("UI", "Favorites"));
        m_tabs->setTabText(5, TRANSLATE("UI", "Language"));
        m_tabs->setTabText(6, TRANSLATE("UI", "About"));
    }

    // Update group boxes
    if (m_searchGroup) {
        m_searchGroup->setTitle(TRANSLATE("UI", "Search Engine"));
    }
    if (m_homeGroup) {
        m_homeGroup->setTitle(TRANSLATE("UI", "Home Page"));
    }

    // Update language tab labels
    if (m_langLabel) {
        m_langLabel->setText(TRANSLATE("UI", "Select your preferred language:"));
    }
    if (m_langGroup) {
        m_langGroup->setTitle(TRANSLATE("UI", "Application Language"));
    }
    if (m_langNoteLabel) {
        m_langNoteLabel->setText(TRANSLATE("UI", "Note: Language changes will take effect immediately."));
    }

    // Update dark mode checkbox text
    if (m_darkCheck) {
        m_darkCheck->setText(TRANSLATE("UI", "Dark mode"));
    }

    // Update privacy checkboxes text
    if (m_jsCheck) {
        m_jsCheck->setText(TRANSLATE("UI", "Enable JavaScript"));
    }
    if (m_cookieCheck) {
        m_cookieCheck->setText(TRANSLATE("UI", "Accept Cookies"));
    }

    // Update button tooltips
    if (m_cancelBtn) {
        m_cancelBtn->setToolTip(TRANSLATE("UI", "Cancel and discard changes"));
    }
    if (m_saveBtn) {
        m_saveBtn->setToolTip(TRANSLATE("UI", "Save settings and close"));
    }
}

void SettingsDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void SettingsDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}
