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

//Standard includes

//Project specific includes
#include "mapswidget.h"

MapsWidget::MapsWidget(Settings* pSettings, QWidget *parent) :
    SettingsListWidget(pSettings, parent)
{
    m_pTitle->setText(getLabelText());
    m_pButtonSelect->setText(getButtonText());

    new QListWidgetItem("Google", m_pList);
    new QListWidgetItem("Google Satellite", m_pList);
    new QListWidgetItem("Bing", m_pList);
    new QListWidgetItem("Nokia", m_pList);
    new QListWidgetItem("OpenStreetMap", m_pList);
    new QListWidgetItem("Yandex", m_pList);

    loadSettings();
}
//------------------------------------------------------------------------------

MapsWidget::~MapsWidget()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void MapsWidget::loadSettings()
{
    int nRow = 0;
    switch (m_pSettings->getSelectedMap())
    {
        case Settings::googlesat:
            nRow = 1;
        break;
        case Settings::bing:
            nRow = 2;
        break;
        case Settings::nokia:
            nRow = 3;
        break;
        case Settings::openstreetmap:
            nRow = 4;
        break;
        case Settings::yandex:
            nRow = 5;
        break;
    }
    m_pList->setCurrentRow(nRow);
}
//------------------------------------------------------------------------------

void MapsWidget::select()
{
    Settings::MapTypes eMap = Settings::google;
    switch (m_pList->currentRow())
    {
        case 1:
            eMap = Settings::googlesat;
        break;
        case 2:
            eMap = Settings::bing;
        break;
        case 3:
            eMap = Settings::nokia;
        break;
        case 4:
            eMap = Settings::openstreetmap;
        break;
        case 5:
            eMap = Settings::yandex;
        break;
    }

    if (eMap != m_pSettings->getSelectedMap())
    {
        m_pSettings->setSelectedMap(eMap);
        emit newMapSelected();
    }

    //hide this view
    hide();

    emit settingsWidgetClosed();
}
//------------------------------------------------------------------------------

void MapsWidget::changeEvent(QEvent* event)
{
    if (QEvent::LanguageChange == event->type())
    {
        //translate
        m_pTitle->setText(getLabelText());
        m_pButtonSelect->setText(getButtonText());
    }
    QWidget::changeEvent(event);
}
//------------------------------------------------------------------------------

QString MapsWidget::getLabelText() const
{
    return tr("Map:");
}
//------------------------------------------------------------------------------

QString MapsWidget::getButtonText() const
{
    return tr("OK");
}
//------------------------------------------------------------------------------
