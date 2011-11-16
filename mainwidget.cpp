#include "mainwidget.h"
#include <QMessage>
#include <QUrl>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    m_pLocationInfo(NULL),
    m_pLocationInfoSat(NULL),
    m_pMessageManager(NULL),
    m_bIsPositionFound(false),
    m_nLatitude(0),
    m_nLongitude(0),
    m_pLayout(NULL),
    m_pMainMenu(NULL),
    m_pAboutWidget(NULL),
    m_pLangWidget(NULL),
    m_pLabelCoordinates(NULL),
    m_pButtonSendMessage(NULL),
    m_pWebView(NULL),
    m_pMapZoomSlider(NULL),
    m_pReverseGeoCoder(NULL),
    m_bPortrait(false),
    m_nMapWidth(640),
    m_nMapHeight(200),
    m_pBusyIndicator(NULL),
    m_pLoadingView(NULL)
{
    QString sStyleBackground = "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4c4c4c, stop: 0.5 #333333, stop: 1 #202020);";

    //menu
    m_pMainMenu = new MenuWidget(this);
#ifdef Q_OS_SYMBIAN
    m_pMainMenu->setMaximumHeight(40);
#else
    m_pMainMenu->setMaximumHeight(50);
#endif

    //labels
    QString sItemsFont = "font-size: ";
#ifdef Q_OS_SYMBIAN
    sItemsFont += "8pt;";
#else
    sItemsFont += "18pt;";
#endif
    sItemsFont += "font-weight:bold;color: #FFFFFF;";
    m_pLabelCoordinates = new QLabel(getWaitText(),this);
    m_pLabelCoordinates->setStyleSheet(sItemsFont);
    m_pLabelCoordinates->setMinimumHeight(50);
    m_pLabelCoordinates->setWordWrap(true);

    //button
    m_pButtonSendMessage = new QPushButton(getButtonSMSText(), this);
    m_pButtonSendMessage->setMinimumHeight(40);
    QString sButtonBorder = "border-width:0px;border-style:solid;border-radius: 10px 10px / 10px 10px;";
    m_pButtonSendMessage->setStyleSheet(sItemsFont+sStyleBackground+sButtonBorder);


    //web view
    m_pWebView = new QWebView(this);
    m_pWebView->setStyleSheet("background-color:#000000;");
    m_pWebView->setMinimumHeight(m_nMapHeight-100);
    m_pWebView->setMaximumHeight(m_nMapHeight);
    m_pWebView->setFixedWidth(m_nMapWidth);

    //slider
    m_pMapZoomSlider = new QSlider(Qt::Horizontal, this);
    m_pMapZoomSlider->setMinimumHeight(32);
    m_pMapZoomSlider->setRange(0,19);
    m_pMapZoomSlider->setValue(14);
    m_pMapZoomSlider->setSingleStep(1);
    m_pMapZoomSlider->setPageStep(1);

    QString sStyleSlider = "QSlider::groove:horizontal {";
    sStyleSlider += "border: 0px; background: #4c4c4c;";
    sStyleSlider += "height: 32px; border-radius: 10px 10px / 10px 10px; } \n";
    sStyleSlider +=  "QSlider::sub-page:horizontal {";
    sStyleSlider +=  "background: qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1,stop: 0 #808080, stop: 1 #44ABFF);";
    sStyleSlider +=  " background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #44ABFF, stop: 1 #006BC2);";
    sStyleSlider +=  "border: 0px solid #777;height: 32px;border-radius: 10px 10px / 10px 10px;} \n";
    sStyleSlider +=  "QSlider::add-page:horizontal {background: #4c4c4c;border: 0px solid #777;";
    sStyleSlider +=  "height: 32px;border-radius: 10px 10px / 10px 10px; } \n";
    sStyleSlider +=  "QSlider::handle:horizontal {";
    sStyleSlider +=  "background: #808080;";
    sStyleSlider +=  "border: 0px solid;width: 20px;margin: -2px 0;";
    sStyleSlider +=  "border-radius: 0px; } \n";
    m_pMapZoomSlider->setStyleSheet(sStyleSlider);


    QGraphicsScene* pScene = new QGraphicsScene(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,0,0));
    pScene->setBackgroundBrush(brush);
    m_pBusyIndicator = new BusyIndicator();
    m_pBusyIndicator->setBackgroundColor(QColor(68,171,255));
    m_pBusyIndicator->setForegroundColor(QColor(0,107,194));
    pScene->addItem(dynamic_cast<QGraphicsItem*>(m_pBusyIndicator));

    m_pLoadingView = new QGraphicsView(pScene, this);
    m_pLoadingView->setStyleSheet( "QGraphicsView { border-style: none; }" );
    m_pLoadingView->setMinimumHeight(200);

    m_pTimeLine = new QTimeLine(1000, this);
    m_pTimeLine->setLoopCount(0);
    m_pTimeLine->setFrameRange(0, 36);

    //layout
    m_pLayout = new QVBoxLayout(this);
    m_pLayout->setSpacing(2);
    m_pLayout->setMargin(0);
    m_pLayout->setContentsMargins(5,0,5,0);
    m_pLayout->addWidget(m_pMainMenu, 0, Qt::AlignTop);
    m_pLayout->addWidget(m_pWebView, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pMapZoomSlider, 0, Qt::AlignTop);
    m_pLayout->addWidget(m_pLoadingView);
    m_pLayout->addWidget(m_pLabelCoordinates, 0, Qt::AlignTop);
    m_pLayout->addWidget(m_pButtonSendMessage, 0, Qt::AlignBottom);
    loading(true);
    setLayout(m_pLayout);

    //about
    m_pAboutWidget = new AboutWidget(this);
    m_pAboutWidget->hide();

    //languages
    m_pLangWidget = new LanguagesWidget(this);
    if (true == m_pLangWidget->isAppStartedForFirstTime())
    {
        //Make sure that lang selection view will not be shown next time
        m_pLangWidget->setIsAppStartedForFirstTime(false);
        //Show screen for language selection at start-up
        m_pLangWidget->show();
    }
    else
    {
        m_pLangWidget->hide();
    }

    m_pMessageManager = new QMessageService(this);

    m_pReverseGeoCoder = new ReverseGeocoding(this);

    // Connect button signal to appropriate slot
    connect(m_pButtonSendMessage, SIGNAL(released()), this, SLOT(handleSendButton()));
    // Handle slider signals
    connect(m_pMapZoomSlider, SIGNAL(valueChanged(int)), this, SLOT(loadMap()));
    connect(m_pMapZoomSlider, SIGNAL(sliderMoved(int)), this, SLOT(loadMap()));
    connect(m_pMapZoomSlider, SIGNAL(sliderReleased()), this, SLOT(loadMap()));
    // Process retrieved address via reverse geocoding
    connect(m_pReverseGeoCoder, SIGNAL(addressRetrieved()), this, SLOT(loadAddress()));
    // Handle help
    connect(m_pMainMenu, SIGNAL(showHelp()),this, SLOT(handleAbout()));
    //handle languages
    connect(m_pMainMenu, SIGNAL(showLang()),this, SLOT(handleLang()));

    connect(m_pAboutWidget, SIGNAL(aboutClosed()),this, SLOT(handleAbout()));
    connect(m_pTimeLine, SIGNAL(frameChanged(int)), this, SLOT(rotateSpinner(int)));

    startLocationAPI();

    //Now when everything is constructed load languages
    m_pLangWidget->loadLanguageSettings();
}
//------------------------------------------------------------------------------

