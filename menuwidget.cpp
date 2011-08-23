#include <QtCore/QCoreApplication>
#include <QPalette>

#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    m_pControlBar(NULL),
    m_pControlLabel(NULL),
    m_pControlHelp(NULL),
    m_pControlExit(NULL)
{
    initGui();
    //handle buttons
    connect(m_pControlHelp, SIGNAL(released()),this, SLOT(handleHelp()));
    connect(m_pControlExit, SIGNAL(released()),this, SLOT(handleExit()));

}
//------------------------------------------------------------------------------

void MenuWidget::initGui()
{
    int nMinHeight = 40;
    int nMinWidth = 80;

    QString sFontStyleTop = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sFontStyleTop += "8pt;";
#else
    sFontStyleTop += "20pt;";
#endif
    sFontStyleTop += "font-weight: bold;color: #FFFFFF;";

    QString sStyleBackground = "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4c4c4c, stop: 0.5 #333333, stop: 1 #202020);";
    QString sButtonBorder = "border-width:0px;border-style:solid;border-radius: 10px 10px / 10px 10px;";

    m_pControlLabel = new QLabel("<i>location<span style=\"color: #006BC2;\">2</span>sms</i>",this);
    m_pControlLabel->setMinimumWidth(200);
    m_pControlLabel->setMinimumHeight(nMinHeight);
    m_pControlLabel->setStyleSheet(sFontStyleTop);
    m_pControlLabel->setAlignment(Qt::AlignVCenter);

    m_pControlHelp = new QPushButton("  ?  ", this);
    m_pControlHelp->setMinimumWidth(nMinWidth);
    m_pControlHelp->setMinimumHeight(nMinHeight);
    m_pControlHelp->setStyleSheet(sFontStyleTop+sStyleBackground+sButtonBorder);

    m_pControlExit = new QPushButton("  X  ", this);
    m_pControlExit->setMinimumWidth(nMinWidth);
    m_pControlExit->setMinimumHeight(nMinHeight);
    m_pControlExit->setStyleSheet(sFontStyleTop+sStyleBackground+sButtonBorder);

    m_pControlBar = new QHBoxLayout(this);
    m_pControlBar->setSpacing(0);
    m_pControlBar->setMargin(0);
    m_pControlBar->setContentsMargins(0,0,0,0);
    m_pControlBar->addWidget(m_pControlLabel, 0, Qt::AlignLeft);
    QSpacerItem* pSpacerItem = new QSpacerItem(50, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_pControlBar->addItem(pSpacerItem);
    m_pControlBar->addWidget(m_pControlHelp, 0, Qt::AlignRight);
    QSpacerItem* pSpacerButtonsItem = new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    m_pControlBar->addItem(pSpacerButtonsItem);
    m_pControlBar->addWidget(m_pControlExit, 0, Qt::AlignRight);
    setLayout(m_pControlBar);
}
//------------------------------------------------------------------------------

void MenuWidget::handleHelp()
{
    emit showHelp();
}
//------------------------------------------------------------------------------

void MenuWidget::handleExit()
{
    QCoreApplication::quit();
}
//------------------------------------------------------------------------------

