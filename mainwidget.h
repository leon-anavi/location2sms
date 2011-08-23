#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QGraphicsView>
#include <QTimeLine>
#include <math.h>

//Qt mobility
#include <qgeopositioninfo.h>
#include <QGeoPositionInfoSource>
#include <QMessageService>

//Qt WebKit
#include <QWebView>

#include "aboutwidget.h"
#include "menuwidget.h"
#include "reversegeocoding.h"
#include "busyindicator.h"

// QtMobility namespace
QTM_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

private:

    QGeoPositionInfoSource* m_pLocationInfo;

    QGeoPositionInfoSource* m_pLocationInfoSat;

    QMessageService* m_pMessageManager;

    bool m_bIsPositionFound;

    qreal m_nLatitude;

    qreal m_nLongitude;

    QVBoxLayout* m_pLayout;

    //main menu
    MenuWidget* m_pMainMenu;

    //about widget
    AboutWidget* m_pAboutWidget;

    QLabel* m_pLabelCoordinates;

    QPushButton* m_pButtonSendMessage;

    QWebView* m_pWebView;

    QSlider* m_pMapZoomSlider;

    ReverseGeocoding* m_pReverseGeoCoder;

    bool m_bPortrait;

    int m_nMapWidth;

    int m_nMapHeight;

    BusyIndicator* m_pBusyIndicator;

    QTimeLine* m_pTimeLine;

    QGraphicsView* m_pLoadingView;

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
      * Handle Send Button
      *
      * @return nothing
      */
    void handleSendButton();

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
      * Show or hide help (about) view
      *
      * @return nothing
      */
    void handleAbout();

    /**
      * Rotate spinner
      *
      * @param nValue
      *
      * @return noting
      */
    void rotateSpinner(int nValue);

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

private:

    /**
     * Start listening for position changes
     *
     * @return nothing
     */
    void startLocationAPI();

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
    void resizeAbout();

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
    inline qreal round(qreal nNumber, unsigned char nDecimalPoints)
    {
        return floor(nNumber * pow(10., nDecimalPoints) + .5) / pow(10., nDecimalPoints);
    }

};

#endif // MAINWIDGET_H
