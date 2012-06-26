#include <QtGui/QApplication>

#include "mainwindow.h"
#ifndef Q_OS_SYMBIAN
#include "qmlapplicationviewer.h"
#include "proxywidget.h"
#endif

Q_DECL_EXPORT int main(int argc, char *argv[])
{
#ifdef Q_OS_SYMBIAN
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
    mainWindow.showExpanded();
    return app.exec();
#else
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    qmlRegisterType<ProxyWidget>("ProxyWidget", 1, 0, "ProxyWidgetItem");

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/TestView/main.qml"));
    viewer->showExpanded();

    return app->exec();
#endif
}
