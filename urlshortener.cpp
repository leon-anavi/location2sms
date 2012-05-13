/*
* ============================================================================
*  Name         : urlshortener.cpp
*  Part of      : location2sms
*  Description  : retrieve short URL using is.gd
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

//Project specific includes
#include "urlshortener.h"

//Standard includes
#include <QTextStream>

UrlShortener::UrlShortener(QObject *parent) :
    QObject(parent),
    m_pDownloader(NULL)
{
    m_pDownloader = new FileDownloader(this);

    connect(m_pDownloader, SIGNAL(downloaded()), SLOT(parseResponse()));
}
//------------------------------------------------------------------------------

UrlShortener::~UrlShortener()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void UrlShortener::requestShortUrl(QString sURL)
{
    //Obtain short URL
    QUrl req = QUrl( "http://is.gd/create.php");
    req.addQueryItem("format", "simple");
    req.addQueryItem("longurl", sURL);
    m_pDownloader->downloadUrl(req);
}
//------------------------------------------------------------------------------

void UrlShortener::parseResponse()
{
    QTextStream downloadedStream(m_pDownloader->downloadedData());

    m_sShortUrl = downloadedStream.readAll();

    //emit a signal
    emit shortUrlRetrieved();
}
//------------------------------------------------------------------------------

QString UrlShortener::getShortUrl() const
{
    return m_sShortUrl;
}
//------------------------------------------------------------------------------
