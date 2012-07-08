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
    QWidget(parent),
    m_pLangWidgetLayout(NULL),
    m_pLangLabel(NULL),
    m_pMapsLabel(NULL),
    m_pLangList(NULL),
    m_pMapsList(NULL),
    m_pLangSelect(NULL)
{
    m_pSettings = pSettings;

    QString sStyleBackground = "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4c4c4c, stop: 0.5 #333333, stop: 1 #202020);";
    QString sItemsFont = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sItemsFont += "8pt;";
#else
    sItemsFont += "22pt;";
#endif
    sItemsFont += "color: #FFFFFF;";

    QString sFontBold = QString("font-weight:bold;");

    QString sStyle = QString("background-color: transparent;");
    sStyle += sItemsFont;

    m_pLangLabel = new QLabel(tr("Language:"), this);
    m_pLangLabel->setStyleSheet(sStyle);

    m_pMapsLabel = new QLabel(tr("Map:"), this);
    m_pMapsLabel->setStyleSheet(sStyle);

    m_pLangList = new QListWidget(this);
    new QListWidgetItem("English", m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Български"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Türkçe"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Deutsch"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Română"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Ελληνικά"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Nederlands"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Čeština"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Bahasa Indonesia"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Русский"), m_pLangList);
    m_pLangList->setStyleSheet(sStyle+sFontBold);

    m_pMapsList = new QListWidget(this);
    new QListWidgetItem("Google", m_pMapsList);
    new QListWidgetItem("Bing", m_pMapsList);
    new QListWidgetItem("Nokia", m_pMapsList);
    new QListWidgetItem("OpenStreet Maps", m_pMapsList);
    m_pMapsList->setStyleSheet(sStyle+sFontBold);

    m_pLangSelect = new QPushButton(tr("OK"), this);
    QString sButtonBorder = "border-width:0px;border-style:solid;border-radius: 10px 10px / 10px 10px;";
    m_pLangSelect->setStyleSheet(sItemsFont+sStyleBackground+sButtonBorder);
    m_pLangSelect->setMinimumHeight(40);

    m_pLangWidgetLayout = new QVBoxLayout(this);
    m_pLangWidgetLayout->setSpacing(2);
    m_pLangWidgetLayout->setMargin(0);
    m_pLangWidgetLayout->setContentsMargins(5,0,5,0);
    m_pLangWidgetLayout->addWidget(m_pLangLabel, 0, Qt::AlignVCenter);
    m_pLangWidgetLayout->addWidget(m_pLangList, 0, Qt::AlignTop);
    m_pLangWidgetLayout->addWidget(m_pMapsLabel, 0, Qt::AlignVCenter);
    m_pLangWidgetLayout->addWidget(m_pMapsList, 0, Qt::AlignTop);
    m_pLangWidgetLayout->addWidget(m_pLangSelect, 0, Qt::AlignBottom);
    setLayout(m_pLangWidgetLayout);

    // Connect button signals to appropriate slot
    connect(m_pLangSelect, SIGNAL(released()), this, SLOT(selectLang()));
}
//------------------------------------------------------------------------------

LanguagesWidget::~LanguagesWidget()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void LanguagesWidget::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor(32,32,32,220);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}
//------------------------------------------------------------------------------

void LanguagesWidget::resizeGUI(int nPosX, int nPosY, int nWidth, int nHeight)
{
    setGeometry(nPosX, nPosY, nWidth, nHeight);
    int nButtonHeightAndSpacing = static_cast<int>(1.5*m_pLangSelect->height());
    int nMapListHeight = static_cast<int>(1.2*m_pMapsList->count()* m_pMapsList->fontMetrics().height());
    m_pMapsList->setMinimumHeight(nMapListHeight);

    int nLangListHeight = nHeight - m_pLangLabel->height() -
            m_pMapsLabel->height() - m_pMapsList->height() - nButtonHeightAndSpacing;
    m_pLangList->setMaximumHeight(nLangListHeight);
}
//------------------------------------------------------------------------------

void LanguagesWidget::selectLang()
{
    m_pSettings->setSelectedLanguage(m_pLangList->currentRow());
    loadSelectedLanguage();

    Settings::MapTypes eMap = Settings::google;
    switch (m_pMapsList->currentRow())
    {
        case 1:
            eMap = Settings::bing;
        break;
    }

    if (eMap != m_pSettings->getSelectedMap())
    {
        m_pSettings->setSelectedMap(eMap);
        emit mapChanged();
    }

    //hide this view
    hide();
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

void LanguagesWidget::loadLanguageSettings()
{
    m_pLangList->setCurrentRow(m_pSettings->getSelectedLanguage());
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
    m_pMapsList->setCurrentRow(nRow);

    //Make sure that lang selection view will not be shown next time
    if (true == m_pSettings->isAppStartedForFirstTime())
    {
        m_pSettings->setIsAppStartedForFirstTime(false);
    }
}
//------------------------------------------------------------------------------

