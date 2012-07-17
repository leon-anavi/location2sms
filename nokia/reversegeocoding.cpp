/*
* ============================================================================
*  Name         : reversegeocoding.cpp
*  Part of      : location2sms
*  Description  : retrieve address from coordinates using Google Maps API
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

//Project specific includes
#include "reversegeocoding.h"

//Standard includes
#include <QDomDocument>
#include <QDomNodeList>
#include <QDomElement>
#include <QTextStream>

ReverseGeocoding::ReverseGeocoding(QObject *parent) :
    QObject(parent),
    m_pReverseGeoCoder(NULL)
{
    m_pReverseGeoCoder = new FileDownloader(this);

    connect(m_pReverseGeoCoder, SIGNAL(downloaded()), SLOT(parseAddress()));
}
//------------------------------------------------------------------------------

ReverseGeocoding::~ReverseGeocoding()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void ReverseGeocoding::requestAddressFromCoordinates(QString sLatitude,
                                                        QString sLongitude)
{

    QString sUrl = QString("http://maps.googleapis.com/maps/api/geocode/"
                           "xml?latlng=%1,%2&sensor=false").
                                            arg(sLatitude).arg(sLongitude);
    m_pReverseGeoCoder->downloadUrl(sUrl);
}
//------------------------------------------------------------------------------

void ReverseGeocoding::parseAddress()
{
    //QTextStream will detect the UTF-16 or the UTF-32 BOM (Byte Order Mark)
    //and switch to the appropriate UTF codec when reading.
    QTextStream downloadedStream(m_pReverseGeoCoder->downloadedData());
    downloadedStream.setCodec("UTF-8");

    QDomDocument document;   
    if (false == document.setContent(downloadedStream.readAll()))
    {
        m_sAddress = "";
        return;
    }

    QDomElement mElement = document.documentElement().
            firstChildElement("result").firstChildElement("formatted_address");

    m_sAddress = mElement.text();

    //emit a signal
    emit addressRetrieved();
}
//------------------------------------------------------------------------------

QString ReverseGeocoding::getAddress() const
{
    return m_sAddress;
}
//------------------------------------------------------------------------------
