/*
* ============================================================================
*  Name         : mainwindow.cpp
*  Part of      : location2sms
*  Description  : Main window
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

//Project specific includes
#include "mainwindow.h"

//Standard includes
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_pMainWidget(NULL)
{
    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, QColor(0, 0, 0) );
    setAutoFillBackground(true);
    setPalette(Pal);

    m_pMainWidget = new MainWidget(this);
    m_pMainWidget->setAutoFillBackground(true);
    m_pMainWidget->setPalette(Pal);

    m_pMainWidget->show();

#ifdef Q_OS_SYMBIAN
    resizeGui();
#endif
}
//------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };

    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    showFullScreen();
#endif
}
//------------------------------------------------------------------------------

void MainWindow::resizeGui(int nWidth, int nHeight)
{
    if ( (0 == nWidth) || (0 == nHeight) )
    {
        QRect Screen = QApplication::desktop()->screenGeometry();
        nWidth = Screen.width();
        nHeight = Screen.height();
    }
    m_pMainWidget->setGeometry(0, 0, nWidth, nHeight);
    bool bPortraint = false;
    //limited to 640px by Google Maps API
    int nMapWidth = 640;
    int nMapHeight = 200;
    if (nHeight > nWidth)
    {
        bPortraint = true;
        nMapWidth = nWidth;
        nMapHeight = nWidth;
    }
    m_pMainWidget->resizeGUI(bPortraint, nMapWidth, nMapHeight);
}
//------------------------------------------------------------------------------

void MainWindow::resizeEvent(QResizeEvent* /*event*/)
{
    resizeGui();
}
//------------------------------------------------------------------------------
