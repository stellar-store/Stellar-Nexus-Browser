#include "downloadmanager.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QScrollArea>
#include <algorithm>

DownloadDialog::DownloadDialog(DownloadManager *manager, QWidget *parent)
    : QDialog(parent, Qt::Dialog), m_manager(manager) {
    
    setWindowTitle("Downloads — Nexus");
    setFixedSize(600, 500);
    setModal(false);
    setStyleSheet("background-color: #0D1117; color: #E6EDF3;");
    
    // Ventana sin marco - frameless
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    
    buildUI();
    
    // Timer para actualizar en tiempo real
    auto *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &DownloadDialog::updateDownloads);
    updateTimer->start(500); // Actualizar cada 500ms
}

void DownloadDialog::buildUI() {
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(10);

    // Header
    auto *headerRow = new QHBoxLayout;
    auto *header = new QLabel("↓  Downloads", this);
    header->setStyleSheet("font-size:16px; font-weight:bold; letter-spacing:2px; color: #E6EDF3;");
    headerRow->addWidget(header);
    headerRow->addStretch();
    
    auto *closeBtn = new QPushButton("✕", this);
    closeBtn->setFixedSize(32, 32);
    closeBtn->setObjectName("m_closeBtn");
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setStyleSheet(
        "#m_closeBtn { "
        "   background-color: transparent; "
        "   border: none; "
        "   color: #E6EDF3; "
        "   font-size: 18px; "
        "   font-weight: bold; "
        "   padding: 4px; "
        "   border-radius: 4px; "
        "} "
        "#m_closeBtn:hover { "
        "   background-color: #1C2330; "
        "   border: none; "
        "} "
        "#m_closeBtn:pressed { "
        "   background-color: #30363D; "
        "}"
    );
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::reject);
    headerRow->addWidget(closeBtn);
    layout->addLayout(headerRow);

    // Scroll area para descargas
    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    
    m_scrollContent = new QWidget(this);
    m_scrollLayout = new QVBoxLayout(m_scrollContent);
    m_scrollLayout->setContentsMargins(0, 0, 0, 0);
    m_scrollLayout->setSpacing(8);
    
    scrollArea->setWidget(m_scrollContent);
    layout->addWidget(scrollArea, 1);

    // Botones de acción
    auto *btnRow = new QHBoxLayout;
    
    auto *clearBtn = new QPushButton("Clear Completed", this);
    clearBtn->setStyleSheet(
        "QPushButton { "
        "   background-color: #1C2330; "
        "   border: 1px solid #30363D; "
        "   border-radius: 4px; "
        "   color: #E6EDF3; "
        "   padding: 6px 14px; "
        "   font-weight: bold; "
        "} "
        "QPushButton:hover { "
        "   background-color: #4FC3F7; "
        "   color: #000; "
        "   border-color: #4FC3F7; "
        "} "
        "QPushButton:pressed { "
        "   opacity: 0.8; "
        "}"
    );
    connect(clearBtn, &QPushButton::clicked, this, [this]{
        if (m_manager) {
            m_manager->clearCompleted();
            rebuildDownloadsList();
        }
    });
    
    btnRow->addWidget(clearBtn);
    btnRow->addStretch();
    layout->addLayout(btnRow);
    
    // Primera construcción de la lista de descargas
    rebuildDownloadsList();
}

