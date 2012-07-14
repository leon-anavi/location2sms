/*
* ============================================================================
*  Name         : mainwindow.h
*  Part of      : location2sms
*  Description  : Main window
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Standard includes
#include <QtGui/QMainWindow>

//Project specific includes
#include "mainwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    MainWidget* m_pMainWidget;

public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

    void resizeGui(int nWidth = 0, int nHeight = 0);

private:

    // from QMainWindow
    void resizeEvent(QResizeEvent* event);

};

#endif // MAINWINDOW_H
