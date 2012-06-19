#include "mainwindow.h"

#include <QtGui/QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    //mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
    mainWindow.showFullScreen();

    return app.exec();
}
