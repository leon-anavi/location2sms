#include <QPainter>
#include <QDebug>
#include <QApplication>

#include "languageswidget.h"

LanguagesWidget::LanguagesWidget(QWidget *parent) :
    QWidget(parent),
    m_pLangWidgetLayout(NULL),
    m_pLangList(NULL),
    m_pLangSelect(NULL)
{
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

    m_pLangList->setCurrentRow(0);

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

void LanguagesWidget::paintEvent(QPaintEvent* /*event*/)
{
  QColor backgroundColor(32,32,32,220);
  QPainter customPainter(this);
  customPainter.fillRect(rect(),backgroundColor);
}
//------------------------------------------------------------------------------

void LanguagesWidget::selectLang()
{
    //get selected row
    int nSelected = m_pLangList->currentRow();
    //change language
    switch (nSelected)
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
    //hide this view
    hide();
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



