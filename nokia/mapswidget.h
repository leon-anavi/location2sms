/*
* ============================================================================
*  Name         : mapswidget.h
*  Part of      : location2sms
*  Description  : manage maps
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

#ifndef MAPSWIDGET_H
#define MAPSWIDGET_H

//Standard includes

//Project specific includes
#include "settingslistwidget.h"

class MapsWidget : public SettingsListWidget
{
    Q_OBJECT

public:
    MapsWidget(Settings* pSettings, QWidget *parent = 0);


    virtual ~MapsWidget();

    /**
      * Read settings and load appropriate language
      *
      * @return nothing
      */
    void loadSettings();

protected slots:

    void select();

signals:

    void newMapSelected();

};

#endif // MAPSWIDGET_H