void DownloadDialog::rebuildDownloadsList() {
    if (!m_scrollLayout) return;
    
    // Limpiar layout anterior
    QLayoutItem *item;
    while ((item = m_scrollLayout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }
    
    // Limpiar mapas de referencias
    m_progressBars.clear();
    m_sizeLabels.clear();

    if (!m_manager || m_manager->getDownloads().isEmpty()) {
        auto *empty = new QLabel("No downloads yet.", m_scrollContent);
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet("color: #58636E; padding: 40px;");
        m_scrollLayout->addWidget(empty);
    } else {
        const auto &downloads = m_manager->getDownloads();
        for (int i = 0; i < downloads.count(); ++i) {
            const auto &item = downloads[i];
            auto *card = new QWidget(m_scrollContent);
            card->setStyleSheet("background: rgba(255,255,255,0.04); border-radius:8px; padding:4px; border: 1px solid #30363D;");
            auto *cardLayout = new QVBoxLayout(card);
            cardLayout->setContentsMargins(12, 10, 12, 10);
            cardLayout->setSpacing(6);

            QFileInfo fi(item.filePath);
            auto *name = new QLabel(fi.fileName(), card);
            name->setStyleSheet("font-weight:bold; font-size:12px; color: #E6EDF3;");

            auto *row2 = new QHBoxLayout;
            auto *size = new QLabel(card);
            m_sizeLabels[i] = size;

            QString stateStr;
            if (item.finished && !item.failed) {
                stateStr = "✓ Completed";
                size->setStyleSheet("color: #56d364;");
            } else if (item.failed) {
                stateStr = "✗ Failed";
                size->setStyleSheet("color: #f85149;");
            } else {
                double recv = item.receivedBytes / 1024.0 / 1024.0;
                double tot  = item.totalBytes    / 1024.0 / 1024.0;
                stateStr = tot > 0 ? QString("%1 / %2 MB").arg(recv,0,'f',1).arg(tot,0,'f',1)
                                   : QString("%1 MB").arg(recv,0,'f',1);
                size->setStyleSheet("color: #4FC3F7;");
            }
            size->setText(stateStr);

            auto *openBtn = new QPushButton("Open", card);
            openBtn->setFixedHeight(24);
            openBtn->setFixedWidth(60);
            openBtn->setStyleSheet(
                "QPushButton { "
                "   background-color: #1C2330; "
                "   border: 1px solid #30363D; "
                "   border-radius: 4px; "
                "   color: #E6EDF3; "
                "   font-weight: bold; "
                "   font-size: 11px; "
                "} "
                "QPushButton:hover { "
                "   background-color: #4FC3F7; "
                "   color: #000; "
                "   border-color: #4FC3F7; "
                "} "
                "QPushButton:pressed { "
                "   opacity: 0.8; "
                "}"
            );
            QString path = item.filePath;
            connect(openBtn, &QPushButton::clicked, [path]{
                QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(path).absolutePath()));
            });

            row2->addWidget(size);
            row2->addStretch();
            
            // Botones para descargas activas
            if (!item.finished && item.request) {
                auto *pauseBtn = new QPushButton("Pause", card);
                pauseBtn->setFixedHeight(24);
                pauseBtn->setFixedWidth(60);
                pauseBtn->setStyleSheet(
                    "QPushButton { "
                    "   background-color: #1C2330; "
                    "   border: 1px solid #30363D; "
                    "   border-radius: 4px; "
                    "   color: #E6EDF3; "
                    "   font-weight: bold; "
                    "   font-size: 11px; "
                    "} "
                    "QPushButton:hover { "
                    "   background-color: #4FC3F7; "
                    "   color: #000; "
                    "   border-color: #4FC3F7; "
                    "} "
                    "QPushButton:pressed { "
                    "   opacity: 0.8; "
                    "}"
                );
                auto *req = item.request;
                auto *isPaused = new bool(false);
                connect(pauseBtn, &QPushButton::clicked, this, [req, pauseBtn, isPaused]{
                    if (req) {
                        if (*isPaused) {
                            req->resume();
                            pauseBtn->setText("Pause");
                            *isPaused = false;
                        } else {
                            req->pause();
                            pauseBtn->setText("Resume");
                            *isPaused = true;
                        }
                    }
                });
                
                auto *cancelBtn = new QPushButton("Cancel", card);
                cancelBtn->setFixedHeight(24);
                cancelBtn->setFixedWidth(60);
                cancelBtn->setStyleSheet(
                    "QPushButton { "
                    "   background-color: #1C2330; "
                    "   border: 1px solid #30363D; "
                    "   border-radius: 4px; "
                    "   color: #E6EDF3; "
                    "   font-weight: bold; "
                    "   font-size: 11px; "
                    "} "
                    "QPushButton:hover { "
                    "   background-color: #f85149; "
                    "   color: #fff; "
                    "   border-color: #f85149; "
                    "} "
                    "QPushButton:pressed { "
                    "   opacity: 0.8; "
                    "}"
                );
                connect(cancelBtn, &QPushButton::clicked, this, [req]{
                    if (req) {
                        req->cancel();
                    }
                });
                
                row2->addWidget(pauseBtn);
                row2->addWidget(cancelBtn);
            }
            
            row2->addWidget(openBtn);

            cardLayout->addWidget(name);

            if (!item.finished && item.totalBytes > 0) {
                auto *bar = new QProgressBar(card);
                bar->setRange(0, 100);
                bar->setValue(int(100.0 * item.receivedBytes / item.totalBytes));
                bar->setTextVisible(false);
                bar->setFixedHeight(4);
                bar->setStyleSheet(
                    "QProgressBar { border-radius:2px; background:#1C2330; }"
                    "QProgressBar::chunk { background:#4FC3F7; border-radius:2px; }");
                m_progressBars[i] = bar;
                cardLayout->addWidget(bar);
            }

            cardLayout->addLayout(row2);
            m_scrollLayout->addWidget(card);
        }
    }

    m_scrollLayout->addStretch();
}

