/*
* ============================================================================
*  Name         : menuwidget.h
*  Part of      : location2sms
*  Description  : Menu
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

#ifndef MENUWIDGET_H
#define MENUWIDGET_H

//Standard includes
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = 0);

    virtual ~MenuWidget();

signals:

    void showOptionsMenu();

private slots:

    void handleHelp();

    void handleExit();

private:

    void initGui();

private:

    //controls
    QLabel* m_pControlLabel;

    QPushButton* m_pControlOptions;

    QPushButton* m_pControlExit;

    QHBoxLayout* m_pControlBar;

};

#endif // MENUWIDGET_H
