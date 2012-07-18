/*
* ============================================================================
*  Name         : settingslistwidget.cpp
*  Part of      : location2sms
*  Description  : basic settings view with list
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

//Standard includes
#include <QPainter>
#include <QEvent>

//Project specific includes
#include "settingslistwidget.h"

SettingsListWidget::SettingsListWidget(Settings* pSettings,
                               QWidget *parent) :
    QWidget(parent),
    m_pSettings(NULL),
    m_pLayout(NULL),
    m_pTitle(NULL),
    m_pList(NULL),
    m_pButtonSelect(NULL)
{
    m_pSettings = pSettings;

    QString sStyleBackground = "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4c4c4c, stop: 0.5 #333333, stop: 1 #202020);";
    QString sItemsFont = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sItemsFont += "6pt;";
#else
    sItemsFont += "22pt;";
#endif
    sItemsFont += "color: #FFFFFF;";

    QString sFontBold = QString("font-weight:bold;");

    QString sStyle = QString("background-color: transparent;");
    sStyle += sItemsFont;

    m_pTitle = new QLabel(this);
    m_pTitle->setStyleSheet(sStyle);

    m_pList = new QListWidget(this);
    m_pList->setStyleSheet(sStyle+sFontBold);

    QString sButtonBorder = "border-width:0px;border-style:solid;border-radius: 10px 10px / 10px 10px;";
    QString sButtonStyle = sItemsFont+sStyleBackground+sButtonBorder;

    m_pButtonSelect = new QPushButton(tr("OK"), this);

    m_pButtonSelect->setStyleSheet(sButtonStyle);
    m_pButtonSelect->setMinimumHeight(40);

    m_pLayout = new QVBoxLayout(this);
    m_pLayout->setSpacing(2);
    m_pLayout->setMargin(0);
    m_pLayout->setContentsMargins(5,0,5,0);
    m_pLayout->addWidget(m_pTitle, 0, Qt::AlignVCenter);
    m_pLayout->addWidget(m_pList, 0, Qt::AlignTop);
    m_pLayout->addWidget(m_pButtonSelect, 0, Qt::AlignBottom);
    setLayout(m_pLayout);

    // Connect signals from buttons to appropriate slot
    connect(m_pButtonSelect, SIGNAL(released()), this, SLOT(select()));
}
//------------------------------------------------------------------------------

SettingsListWidget::~SettingsListWidget()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void SettingsListWidget::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor(32,32,32,220);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}
//------------------------------------------------------------------------------

void SettingsListWidget::changeEvent(QEvent* event)
{
    if (QEvent::LanguageChange == event->type())
    {
        //TODO: translate
    }
    QWidget::changeEvent(event);
}
//------------------------------------------------------------------------------

void SettingsListWidget::resizeEvent(QResizeEvent* event)
{
    //resize GUI
    int nButtonHeightAndSpacing = static_cast<int>(1.5*m_pButtonSelect->height());
    int nListHeight = height() - 2*nButtonHeightAndSpacing;
    m_pList->setMinimumHeight(nListHeight);

    QWidget::resizeEvent(event);
}
//------------------------------------------------------------------------------
