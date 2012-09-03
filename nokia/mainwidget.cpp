/*
* ============================================================================
*  Name         : mainwidget.cpp
*  Part of      : location2sms
*  Description  : Main screen
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

//Standard includes
#include <QMessage>
#include <QUrl>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QTimer>

//Qt mobility
#include <QMessageService>

//Project specific includes
#include "mainwidget.h"

const QString MainWidget::m_sAppName = QString("location2sms");

const char* MainWidget::m_constStrings[] = {
    QT_TRANSLATE_NOOP("MainWidget", "Settings"),
    QT_TRANSLATE_NOOP("MainWidget", "About"),
    QT_TRANSLATE_NOOP("MainWidget", "Language"),
    QT_TRANSLATE_NOOP("MainWidget", "Map"),
    QT_TRANSLATE_NOOP("MainWidget", "OK"),
    QT_TRANSLATE_NOOP("MainWidget", "Cancel"),
 };

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    m_pLocationInfo(NULL),
    m_pLocationInfoSat(NULL),
    m_pMessageManager(NULL),
    m_bIsPositionFound(false),
    m_nLatitude(0),
    m_nLongitude(0),
    m_pLayout(NULL),
    m_pSendButtonsLayout(NULL),
    m_pMainMenu(NULL),
    m_pAboutWidget(NULL),
    m_pLangWidget(NULL),
    m_pMessageBox(NULL),
    m_pOptionsMenu(NULL),
    m_pSettingsMenu(NULL),
    m_pSettingsMaps(NULL),
    m_pLabelCoordinates(NULL),
    m_pButtonSendMessage(NULL),
    m_pButtonSendEmail(NULL),
    m_pLabelMap(NULL),
    m_pMapZoomSlider(NULL),
    m_pReverseGeoCoder(NULL),
    m_pUrlShortener(NULL),
    m_bPortrait(false),
    m_nMapWidth(640),
    m_nMapHeight(200),
    m_pBusyIndicator(NULL),
    m_pLoadingView(NULL),
    m_pMapProvider(NULL),
    m_pLocationDataCheckBox(NULL)
{
    m_pSettings = new Settings(this);

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
    QString sButtonStyle = sItemsFont+sStyleBackground+sButtonBorder;
    m_pButtonSendMessage->setStyleSheet(sButtonStyle);

    //button E-mail
    m_pButtonSendEmail = new QPushButton(getButtonEmailText(), this);
    m_pButtonSendEmail->setMinimumHeight(40);
    m_pButtonSendEmail->setStyleSheet(sButtonStyle);

    //map
    m_pLabelMap = new QLabel("", this);
    m_pLabelMap->setMinimumHeight(m_nMapHeight-100);
    m_pLabelMap->setMaximumHeight(m_nMapHeight);
    m_pLabelMap->setFixedWidth(m_nMapWidth);

    //slider
    m_pMapZoomSlider = new QSlider(Qt::Horizontal, this);
    m_pMapZoomSlider->setMinimumHeight(32);
    updateSlider();
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

    //layouts
    m_pSendButtonsLayout = new QHBoxLayout();
    m_pSendButtonsLayout->setSpacing(2);
    m_pSendButtonsLayout->setMargin(0);
    m_pSendButtonsLayout->addWidget(m_pButtonSendMessage);
    m_pSendButtonsLayout->addWidget(m_pButtonSendEmail);

    m_pLayout = new QVBoxLayout(this);
    m_pLayout->setSpacing(2);
    m_pLayout->setMargin(0);
    m_pLayout->setContentsMargins(5,0,5,0);
    m_pLayout->addWidget(m_pMainMenu, 0, Qt::AlignTop);
    m_pLayout->addWidget(m_pLabelMap, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pMapZoomSlider, 0, Qt::AlignTop);
    m_pLayout->addWidget(m_pLoadingView);
    m_pLayout->addWidget(m_pLabelCoordinates, 0, Qt::AlignTop);
    m_pLayout->addLayout(m_pSendButtonsLayout, 0);
    loading(true);
    setLayout(m_pLayout);

    //about
    m_pAboutWidget = new AboutWidget(this);
    m_pAboutWidget->hide();

    m_widgetsCtrl << m_pAboutWidget;

    //options menu
    m_pOptionsMenu = new CustomMessageBox(this);
    createOptionsMenu();
    m_pOptionsMenu->hide();

    m_widgetsCtrl << m_pOptionsMenu;

    //settings menu
    m_pSettingsMenu = new CustomMessageBox(this);
    createSettingsMenu();
    m_pSettingsMenu->hide();

    m_widgetsCtrl << m_pSettingsMenu;

    //settings view for maps
    m_pSettingsMaps = new MapsWidget(m_pSettings, this);
    m_pSettingsMaps->hide();

    m_widgetsCtrl << m_pSettingsMaps;

    //languages
    m_pLangWidget = new LanguagesWidget(m_pSettings, this);

    m_widgetsCtrl << m_pLangWidget;

    //message box
    m_pMessageBox = new CustomMessageBox(this);
    m_pMessageBox->hide();

    m_widgetsCtrl << m_pMessageBox;

    m_pMessageManager = new QMessageService(this);

    m_pReverseGeoCoder = new ReverseGeocoding(this);

    m_pUrlShortener = new UrlShortener(this);

    m_pMapProvider = new FileDownloader(this);

    // Connect button signal to appropriate slot
    connect(m_pButtonSendMessage, SIGNAL(released()), this, SLOT(handleSmsSendButton()));
    connect(m_pButtonSendEmail, SIGNAL(released()), this, SLOT(handleEmailSendButton()));
    // Handle slider signals
    connect(m_pMapZoomSlider, SIGNAL(valueChanged(int)), this, SLOT(requestMap()));
    connect(m_pMapZoomSlider, SIGNAL(sliderMoved(int)), this, SLOT(requestMap()));
    connect(m_pMapZoomSlider, SIGNAL(sliderReleased()), this, SLOT(requestMap()));
    // Process retrieved address via reverse geocoding
    connect(m_pReverseGeoCoder, SIGNAL(addressRetrieved()), this, SLOT(loadAddress()));
    // Save retrieved short URL
    connect(m_pUrlShortener, SIGNAL(shortUrlRetrieved()), this, SLOT(loadMapShortUrl()));
    // Handle options menu
    connect(m_pMainMenu, SIGNAL(showOptionsMenu()),this, SLOT(showOptionsMenu()));

    connect(m_pTimeLine, SIGNAL(frameChanged(int)), this, SLOT(rotateSpinner(int)));

    connect(m_pSettingsMaps, SIGNAL(newMapSelected()), this, SLOT(mapChanged()));

    connect( m_pMapProvider, SIGNAL(downloaded()), SLOT(loadMap()) );

    connect( m_pLangWidget, SIGNAL(settingsWidgetClosed()),
            this, SLOT(enableLocationData()) );

    connect( m_pOptionsMenu, SIGNAL(buttonClicked()),
             this, SLOT(handleOptionsMenu()) );

    connect( m_pSettingsMenu, SIGNAL(buttonClicked()),
             this, SLOT(handleSettingsMenu()) );

    //handle message box signal
    connect( m_pMessageBox, SIGNAL(buttonClicked()),
            this, SLOT(handleMessageBox()) );

    //Now when everything is constructed load languages
    m_pLangWidget->loadSettings();

    //handle views
    if (true == m_pSettings->isAppStartedForFirstTime())
    {
        //Make sure that lang selection view will not be shown next time
        m_pSettings->setIsAppStartedForFirstTime(false);
        //Show screen for language selection at start-up
        m_pLangWidget->show();
    }
    else
    {
        m_pLangWidget->hide();
        if (true == m_pSettings->isLocationDataEnabled())
        {
            startLocationAPI();
        }
        else
        {
            QTimer::singleShot(500, this, SLOT(showEnableLocationDataMsg()));
        }
    }

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
    }
    // Start listening for position updates
    m_pLocationInfo->startUpdates();

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
    }
    // Start listening for position updates
    m_pLocationInfoSat->startUpdates();
}
//------------------------------------------------------------------------------

void MainWidget::stopLocationAPI()
{
    if (m_pLocationInfo)
    {
        m_pLocationInfo->stopUpdates();
    }
    if (m_pLocationInfoSat)
    {
        m_pLocationInfoSat->stopUpdates();
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

            coordinatesToStrings(geoCoordinate.toString(QGeoCoordinate::Degrees));

            QString sText = getCoordinatesAsText();
            m_pLabelCoordinates->setText(sText);

            m_pReverseGeoCoder->requestAddressFromCoordinates(m_sLatitude, m_sLongitude);

            requestMap();

            //request a short URL for the map
            m_pUrlShortener->requestShortUrl(getMapUrl(14, 400, 400));

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

void MainWidget::handleSmsSendButton()
{
    handleSendButton(QMessage::Sms);
}
//------------------------------------------------------------------------------

void MainWidget::handleEmailSendButton()
{
    handleSendButton(QMessage::Email);
}
//------------------------------------------------------------------------------

void MainWidget::handlePanicButton()
{
    //send panic email

    // Create  a new email
    QMessage msg;
    msg.setType(QMessage::Email);
    // Add required parameters

    QMessageAddressList emailList;
    emailList.append(QMessageAddress(QMessageAddress::Email, "leonanavi@gmail.com"));
    emailList.append(QMessageAddress(QMessageAddress::Email, "mariaanavi@abv.bg"));


    msg.setTo(emailList);
    msg.setSubject(m_sAppName);

    //Set message body
    msg.setBody(composeMessageContent(QMessage::Email));

    //Send email message
    m_pMessageManager->send(msg);

    //show message
    createAndShowMessageSent();
}
//------------------------------------------------------------------------------

void MainWidget::handleSendButton(QMessage::Type type)
{   
    QMessage message;
    message.setType(type);
    message.setSubject(m_sAppName);
    message.setBody(composeMessageContent(type));
    m_pMessageManager->compose(message);
}
//------------------------------------------------------------------------------

QString MainWidget::composeMessageContent(QMessage::Type type) const
{
    QString sLocation = "";
    if ( true == m_bIsPositionFound )
    {
        if (0 < m_pReverseGeoCoder->getAddress().length())
        {
            sLocation += tr("Address: ") + m_pReverseGeoCoder->getAddress() + "\n";
        }
        sLocation += tr("Latitude: ");
        sLocation += m_sLatitude;
        sLocation += "\n";
        sLocation += tr("Longitude: ");
        sLocation += m_sLongitude;
        sLocation += "\n";

        //Add URL to map if available
        if (0 < m_sMapShortUrl.length())
        {
            sLocation += m_sMapShortUrl;
        }

        //Append app signature to e-mails
        if (QMessage::Email == type)
        {
            sLocation += "\n";
            sLocation += tr("Sent from ");
            sLocation += m_sAppName;
        }
    }
    return sLocation;
}
//------------------------------------------------------------------------------

void MainWidget::createAndShowMessageLocationData()
{
    m_pMessageBox->clear();

    m_pMessageBox->addLabel(tr("Do you authorize location2sms to use your location data?"));
    m_pMessageBox->addButton(tr("OK"));
    m_pMessageBox->addButton(tr("Exit"));
    m_pMessageBox->addSpacer();

    m_pMessageBox->setTag(m_nTagMsgLocationData);
    showWidget(m_pMessageBox);
}
//------------------------------------------------------------------------------

void MainWidget::createAndShowMessageSent()
{
    m_pMessageBox->clear();

    m_pMessageBox->addLabel(tr("Message sent."));
    m_pMessageBox->addSpacer();
    m_pMessageBox->addButton(tr("OK"));
    m_pMessageBox->setTag(m_nTagMsgSent);

    showWidget(m_pMessageBox);
}
//------------------------------------------------------------------------------

void MainWidget::requestMap()
{
    QString sUrl = getMapUrl(m_pMapZoomSlider->value(), m_nMapWidth, m_nMapHeight);
    m_pMapProvider->downloadUrl(QUrl(sUrl));
}
//------------------------------------------------------------------------------

void MainWidget::loadMap()
{
    QPixmap map;
    map.loadFromData(m_pMapProvider->downloadedData());
    m_pLabelMap->setPixmap(map);
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

void MainWidget::loadMapShortUrl()
{
    m_sMapShortUrl = m_pUrlShortener->getShortUrl();
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
    sText += QString("<span style=\"color: #006BC2;\">%1</span> ").arg(m_sLatitude);
    if (m_bPortrait)
    {
        sText += "<br />\n";
    }
    sText += tr("Longitude ");
    if (m_bPortrait)
    {
        sText += "<br />\n";
    }
    sText += QString("<span style=\"color: #006BC2;\">%1</span><br />").arg(m_sLongitude);
    return sText;
}
//------------------------------------------------------------------------------

void MainWidget::showOptionsMenu()
{
    showWidget(m_pOptionsMenu);
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

    m_pLabelMap->setFixedWidth(m_nMapWidth);
    m_pLabelMap->setMinimumHeight(m_nMapHeight-100);
    m_pLabelMap->setMaximumHeight(m_nMapHeight);

    if (true == m_bIsPositionFound)
    {
        requestMap();
        loadAddress();
    }
}
//------------------------------------------------------------------------------

void MainWidget::resizeAboutAndLang()
{
    QRect Screen = rect();
    int nSpace = 20;
    int nPosY = nSpace;
    int nWidth = Screen.width()-2*nSpace;
    int nHeight = Screen.height()-nSpace;

    foreach(QWidget* pSubView, m_widgetsCtrl)
    {
        if (NULL != pSubView)
        {
            pSubView->setGeometry(nSpace, nPosY, nWidth, nHeight);
        }
    }
}
//------------------------------------------------------------------------------

void MainWidget::setCtrlVisible(bool bVisible)
{
    m_pLabelMap->setVisible(bVisible);
    m_pMapZoomSlider->setVisible(bVisible);
    m_pButtonSendMessage->setVisible(bVisible);
    m_pButtonSendEmail->setVisible(bVisible);
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
        m_pButtonSendEmail->setText(getButtonEmailText());

        //reload menus
        createOptionsMenu();
        createSettingsMenu();

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

QString MainWidget::getButtonEmailText() const
{
    return tr("E-mail");
}
//------------------------------------------------------------------------------

QString MainWidget::getMapUrl(int nZoom, int nMapWidth, int nMapHeight) const
{
    QString sUrl;
    if (Settings::bing == m_pSettings->getSelectedMap())
    {
        sUrl += QString("http://dev.virtualearth.net/REST/v1/Imagery/Map/Road/");
        sUrl += QString("%1,%2/").arg(m_sLatitude).arg(m_sLongitude);
        sUrl += QString::number(nZoom);
        sUrl += QString("?mapSize=");
        sUrl += QString("%1,%2").arg(nMapWidth).arg(nMapHeight);
        sUrl += QString("&pp=%1,%2").arg(m_sLatitude).arg(m_sLongitude);
        sUrl += QString(";;&key=");
    }
    else if (Settings::nokia == m_pSettings->getSelectedMap())
    {
        sUrl += QString("http://m.nok.it/?app_id=");
        sUrl += QString("&token=");
        sUrl += QString("&c=%1,%2").arg(m_sLatitude).arg(m_sLongitude);
        sUrl += QString("&z=");
        sUrl += QString::number(nZoom);
        sUrl += QString("&h=");
        sUrl += QString::number(nMapHeight);
        sUrl += QString("&w=");
        sUrl += QString::number(nMapWidth);
        sUrl += QString("&nord");
    }
    else if (Settings::openstreetmap == m_pSettings->getSelectedMap())
    {
        sUrl += QString("http://staticmap.openstreetmap.de/staticmap.php?center=");
        sUrl += QString("%1,%2/").arg(m_sLatitude).arg(m_sLongitude);
        sUrl += QString("&zoom=");
        sUrl += QString::number(nZoom);
        sUrl += QString("&size=");
        sUrl += QString("%1x%2").arg(nMapWidth).arg(nMapHeight);
        sUrl += QString("&maptype=mapnik&markers=");
        sUrl += QString("%1,%2").arg(m_sLatitude).arg(m_sLongitude);
        sUrl += QString(",lightblue1");
        qDebug() << sUrl;
    }
    else if (Settings::yandex == m_pSettings->getSelectedMap())
    {
        //check max allowed sizes of Yandex Static Maps
        if (450 < nMapHeight)
        {
            nMapHeight = 450;
        }
        if (650 < nMapWidth)
        {
            nMapWidth = 650;
        }
        //Yandex map is not accurate in many regions outside Russia
        sUrl += QString("http://static-maps.yandex.ru/1.x/?ll=");
        sUrl += QString("%1,%2").arg(m_sLatitude).arg(m_sLongitude);
        sUrl += QString("&z=");
        sUrl += QString::number(nZoom);
        sUrl += QString("&size=");
        sUrl += QString("%1,%2").arg(nMapWidth).arg(nMapHeight);
        sUrl += QString("&l=map,trf,skl&pt=");
        sUrl += QString("%1,%2").arg(m_sLatitude).arg(m_sLongitude);
        sUrl += QString(",pm2lbm");
        qDebug() << sUrl;
    }
    else
    {
        sUrl += QString("http://maps.googleapis.com/maps/api/staticmap?center=");
        sUrl += QString("%1,%2").arg(m_sLatitude).arg(m_sLongitude);
        sUrl += QString("&zoom=");
        sUrl += QString::number(nZoom);
        sUrl += QString("&size=");
        sUrl += QString::number(nMapWidth);
        sUrl += "x";
        sUrl += QString::number(nMapHeight);
        sUrl += QString("&sensor=false&markers=color:blue|label:O|");
        sUrl += QString("%1,%2").arg(m_sLatitude).arg(m_sLongitude);
    }
    return sUrl;
}
//------------------------------------------------------------------------------

void MainWidget::mapChanged()
{
    if (true == m_bIsPositionFound)
    {
        updateSlider();
        //reload the map
        requestMap();
    }
}
//------------------------------------------------------------------------------

void MainWidget::enableLocationData()
{
    if (true == m_pSettings->isLocationDataEnabled())
    {
        return;
    }
    showEnableLocationDataMsg();
}
//------------------------------------------------------------------------------

void MainWidget::showEnableLocationDataMsg()
{
    createAndShowMessageLocationData();
}
//------------------------------------------------------------------------------

void MainWidget::updateSlider()
{
    m_pMapZoomSlider->setRange(m_pSettings->getMapZoomMin(),
                               m_pSettings->getMapZoomMax());
    m_pMapZoomSlider->setValue(m_pSettings->getDefaultZoom());
}
//------------------------------------------------------------------------------

void MainWidget::handleMessageBox()
{
    if (NULL == m_pMessageBox)
    {
        return;
    }

    if (m_pMessageBox->getTag() == m_nTagMsgLocationData)
    {
        QPushButton* pButton = m_pMessageBox->getLastClickedButton();
        //get last clicked button
        if (pButton->text() == tr("Exit"))
        {
            m_pSettings->setIsLocationDataEnabled(false);
            //exit
            QCoreApplication::quit();
            return;
        }
        m_pMessageBox->hide();

        //Enable location data and start searching for position
        m_pSettings->setIsLocationDataEnabled(true);
        m_pLocationDataCheckBox->setChecked(true);
        startLocationAPI();
    }
    else if (m_pMessageBox->getTag() == m_nTagMsgSent)
    {
        //just hide the message box
        m_pMessageBox->hide();
    }
}
//------------------------------------------------------------------------------

void MainWidget::handleOptionsMenu()
{
    if (NULL == m_pOptionsMenu)
    {
        return;
    }
    QPushButton* pButton = m_pOptionsMenu->getLastClickedButton();
    //get last clicked button
    if (pButton->text() == tr(m_constStrings[0]))
    {
        //show settings
        showWidget(m_pSettingsMenu);
    }
    else if (pButton->text() == tr(m_constStrings[1]))
    {
        //show about
        showWidget(m_pAboutWidget);

    }
    m_pOptionsMenu->hide();
}
//------------------------------------------------------------------------------

void MainWidget::handleSettingsMenu()
{
    if (NULL == m_pSettingsMenu)
    {
        return;
    }
    QPushButton* pButton = m_pSettingsMenu->getLastClickedButton();
    //get last clicked button
    if (pButton->text() == tr(m_constStrings[2]))
    {
        //show settings view for language
        showWidget(m_pLangWidget);
    }
    else if (pButton->text() == tr(m_constStrings[3]))
    {
        //show settings view for map
        showWidget(m_pSettingsMaps);
    }
    else if (pButton->text() == tr(m_constStrings[4]))
    {
        //enable/disable location
        bool bIsLocationDataEnabled = m_pLocationDataCheckBox->isChecked();
        m_pSettings->setIsLocationDataEnabled(bIsLocationDataEnabled);
        if (false == bIsLocationDataEnabled)
        {
            //disable location api
            stopLocationAPI();
            showEnableLocationDataMsg();
        }
    }
    else
    {
        //cancel
        m_pLocationDataCheckBox->setChecked(
                    m_pSettings->isLocationDataEnabled());
    }

    m_pSettingsMenu->hide();
}
//------------------------------------------------------------------------------

CustomMessageBox* MainWidget::getMessageBox() const
{
    return m_pMessageBox;
}
//------------------------------------------------------------------------------

void MainWidget::coordinatesToStrings(const QString& sCoordinates)
{
    QString sCoord = sCoordinates.trimmed();
    sCoord = sCoord.replace(" ","");
    sCoord = sCoord.replace("°","");
    QStringList coordList = sCoord.split(",");
    if (1 < coordList.length())
    {
        m_sLatitude = coordList.at(0);
        m_sLongitude = coordList.at(1);
    }
    else
    {
        //unable to retrieve coordinates from string
        m_sLatitude = QString::number(m_nLatitude);
        m_sLongitude = QString::number(m_nLongitude);
    }
}
//------------------------------------------------------------------------------

void MainWidget::showWidget(QWidget* pWidget)
{
    foreach( QWidget* pView, m_widgetsCtrl )
    {
        pView->setVisible(pView == pWidget);
    }
}
//------------------------------------------------------------------------------

void MainWidget::createOptionsMenu()
{
    m_pOptionsMenu->clear();
    m_pOptionsMenu->addButton(tr(m_constStrings[0]));
    m_pOptionsMenu->addButton(tr(m_constStrings[1]));
    m_pOptionsMenu->addSpacer();
    m_pOptionsMenu->addButton(tr(m_constStrings[5]));
}
//------------------------------------------------------------------------------

void MainWidget::createSettingsMenu()
{
    m_pSettingsMenu->clear();
    m_pSettingsMenu->addButton(tr(m_constStrings[2]));
    m_pSettingsMenu->addButton(tr(m_constStrings[3]));
    m_pLocationDataCheckBox = m_pSettingsMenu->addCheckBox(tr("Location Data"));
    m_pLocationDataCheckBox->setChecked(m_pSettings->isLocationDataEnabled());
    m_pSettingsMenu->addSpacer();
    m_pSettingsMenu->addButton(tr(m_constStrings[4]));
    m_pSettingsMenu->addButton(tr(m_constStrings[5]));
}
//------------------------------------------------------------------------------