void DownloadDialog::updateDownloads() {
    if (!m_manager) return;
    
    const auto &downloads = m_manager->getDownloads();
    for (int i = 0; i < downloads.count(); ++i) {
        const auto &item = downloads[i];
        
        // Actualizar el label de tamaño si existe
        if (m_sizeLabels.contains(i)) {
            QString stateStr;
            if (item.finished && !item.failed) {
                stateStr = "✓ Completed";
                m_sizeLabels[i]->setStyleSheet("color: #56d364;");
            } else if (item.failed) {
                stateStr = "✗ Failed";
                m_sizeLabels[i]->setStyleSheet("color: #f85149;");
            } else {
                double recv = item.receivedBytes / 1024.0 / 1024.0;
                double tot  = item.totalBytes    / 1024.0 / 1024.0;
                stateStr = tot > 0 ? QString("%1 / %2 MB").arg(recv,0,'f',1).arg(tot,0,'f',1)
                                   : QString("%1 MB").arg(recv,0,'f',1);
                m_sizeLabels[i]->setStyleSheet("color: #4FC3F7;");
            }
            m_sizeLabels[i]->setText(stateStr);
        }
        
        // Actualizar la barra de progreso si existe
        if (m_progressBars.contains(i) && !item.finished && item.totalBytes > 0) {
            int progress = int(100.0 * item.receivedBytes / item.totalBytes);
            m_progressBars[i]->setValue(progress);
        }
    }
}

void DownloadDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void DownloadDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

DownloadManager::DownloadManager(QObject *parent) : QObject(parent) {}

void DownloadManager::addDownload(QWebEngineDownloadRequest *dl) {
    // Ask user where to save
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)
                          + "/" + dl->suggestedFileName();
    QString savePath = QFileDialog::getSaveFileName(
        nullptr, "Save File", defaultPath);

    if (savePath.isEmpty()) {
        dl->cancel();
        return;
    }

    dl->setDownloadDirectory(QFileInfo(savePath).absolutePath());
    dl->setDownloadFileName(QFileInfo(savePath).fileName());
    dl->accept();

    DownloadItem item;
    item.request   = dl;
    item.filePath  = savePath;
    item.startTime = QDateTime::currentDateTime();
    m_downloads.prepend(item);

    int idx = 0;
    connect(dl, &QWebEngineDownloadRequest::receivedBytesChanged, this,
            [this, idx]() mutable {
                if (idx < m_downloads.size()) {
                    m_downloads[idx].receivedBytes = m_downloads[idx].request->receivedBytes();
                    m_downloads[idx].totalBytes    = m_downloads[idx].request->totalBytes();
                }
            });

    connect(dl, &QWebEngineDownloadRequest::isFinishedChanged, this,
            [this, idx, dl]() mutable {
                if (idx < m_downloads.size()) {
                    m_downloads[idx].finished = true;
                    m_downloads[idx].failed   =
                        (dl->state() == QWebEngineDownloadRequest::DownloadInterrupted);
                    if (!m_downloads[idx].failed)
                        emit downloadFinished(m_downloads[idx].filePath);
                }
            });

    emit downloadStarted(QFileInfo(savePath).fileName());
}

int DownloadManager::activeCount() const {
    int c = 0;
    for (const auto &d : m_downloads)
        if (!d.finished) ++c;
    return c;
}

void DownloadManager::clearCompleted() {
    m_downloads.erase(
        std::remove_if(m_downloads.begin(), m_downloads.end(),
                      [](const DownloadItem &item) { return item.finished; }),
        m_downloads.end()
    );
}

void DownloadManager::showDialog(QWidget *parent) {
    auto *dlg = new DownloadDialog(this, parent);
    dlg->show();
}
