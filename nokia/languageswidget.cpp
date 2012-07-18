/*
* ============================================================================
*  Name         : languageswidget.cpp
*  Part of      : location2sms
*  Description  : manage languages
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

//Standard includes
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QFile>

//Project specific includes
#include "languageswidget.h"

LanguagesWidget::LanguagesWidget(Settings* pSettings, QWidget *parent) :
    SettingsListWidget(pSettings, parent)
{
    m_pTitle->setText(tr("Language:"));

    new QListWidgetItem("English", m_pList);
    new QListWidgetItem(QString::fromUtf8("Български"), m_pList);
    new QListWidgetItem(QString::fromUtf8("Türkçe"), m_pList);
    new QListWidgetItem(QString::fromUtf8("Deutsch"), m_pList);
    new QListWidgetItem(QString::fromUtf8("Română"), m_pList);
    new QListWidgetItem(QString::fromUtf8("Ελληνικά"), m_pList);
    new QListWidgetItem(QString::fromUtf8("Nederlands"), m_pList);
    new QListWidgetItem(QString::fromUtf8("Čeština"), m_pList);
    new QListWidgetItem(QString::fromUtf8("Bahasa Indonesia"), m_pList);
    new QListWidgetItem(QString::fromUtf8("Русский"), m_pList);

}
//------------------------------------------------------------------------------

LanguagesWidget::~LanguagesWidget()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void LanguagesWidget::select()
{
    int nSelectedLang = m_pList->currentRow();
    if (m_pSettings->getSelectedLanguage() != nSelectedLang)
    {
        m_pSettings->setSelectedLanguage(nSelectedLang);
        loadSelectedLanguage();
    }

    //hide this view
    hide();

    emit settingsWidgetClosed();
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadSelectedLanguage()
{
    //change language
    switch (m_pSettings->getSelectedLanguage())
    {
        case 1:
            //Bulgarian
            loadBulgarian();
        break;
        case 2:
            //Turkish
            loadTurkish();
        break;
        case 3:
            loadGerman();
        break;
        case 4:
            loadRomanian();
        break;
        case 5:
            loadGreek();
        break;
        case 6:
            loadDutch();
        break;
        case 7:
            loadCzech();
        break;
        case 8:
            loadIndonesian();
        break;
        case 9:
            loadRussian();
        break;
        default:
            //English
            loadEnglish();
        break;
    }
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadBulgarian()
{
    if (m_Translator.load(":/translations/location2sms_bg"))
    {
        qDebug() << "Bulgarian translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load Bulgarian translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadEnglish()
{
    qDebug() << "Load English translation.";
    qApp->removeTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadTurkish()
{
    if (m_Translator.load(":/translations/location2sms_tr"))
    {
        qDebug() << "Turkish translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load Turkish translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadGerman()
{
    if (m_Translator.load(":/translations/location2sms_de"))
    {
        qDebug() << "German translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load German translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadRomanian()
{
    if (m_Translator.load(":/translations/location2sms_ro"))
    {
        qDebug() << "Romanian translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load Romanian translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadGreek()
{
    if (m_Translator.load(":/translations/location2sms_el"))
    {
        qDebug() << "Greek translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load Greek translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadDutch()
{
    if (m_Translator.load(":/translations/location2sms_nl"))
    {
        qDebug() << "Dutch translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load Dutch translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------


void LanguagesWidget::loadCzech()
{
    if (m_Translator.load(":/translations/location2sms_cs"))
    {
        qDebug() << "Czech translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load Czech translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadIndonesian()
{
    if (m_Translator.load(":/translations/location2sms_id"))
    {
        qDebug() << "Indonesian translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load Indonesian translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadRussian()
{
    if (m_Translator.load(":/translations/location2sms_ru"))
    {
        qDebug() << "Russian translation loaded.";
    }
    else
    {
        qDebug() << "Unable to load Russian translation.";
    }

    qApp->installTranslator(&m_Translator);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadSettings()
{
    m_pList->setCurrentRow(m_pSettings->getSelectedLanguage());
    //by default language is English so there is no need to reload it
    if (0 != m_pSettings->getSelectedLanguage())
    {
        loadSelectedLanguage();
    }

    int nRow = 0;
    switch (m_pSettings->getSelectedMap())
    {
        case Settings::bing:
            nRow = 1;
        break;
    }
    m_pList->setCurrentRow(nRow);
}
//------------------------------------------------------------------------------