MainWidget::~MainWidget()
{
    if (m_pBusyIndicator)
    {
        delete m_pBusyIndicator;
        m_pBusyIndicator = NULL;
    }
}
//------------------------------------------------------------------------------

void MainWidget::startLocationAPI()
{
    // Obtain the location data source if it is not obtained already
    if (!m_pLocationInfo)
    {
        m_pLocationInfo =
            QGeoPositionInfoSource::createDefaultSource(this);

        //Select positioning method
        m_pLocationInfo->setPreferredPositioningMethods(
                    QGeoPositionInfoSource::NonSatellitePositioningMethods);

        // When the position is changed the positionUpdated function is called
        connect(m_pLocationInfo, SIGNAL(positionUpdated(QGeoPositionInfo)),
                      this, SLOT(positionUpdated(QGeoPositionInfo)));

        // Start listening for position updates
        m_pLocationInfo->startUpdates();
    }

    if (!m_pLocationInfoSat)
    {
        m_pLocationInfoSat =
            QGeoPositionInfoSource::createDefaultSource(this);

        //Select positioning method
        m_pLocationInfoSat->setPreferredPositioningMethods(
                        QGeoPositionInfoSource::SatellitePositioningMethods);

        // When the position is changed the positionUpdated function is called
        connect(m_pLocationInfoSat, SIGNAL(positionUpdated(QGeoPositionInfo)),
                      this, SLOT(positionUpdated(QGeoPositionInfo)));

        // Start listening for position updates
        m_pLocationInfoSat->startUpdates();
    }
}
//------------------------------------------------------------------------------

