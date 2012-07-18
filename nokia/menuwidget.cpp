/*
* ============================================================================
*  Name         : menuwidget.cpp
*  Part of      : location2sms
*  Description  : Menu
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

//Standard includes
#include <QtCore/QCoreApplication>
#include <QPalette>
#include <QDebug>

//Project specific includes
#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    m_pControlLabel(NULL),
    m_pControlOptions(NULL),
    m_pControlExit(NULL),
    m_pControlBar(NULL)
{
    initGui();

    //handle buttons
    connect(m_pControlOptions, SIGNAL(released()),this, SLOT(handleHelp()));

    if (NULL != m_pControlExit)
    {
        connect(m_pControlExit, SIGNAL(released()),this, SLOT(handleExit()));
    }
}
//------------------------------------------------------------------------------

MenuWidget::~MenuWidget()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void MenuWidget::initGui()
{
    int nMinHeight = 40;
    int nMinWidth = 80;

    QString sFontStyleTop = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sFontStyleTop += "8pt;";
    nMinWidth = 60;
#else
    sFontStyleTop += "20pt;";
#endif
    sFontStyleTop += "font-weight: bold;color: #FFFFFF;";

    QString sStyleBackground = "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4c4c4c, stop: 0.5 #333333, stop: 1 #202020);";
    QString sButtonBorder = "border-width:0px;border-style:solid;border-radius: 10px 10px / 10px 10px;";

    m_pControlLabel = new QLabel("<i>location<span style=\"color: #006BC2;\">2</span>sms</i>",this);
    m_pControlLabel->setMinimumWidth(180);
    m_pControlLabel->setMinimumHeight(nMinHeight);
    m_pControlLabel->setStyleSheet(sFontStyleTop);
    m_pControlLabel->setAlignment(Qt::AlignVCenter);

    QString sButtonStyle = sFontStyleTop+sStyleBackground+sButtonBorder;

    m_pControlOptions = new QPushButton("  O  ", this);
    m_pControlOptions->setMinimumWidth(nMinWidth);
    m_pControlOptions->setMinimumHeight(nMinHeight);
    m_pControlOptions->setStyleSheet(sButtonStyle);

#ifdef Q_OS_SYMBIAN
    m_pControlExit = new QPushButton("  X  ", this);
    m_pControlExit->setMinimumWidth(nMinWidth);
    m_pControlExit->setMinimumHeight(nMinHeight);
    m_pControlExit->setStyleSheet(sButtonStyle);
#endif

    m_pControlBar = new QHBoxLayout(this);
    m_pControlBar->setSpacing(0);
    m_pControlBar->setMargin(0);
    m_pControlBar->setContentsMargins(0,0,0,0);
    m_pControlBar->addWidget(m_pControlLabel, 0, Qt::AlignLeft);
    m_pControlBar->addItem(new QSpacerItem(50, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    m_pControlBar->addItem( new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Minimum) );
    m_pControlBar->addWidget(m_pControlOptions, 0, Qt::AlignRight);
    if (NULL != m_pControlExit)
    {
        m_pControlBar->addItem( new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Minimum) );
        m_pControlBar->addWidget(m_pControlExit, 0, Qt::AlignRight);
    }
    setLayout(m_pControlBar);
}
//------------------------------------------------------------------------------

void MenuWidget::handleHelp()
{
    emit showOptionsMenu();
}
//------------------------------------------------------------------------------

void MenuWidget::handleExit()
{
    QCoreApplication::quit();
}
//------------------------------------------------------------------------------

