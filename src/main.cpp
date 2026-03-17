#include <QApplication>
#include <QSurfaceFormat>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    // Required for WebEngine
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QApplication app(argc, argv);
    app.setApplicationName("Stellar");
    app.setOrganizationName("StellarBrowser");
    app.setApplicationVersion("1.0.0");
    app.setWindowIcon(QIcon(":/icon.png"));

    // Better rendering
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow window;
    window.show();

    // Open URL from command line if provided
    QStringList args = app.arguments();
    if (args.size() > 1) {
        window.openUrl(QUrl::fromUserInput(args.last()));
    }

    return app.exec();
}
