/*
* ============================================================================
*  Name         : reversegeocoding.h
*  Part of      : location2sms
*  Description  : retrieve address from coordinates using Google Maps API
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

#ifndef REVERSEGEOCODING_H
#define REVERSEGEOCODING_H

//Standard includes
#include <QObject>
#include <QString>

//Project specific includes
#include "filedownloader.h"

class ReverseGeocoding : public QObject
{
    Q_OBJECT

private:

    FileDownloader* m_pReverseGeoCoder;

    QString m_sAddress;

public:
    explicit ReverseGeocoding(QObject *parent = 0);

    virtual ~ReverseGeocoding();

    /**
      * Reverse geocoding
      *
      * @param nLatitude
      * @param nLongitude
      *
      * @return nothing
      */
    void requestAddressFromCoordinates(qreal nLatitude, qreal nLongitude);

    /**
      * Get address
      *
      * @return QString
      */
    QString getAddress() const;

signals:

    void addressRetrieved();

public slots:

private slots:

    void parseAddress();

};

#endif // REVERSEGEOCODING_H