void MainWidget::positionUpdated(QGeoPositionInfo geoPositionInfo)
{
    if (geoPositionInfo.isValid())
    {
        // Get the current location coordinates
        QGeoCoordinate geoCoordinate = geoPositionInfo.coordinate();
        if ( (false == m_bIsPositionFound) ||
             (round(geoCoordinate.latitude(),3) != round(m_nLatitude,3)) ||
             (round(geoCoordinate.longitude(),3) != round(m_nLongitude,3)) )
        {
            m_bIsPositionFound = true;
            //reload infomation only if the coordinates have been changed
            m_nLatitude = geoCoordinate.latitude();
            m_nLongitude = geoCoordinate.longitude();
            QString sText = getCoordinatesAsText();
            m_pLabelCoordinates->setText(sText);

            m_pReverseGeoCoder->requestAddressFromCoordinates(m_nLatitude, m_nLongitude);

            loadMap();

            loading(false);
        }
        else
        {
            //do not update GUI
            m_bIsPositionFound = true;
        }
    }
}
//------------------------------------------------------------------------------

void MainWidget::handleSendButton()
{   
    qDebug() << "SMS button pressed.";
    QMessage message;
    message.setType(QMessage::Sms);
    if ( true == m_bIsPositionFound )
    {
        QString sLocation;
        if (0 < m_pReverseGeoCoder->getAddress().length())
        {
            sLocation += tr("Address: ") + m_pReverseGeoCoder->getAddress() + "\n";
        }
        sLocation += QString(tr("Latitude: %1 \nLongitude: %2")).
                                            arg(m_nLatitude).arg(m_nLongitude);
        message.setBody(sLocation);
    }
    m_pMessageManager->compose(message);
}
//------------------------------------------------------------------------------

void MainWidget::loadMap()
{
    QString sUrl = QString("http://maps.googleapis.com/maps/api/staticmap?center=");
    sUrl += QString("%1,%2").arg(m_nLatitude).arg(m_nLongitude);
    sUrl += QString("&zoom=");
    sUrl += QString::number(m_pMapZoomSlider->value());
    sUrl += QString("&size=");
    sUrl += QString::number(m_nMapWidth);
    sUrl += "x";
    sUrl += QString::number(m_nMapHeight);
    sUrl += QString("&sensor=false&markers=color:blue|label:O|");
    sUrl += QString("%1,%2").arg(m_nLatitude).arg(m_nLongitude);
    m_pWebView->load(QUrl(sUrl));
}
//------------------------------------------------------------------------------

void MainWidget::loadAddress()
{
    QString sText = getCoordinatesAsText();
    QString sAddr = m_pReverseGeoCoder->getAddress();
    if (0 < sAddr.length())
    {
        sText += tr("Address ");
        if (m_bPortrait)
        {
            sText += "<br />\n";
        }
        sText += QString("<span style=\"color: #006BC2;\">%1</span>").arg(sAddr);
    }
    m_pLabelCoordinates->setText(sText);
}
//------------------------------------------------------------------------------

