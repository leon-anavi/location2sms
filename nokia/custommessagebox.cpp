/*
* ============================================================================
*  Name         : custommessagebox.h
*  Part of      : location2sms
*  Description  : Custom message box
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

#include "custommessagebox.h"

#include <QPainter>
#include <QEvent>

CustomMessageBox::CustomMessageBox(QWidget *parent) :
                                    QWidget(parent),
                                    m_pLayout(NULL),
                                    m_pLastPressedButton(NULL),
                                    m_nTag(0)
{
    m_pLayout = new QVBoxLayout(this);
    m_pLayout->setSpacing(2);
    m_pLayout->setMargin(0);
    m_pLayout->setContentsMargins(5,10,10,5);
    setLayout(m_pLayout);
}
//------------------------------------------------------------------------------

CustomMessageBox::~CustomMessageBox()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

QPushButton* CustomMessageBox::addButton(const QString& sText)
{
    QPushButton* pButton = new QPushButton(sText, this);

    QString sItemsFont = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sItemsFont += "7pt;";
#else
    sItemsFont += "18pt;";
#endif
    sItemsFont += "font-weight:bold;color: #FFFFFF;";
    QString sButtonStyle = "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4c4c4c, stop: 0.5 #333333, stop: 1 #202020);";
    sButtonStyle += sItemsFont;
    sButtonStyle += "border-width:0px;border-style:solid;border-radius: 10px 10px / 10px 10px;";

    pButton->setStyleSheet(sButtonStyle);

    pButton->setMinimumHeight(40);

    connect(pButton, SIGNAL(released()), this, SLOT(handleButtonClicked()));

    m_pLayout->addWidget(pButton);
    return pButton;
}
//------------------------------------------------------------------------------

QCheckBox* CustomMessageBox::addCheckBox(const QString& sText)
{
    QCheckBox* pCheckBox = new QCheckBox(sText, this);

    QString sItemsFont = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sItemsFont += "7pt;";
#else
    sItemsFont += "18pt;";
#endif
    sItemsFont += "font-weight:bold;color: #FFFFFF;";

    pCheckBox->setStyleSheet(sItemsFont);

    pCheckBox->setMinimumHeight(40);

    m_pLayout->addWidget(pCheckBox);
    return pCheckBox;
}
//------------------------------------------------------------------------------

QLabel* CustomMessageBox::addLabel(const QString& sText)
{
    QLabel* pLabel = new QLabel(sText, this);
    pLabel->setWordWrap(true);

    QString sItemsFont = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sItemsFont += "7pt;";
#else
    sItemsFont += "18pt;";
#endif
    sItemsFont += "color: #FFFFFF;";

    pLabel->setStyleSheet(sItemsFont);

    m_pLayout->addWidget(pLabel);
    return pLabel;
}
//------------------------------------------------------------------------------

void CustomMessageBox::addSpacer()
{
    // Add a vertical spacer to take up the remaining available space
    QSpacerItem* pSpacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding );
    m_pLayout->addItem( pSpacer );
}
//------------------------------------------------------------------------------

void CustomMessageBox::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor(32,32,32,220);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}
//------------------------------------------------------------------------------

void CustomMessageBox::handleButtonClicked()
{
    m_pLastPressedButton = (QPushButton*)sender();
    emit buttonClicked();
}
//------------------------------------------------------------------------------

QPushButton* CustomMessageBox::getLastClickedButton()
{
    return m_pLastPressedButton;
}
//------------------------------------------------------------------------------

void CustomMessageBox::clear()
{
    if (NULL != m_pLayout)
    {
        clearLayout(dynamic_cast<QLayout*>(m_pLayout));
        repaint();
    }
}
//------------------------------------------------------------------------------

int CustomMessageBox::getTag() const
{
    return m_nTag;
}
//------------------------------------------------------------------------------

void CustomMessageBox::setTag(int nTag)
{
    m_nTag = nTag;
}
//------------------------------------------------------------------------------

void CustomMessageBox::clearLayout(QLayout* pLayout)
{
    QLayoutItem* pItem = NULL;
    while(pItem = pLayout->takeAt(0))
    {
        if (0 != pItem->layout())
        {
            //recursively delete other layout inside the main layout
            clearLayout(pItem->layout());
        }
        QWidget* pWidget = pItem->widget();
        if (0 != pWidget)
        {
            pLayout->removeWidget(pWidget);
            delete pWidget;
            pWidget = NULL;
        }
    }
}
//------------------------------------------------------------------------------

