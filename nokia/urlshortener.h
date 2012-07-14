/*
* ============================================================================
*  Name         : urlshortener.h
*  Part of      : location2sms
*  Description  : retrieve short URL using is.gd
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

#ifndef URLSHORTENER_H
#define URLSHORTENER_H

//Standard includes
#include <QObject>
#include <QString>

//Project specific includes
#include "filedownloader.h"

class UrlShortener : public QObject
{
    Q_OBJECT

private:

    FileDownloader* m_pDownloader;

    QString m_sShortUrl;

public:

    explicit UrlShortener(QObject *parent = 0);

    virtual ~UrlShortener();

    /**
      * Request short URL from Google API
      *
      * @param sURL
      *
      * @return nothing
      */
    void requestShortUrl(QString sURL);

    /**
      * Get address
      *
      * @return QString
      */
    QString getShortUrl() const;

signals:

    void shortUrlRetrieved();

private slots:

    void parseResponse();

};

#endif // URLSHORTENER_H
