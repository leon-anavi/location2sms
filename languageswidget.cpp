#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QFile>

#include "languageswidget.h"

LanguagesWidget::LanguagesWidget(QWidget *parent) :
    QWidget(parent),
    m_pLangWidgetLayout(NULL),
    m_pLangList(NULL),
    m_pLangSelect(NULL),
    m_bIsAppStartedForFirstTime(true),
    m_nSelectedLanguage(0)
{

#ifdef Q_OS_SYMBIAN
    m_sSettingsFile = QApplication::applicationDirPath();
#else
    m_sSettingsFile ="/home/user";
#endif

    m_sSettingsFile += "/location2sms.ini";

    //load settings and eventually language
    loadSettings();

    qDebug() << "Settings file: " << m_sSettingsFile;

    QString sStyleBackground = "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4c4c4c, stop: 0.5 #333333, stop: 1 #202020);";
    QString sItemsFont = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sItemsFont += "8pt;";
#else
    sItemsFont += "22pt;";
#endif
    sItemsFont += "font-weight:bold;color: #FFFFFF;";

    m_pLangList = new QListWidget(this);
    new QListWidgetItem("English", m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Български"), m_pLangList);
    new QListWidgetItem(QString::fromUtf8("Türkçe"), m_pLangList);
    m_pLangList->setStyleSheet("background-color: transparent;"+sItemsFont);

    m_pLangSelect = new QPushButton(tr("OK"), this);
    QString sButtonBorder = "border-width:0px;border-style:solid;border-radius: 10px 10px / 10px 10px;";
    m_pLangSelect->setStyleSheet(sItemsFont+sStyleBackground+sButtonBorder);
    m_pLangSelect->setMinimumHeight(40);

    m_pLangWidgetLayout = new QVBoxLayout(this);
    m_pLangWidgetLayout->addWidget(m_pLangList, 0, Qt::AlignTop);
    m_pLangWidgetLayout->addWidget(m_pLangSelect, 0, Qt::AlignBottom);
    setLayout(m_pLangWidgetLayout);

    // Connect button signals to appropriate slot
    connect(m_pLangSelect, SIGNAL(released()), this, SLOT(selectLang()));
}
//------------------------------------------------------------------------------

LanguagesWidget::~LanguagesWidget()
{
    saveSettings();
}
//------------------------------------------------------------------------------

void LanguagesWidget::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor(32,32,32,220);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}
//------------------------------------------------------------------------------

void LanguagesWidget::selectLang()
{
    m_nSelectedLanguage = m_pLangList->currentRow();
    loadSelectedLanguage();
    //hide this view
    hide();
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadSelectedLanguage()
{
    //change language
    switch (m_nSelectedLanguage)
    {
        case 1:
            //Bulgarian
            loadBulgarian();
        break;
        case 2:
            //Turkish
            loadTurkish();
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

bool LanguagesWidget::isAppStartedForFirstTime() const
{
    return m_bIsAppStartedForFirstTime;
}
//------------------------------------------------------------------------------

void LanguagesWidget::setIsAppStartedForFirstTime(bool bIsFirstTime)
{
    m_bIsAppStartedForFirstTime = bIsFirstTime;
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadSettings()
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
}
//------------------------------------------------------------------------------

void LanguagesWidget::saveSettings()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    qDebug() << "Save: IsAppStartedForFirstTime=" << m_bIsAppStartedForFirstTime;
    settings.setValue("IsAppStartedForFirstTime", m_bIsAppStartedForFirstTime);
    settings.setValue("SelectedLanguage", m_nSelectedLanguage);
}
//------------------------------------------------------------------------------

void LanguagesWidget::loadLanguageSettings()
{
    m_pLangList->setCurrentRow(m_nSelectedLanguage);
    //by default language is English so there is no need to reload it
    if (0 != m_nSelectedLanguage)
    {
        loadSelectedLanguage();
    }

    //Make sure that lang selection view will not be shown next time
    if (true == m_bIsAppStartedForFirstTime)
    {
        m_bIsAppStartedForFirstTime = false;
    }
}
//------------------------------------------------------------------------------

