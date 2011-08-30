#include "aboutwidget.h"

#include <QPainter>
#include <QDebug>
#include <QEvent>

AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    m_pAboutWidgetLayout(NULL),
    m_pAboutInfo(NULL)
{
    QString sText = "<h2><i>location<span style=\"color: #006BC2;\">2</span>sms</i></h2>\n";
    sText += "version 1.0.0<br />\n";
    sText += QChar(0x00A9);
    sText += " 2011 Leon Anavi<br />\n"
        "http://anavi.org/<br />\n<br />\n"
        "<i>location<span style=\"color: #006BC2;\">2</span>sms</i> "
        "depends on GPS quality that the device delivers. "
        "Position accuracy of about 20 meters can be expected. "
        "The application is powered by Google Maps API and requires Internet connection. <br />\n<br />\n";
    m_pAboutInfo = new QLabel(sText, this);
    QString sItemsFont = "font-size:";
#ifdef Q_OS_SYMBIAN
    sItemsFont += "7pt;";
#else
    sItemsFont += "16pt;";
#endif
    sItemsFont += "font-weight:bold;color: #FFFFFF;";
    m_pAboutInfo->setStyleSheet(sItemsFont);
    m_pAboutInfo->setWordWrap(true);

    m_pAboutWidgetLayout = new QVBoxLayout(this);
    m_pAboutWidgetLayout->addWidget(m_pAboutInfo, 0, Qt::AlignTop);
    setLayout(m_pAboutWidgetLayout);
}
//------------------------------------------------------------------------------

AboutWidget::~AboutWidget()
{

}
//------------------------------------------------------------------------------

void AboutWidget::paintEvent(QPaintEvent* /*event*/)
{
  QColor backgroundColor(32,32,32,220);
  QPainter customPainter(this);
  customPainter.fillRect(rect(),backgroundColor);
}
//------------------------------------------------------------------------------

void AboutWidget::mousePressEvent(QMouseEvent* /*event*/)
{
    qDebug() << "hide about widget";
    hide();
}
//------------------------------------------------------------------------------