QString MainWidget::getCoordinatesAsText() const
{
    if (false == m_bIsPositionFound)
    {
        return "";
    }
    QString sText = tr("Latitude ");
    if (m_bPortrait)
    {
        sText += "<br />\n";
    }
    sText += QString("<span style=\"color: #006BC2;\">%1</span> ").arg(m_nLatitude);
    if (m_bPortrait)
    {
        sText += "<br />\n";
    }
    sText += tr("Longitude ");
    if (m_bPortrait)
    {
        sText += "<br />\n";
    }
    sText += QString("<span style=\"color: #006BC2;\">%1</span><br />").arg(m_nLongitude);
    return sText;
}
//------------------------------------------------------------------------------

void MainWidget::handleAbout()
{
    if (NULL == m_pAboutWidget)
    {
        return;
    }
    if (m_pAboutWidget->isVisible())
    {
        m_pAboutWidget->hide();
    }
    else
    {
        //make sure that the Language settings view is hidden
        m_pAboutWidget->hide();
        m_pAboutWidget->show();
    }

}
//------------------------------------------------------------------------------

void MainWidget::handleLang()
{
    if (NULL == m_pLangWidget)
    {
        return;
    }
    if (m_pLangWidget->isVisible())
    {
        m_pLangWidget->hide();
    }
    else
    {
        //make sure that the About view is hidden
        m_pAboutWidget->hide();
        m_pLangWidget->show();
    }
}
//------------------------------------------------------------------------------

void MainWidget::resizeGUI(bool bPortrait, int nMapWidth, int nMapHeight)
{
    resizeAboutAndLang();
    m_bPortrait = bPortrait;
    m_nMapWidth = nMapWidth;
    m_nMapHeight = nMapHeight;
    m_pWebView->setFixedWidth(m_nMapWidth);
    m_pWebView->setMinimumHeight(m_nMapHeight-100);
    m_pWebView->setMaximumHeight(m_nMapHeight);
    if (true == m_bIsPositionFound)
    {
        loadMap();
        loadAddress();
    }
}
//------------------------------------------------------------------------------

void MainWidget::resizeAboutAndLang()
{
    QRect Screen = QApplication::desktop()->screenGeometry();
    int nSpace = 20;
    int nPosY = m_pMainMenu->height() + nSpace;
    int nWidth = Screen.width()-2*nSpace;
    int nHeight = Screen.height()-2*nPosY-3*nSpace;
    m_pAboutWidget->setGeometry(nSpace, nPosY, nWidth, nHeight);

    m_pLangWidget->setGeometry(nSpace, nPosY, nWidth, nHeight);
}
//------------------------------------------------------------------------------

void MainWidget::setCtrlVisible(bool bVisible)
{
    m_pWebView->setVisible(bVisible);
    m_pMapZoomSlider->setVisible(bVisible);
    m_pButtonSendMessage->setVisible(bVisible);
}
//------------------------------------------------------------------------------

void MainWidget::rotateSpinner(int nValue)
{
    qreal nTrans = m_pBusyIndicator->actualOuterRadius();
    m_pBusyIndicator->setTransform(QTransform().translate(nTrans, nTrans).
                        rotate(nValue*10).translate(-1*nTrans, -1*nTrans));
}
//------------------------------------------------------------------------------

void MainWidget::loading(bool bStart)
{
    m_pLoadingView->setVisible(bStart);
    setCtrlVisible(!bStart);
    if (bStart)
    {
        m_pTimeLine->start();
        m_pLabelCoordinates->setAlignment(Qt::AlignHCenter);
    }
    else
    {
        m_pTimeLine->stop();
        m_pLabelCoordinates->setAlignment(Qt::AlignLeft);
        m_pLayout->removeWidget(m_pLoadingView);
    }
}
//------------------------------------------------------------------------------

void MainWidget::changeEvent(QEvent* event)
{
    if (QEvent::LanguageChange == event->type())
    {
        //translate
        m_pLabelCoordinates->setText(getWaitText());

        m_pButtonSendMessage->setText(getButtonSMSText());

        loadAddress();
    }
    QWidget::changeEvent(event);
}
//------------------------------------------------------------------------------

QString MainWidget::getWaitText() const
{
    QString sWait = tr("Please wait...");
    return "<span style=\"color: #006BC2;\">"+sWait+"</span>";
}
//------------------------------------------------------------------------------

QString MainWidget::getButtonSMSText() const
{
    return tr("SMS");
}
//------------------------------------------------------------------------------



