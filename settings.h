/*
* ============================================================================
*  Name         : settings.h
*  Part of      : location2sms
*  Description  : settings back-end
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT

public:

    enum MapTypes { google, bing, nokia, openstreetmaps };

private:

    QString m_sSettingsFile;

    bool m_bIsAppStartedForFirstTime;

    int m_nSelectedLanguage;

    MapTypes m_eMapType;

    int m_nMapZoomMin;

    int m_nMapZoomMax;

    int m_nMapZoomDefault;

    static const int m_nMapZoomMinGoogle = 1;
    static const int m_nMapZoomMaxGoogle = 19;
    static const int m_nMapDefaultZoomGoogle = 14;

    static const int m_nMapZoomMinBing = 1;
    static const int m_nMapZoomMaxBing = 18;
    static const int m_nMapDefaultZoomBing = 14;

    static const int m_nMapZoomMinNokia = 2;
    static const int m_nMapZoomMaxNokia = 18;
    static const int m_nMapDefaultZoomNokia = 14;

    static const int m_nMapZoomMinOpenstreetMap = 2;
    static const int m_nMapZoomMaxOpenstreetMap = 18;
    static const int m_nMapDefaultZoomOpenstreetMap = 14;

public:

    explicit Settings(QObject *parent = 0);

    virtual ~Settings();

    /**
      * Is application started for first time
      *
      * @return bool
      */
    bool isAppStartedForFirstTime() const;

    /**
      * set if the application is started for first time or not
      *
      * @param bIsFirstTime
      *
      * @return noting
      */
    void setIsAppStartedForFirstTime(bool bIsFirstTime);

    /**
      * Get selected language
      *
      * @return int
      */
    int getSelectedLanguage() const;

    /**
      * set selected language
      *
      * @param nLanguage
      *
      * @return nothing
      */
    void setSelectedLanguage(int nLanguage);

    /**
      * Get selected map type
      *
      * @return MapTypes
      */
    MapTypes getSelectedMap() const;

    /**
      * Get type of the selected map
      *
      * @param eMapType
      *
      * @return nothing
      */
    void setSelectedMap(MapTypes eMapType);

    /**
      * get max zoom
      *
      * @return int
      */
    int getMapZoomMin() const;

    /**
      * get min zoom
      *
      * @return int
      */
    int getMapZoomMax() const;

    /**
      * get default zoom
      *
      * @return int
      */
    int getDefaultZoom() const;

private:

    /**
      * Read settings and load appropriate language
      *
      * @return nothing
      */
    void loadSettings();

    /**
      * Save settings
      *
      * @return nothing
      */
    void saveSettings();

signals:
    
public slots:
    
};

#endif // SETTINGS_H
