/*
* ============================================================================
*  Name         : mainwidget.h
*  Part of      : location2sms
*  Description  : Main screen
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

//Standard includes
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QGraphicsView>
#include <QTimeLine>
#include <QtCore/qmath.h>
#include <QList>

//Qt mobility
#include <qgeopositioninfo.h>
#include <QGeoPositionInfoSource>
#include <QMessageService>

//Qt WebKit
#include <QWebView>

//Project specific includes
#include "aboutwidget.h"
#include "menuwidget.h"
#include "reversegeocoding.h"
#include "busyindicator.h"
#include "languageswidget.h"
#include "urlshortener.h"
#include "settings.h"
#include "filedownloader.h"
#include "custommessagebox.h"
#include "mapswidget.h"

// QtMobility namespace
QTM_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

private:

    Settings* m_pSettings;

    QGeoPositionInfoSource* m_pLocationInfo;

    QGeoPositionInfoSource* m_pLocationInfoSat;

    QMessageService* m_pMessageManager;

    bool m_bIsPositionFound;

    qreal m_nLatitude;

    qreal m_nLongitude;

    QString m_sLatitude;

    QString m_sLongitude;

    QString m_sMapShortUrl;

    QVBoxLayout* m_pLayout;

    QHBoxLayout* m_pSendButtonsLayout;

    //main menu
    MenuWidget* m_pMainMenu;

    //all subviews
    QList<QWidget*> m_widgetsCtrl;

    //about widget
    AboutWidget* m_pAboutWidget;

    //language settings view
    LanguagesWidget* m_pLangWidget;

    //Custom message
    CustomMessageBox* m_pMessageBox;

    CustomMessageBox* m_pOptionsMenu;

    CustomMessageBox* m_pSettingsMenu;

    //settings view for maps
    MapsWidget* m_pSettingsMaps;

    QLabel* m_pLabelCoordinates;

    QPushButton* m_pButtonSendMessage;

    QPushButton* m_pButtonSendEmail;

    QLabel* m_pLabelMap;

    QSlider* m_pMapZoomSlider;

    ReverseGeocoding* m_pReverseGeoCoder;

    UrlShortener* m_pUrlShortener;

    bool m_bPortrait;

    int m_nMapWidth;

    int m_nMapHeight;

    BusyIndicator* m_pBusyIndicator;

    QTimeLine* m_pTimeLine;

    QGraphicsView* m_pLoadingView;

    FileDownloader* m_pMapProvider;

    QCheckBox* m_pLocationDataCheckBox;

    static const QString m_sAppName;

    static const int m_nTagMsgLocationData = 1;

    static const int m_nTagMsgSent = 2;

public:

    explicit MainWidget(QWidget *parent = 0);

    virtual ~MainWidget();

signals:

public slots:

    /**
     * Called when the current position is updated.
     *
     * @return nothing
     */
    void positionUpdated(QGeoPositionInfo geoPositionInfo);

private slots:

    /**
      * Handle SMS Send Button
      *
      * @return nothing
      */
    void handleSmsSendButton();

    /**
      * Handle E-mail Send Button
      *
      * @return nothing
      */
    void handleEmailSendButton();

    /**
      * Handle panic button by seding sms/email
      * to specified recipients
      *
      * @return nothing
      */
    void handlePanicButton();

    /**
      * Request the map
      *
      * @return nothing
      */
    void requestMap();

    /**
      * Load the map
      *
      * @return nothing
      */
    void loadMap();

    /**
      * Load address of the current location
      *
      * @return nothing
      */
    void loadAddress();

    /**
      * Load short URL
      *
      * @return nothing
      */
    void loadMapShortUrl();

    /**
      * Show or hide help (about) view
      *
      * @return nothing
      */
    void showOptionsMenu();

    /**
      * Show or hide language settings view
      *
      * @return nothing
      */
    void handleLang();

    /**
      * Rotate spinner
      *
      * @param nValue
      *
      * @return noting
      */
    void rotateSpinner(int nValue);

    /**
      * Reload settings
      *
      * @return nothing
      */
    void mapChanged();

    /**
      * Check if location data is disabled and ask the user to enable location
      *
      * @return nothing
      */
    void enableLocationData();

    /**
      * Ask the user to enable location
      *
      * @return nothing
      */
    void showEnableLocationDataMsg();

    /**
      * Handle message box for enabling location data
      *
      * @return nothing
      */
    void handleMessageBox();

    /**
      * Handle options menu
      *
      * @return nothing
      */
    void handleOptionsMenu();

    /**
      * Handle settings menu
      *
      * @return nothing
      */
    void handleSettingsMenu();

public:

    /**
      * Resize the GUI of the application
      *
      * @param bPortrait
      * @param bMapWidth
      * @param bMapHeight
      *
      * @return nothing
      */
    void resizeGUI(bool bPortrait, int bMapWidth, int bMapHeight);

    /**
      * Get message box
      *
      * @return CustomMessageBox
      */
    CustomMessageBox* getMessageBox() const;

protected:

    //overload from QWidget
    void changeEvent(QEvent* event);

private:

    /**
     * Start listening for position changes
     *
     * @return nothing
     */
    void startLocationAPI();

    /**
      * Stop location API
      *
      * @return nothing
      */
    void stopLocationAPI();

    /**
      * Get coordinates as text
      *
      * @return QString
      */
    QString getCoordinatesAsText() const;

    /**
      * Resize about widget
      *
      * @return nothing
      */
    void resizeAboutAndLang();

    /**
      * Adjust visibility of GUI components
      *
      * @param bVisible
      *
      * @return nothing
      */
    void setCtrlVisible(bool bVisible);

    /**
      * Control loading
      *
      * @param bStart
      *
      * @return nothing
      */
    void loading(bool bStart);

    /**
      * round
      *
      * @param nNumber
      * @param nDecimalPoints
      *
      * @return qreal
      */
    inline int round(qreal nNumber, unsigned char nDecimalPoints) const
    {
        return qFloor(nNumber * 10 * nDecimalPoints);
    }

    /**
      * get text for wait
      *
      *
      * @return QString
      */
    QString getWaitText() const;

    /**
      * get text for SMS button
      *
      *
      * @return QString
      */
    QString getButtonSMSText() const;

    /**
      * get text for E-mail button
      *
      * @return QString
      */
    QString getButtonEmailText() const;

    /**
      * Get Google Maps URL
      *
      * @param nZoom
      * @param nMapHeight
      * @param nMapWidth
      *
      * @return Map URL
      */
    QString getMapUrl(int nZoom, int nMapWidth,
                      int nMapHeight) const;

    /**
      * Handle Send Button
      *
      * type SMS or E-mail
      *
      * @return nothing
      */
    void handleSendButton(QMessage::Type type);

    /**
      * compose message text
      *
      * type SMS or E-mail
      *
      * @return QString
      */
    QString composeMessageContent(QMessage::Type type) const;

    /**
      * create and show message for location data
      *
      * @return nothing
      */
    void createAndShowMessageLocationData();

    /**
      * create and show message for sent panic msg
      *
      * @return nothing
      */
    void createAndShowMessageSent();

    /**
      * Update slider value and range based on the settings
      *
      * @return nothing
      */
    void updateSlider();

    /**
      * Save coordinates as strings
      *
      *
      * @return nothing
      */
    void coordinatesToStrings(const QString& sCoordinates);

    /**
      * Show a sub view and close all other subvies
      *
      * @return nothing
      */
    void showWidget(QWidget* pWidget);

};

#endif // MAINWIDGET_H
