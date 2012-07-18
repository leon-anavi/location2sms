/*
* ============================================================================
*  Name         : settingslistwidget.h
*  Part of      : location2sms
*  Description  : basic settings view with list
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

//Standard includes
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>

//Project specific includes
#include "settings.h"

class SettingsListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsListWidget(Settings* pSettings,
                            QWidget *parent = 0);

    virtual ~SettingsListWidget();

    /**
      * Read settings and load appropriate language
      *
      * @return nothing
      */
    virtual void loadSettings() = 0;

protected:

    //overload from QWidget
    void paintEvent(QPaintEvent* event);

    //overload from QWidget
    void changeEvent(QEvent* event);

    //overload from QWidget
    void resizeEvent(QResizeEvent* event);

signals:

    void settingsWidgetClosed();

protected slots:

    virtual void select() = 0;

public slots:

protected:

    Settings* m_pSettings;

    QVBoxLayout* m_pLayout;

    QLabel* m_pTitle;

    QListWidget* m_pList;

    QPushButton* m_pButtonSelect;

private:
    
};

#endif // SETTINGSWIDGET_H
