/*
* ============================================================================
*  Name         : settings.cpp
*  Part of      : location2sms
*  Description  : settings back-end
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

//Standard includes
#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QFile>

//Project specific includes
#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent),
    m_bIsAppStartedForFirstTime(true),
    m_nSelectedLanguage(0),
    m_eMapType(google),
    m_nMapZoomMin(1),
    m_nMapZoomMax(18),
    m_nMapZoomDefault(14)
{
#ifdef Q_OS_SYMBIAN
    m_sSettingsFile = QApplication::applicationDirPath();
#else
    m_sSettingsFile ="/home/user";
#endif

    m_sSettingsFile += "/location2sms.ini";

    loadSettings();
}
//------------------------------------------------------------------------------

Settings::~Settings()
{
    saveSettings();
}
//------------------------------------------------------------------------------

void Settings::loadSettings()
{
    //check if file exists
    QFile settingsFile(m_sSettingsFile);
    if (false == settingsFile.exists())
    {
        return;
    }
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    m_bIsAppStartedForFirstTime =
                         settings.value("IsAppStartedForFirstTime").toBool();
    m_nSelectedLanguage = settings.value("SelectedLanguage").toInt();
    //Map type
    QString sMapType = settings.value("MapType").toString();
    if (0 == sMapType.compare(QString("google")))
    {
        setSelectedMap(google);
    }
    else
    {
        setSelectedMap(bing);
    }
}
//------------------------------------------------------------------------------

void Settings::saveSettings()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    settings.setValue("IsAppStartedForFirstTime", m_bIsAppStartedForFirstTime);
    settings.setValue("SelectedLanguage", m_nSelectedLanguage);
    QString sMapType = (google == m_eMapType) ? QString("google") : QString("bing");
    settings.setValue("MapType", sMapType);
}
//------------------------------------------------------------------------------

bool Settings::isAppStartedForFirstTime() const
{
    return m_bIsAppStartedForFirstTime;
}
//------------------------------------------------------------------------------

void Settings::setIsAppStartedForFirstTime(bool bIsFirstTime)
{
    m_bIsAppStartedForFirstTime = bIsFirstTime;
}
//------------------------------------------------------------------------------

int Settings::getSelectedLanguage() const
{
    return m_nSelectedLanguage;
}
//------------------------------------------------------------------------------

void Settings::setSelectedLanguage(int nLanguage)
{
    m_nSelectedLanguage = nLanguage;
}
//------------------------------------------------------------------------------

int Settings::getMapZoomMin() const
{
    return m_nMapZoomMin;
}
//------------------------------------------------------------------------------

int Settings::getMapZoomMax() const
{
    return m_nMapZoomMax;
}
//------------------------------------------------------------------------------

Settings::MapTypes Settings::getSelectedMap() const
{
    return m_eMapType;
}
//------------------------------------------------------------------------------

void Settings::setSelectedMap(MapTypes eMapType)
{
    m_eMapType = eMapType;
    if (google == m_eMapType)
    {
        m_nMapZoomMin = m_nMapZoomMinGoogle;
        m_nMapZoomMax = m_nMapZoomMaxGoogle;
        m_nMapZoomDefault = m_nMapDefaultZoomGoogle;
    }
    else
    {
        m_nMapZoomMin = m_nMapZoomMinBing;
        m_nMapZoomMax = m_nMapZoomMaxBing;
        m_nMapZoomDefault = m_nMapDefaultZoomBing;
    }
}
//------------------------------------------------------------------------------

int Settings::getDefaultZoom() const
{
    return m_nMapZoomDefault;
}
//------------------------------------------------------------------------------


