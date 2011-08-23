#include "reversegeocoding.h"

#include <QDomDocument>
#include <QDomNodeList>
#include <QDomElement>
#include <QDebug>


ReverseGeocoding::ReverseGeocoding(QObject *parent) :
    QObject(parent),
    m_pReverseGeoCoder(NULL)
{
    m_pReverseGeoCoder = new FileDownloader(this);

    connect(m_pReverseGeoCoder, SIGNAL(downloaded()), SLOT(parseAddress()));
}
//------------------------------------------------------------------------------

void ReverseGeocoding::requestAddressFromCoordinates(qreal nLatitude,
                                                        qreal nLongitude)
{

    QString sUrl = QString("http://maps.googleapis.com/maps/api/geocode/"
                           "xml?latlng=%1,%2&sensor=false").
                                            arg(nLatitude).arg(nLongitude);
    qDebug() << "Searching for address via: " << sUrl;
    QUrl locationUrl(sUrl);
    m_pReverseGeoCoder->downloadUrl(sUrl);
}
//------------------------------------------------------------------------------

void ReverseGeocoding::parseAddress()
{
    qDebug() << "Parsing the address...";
    QString sAddrAsXml(m_pReverseGeoCoder->downloadedData());

    //TODO: parse XML
    QDomDocument document;
    if (false == document.setContent(sAddrAsXml))
    {
        qDebug() << "Bad input data.";
        m_sAddress = "";
        return;
    }

    QDomElement mElement = document.documentElement().
            firstChildElement("result").firstChildElement("formatted_address");

    m_sAddress = mElement.text();
    qDebug() <<  "The address is: '" << m_sAddress << "'";

    //emit a signal
    emit addressRetrieved();
}
//------------------------------------------------------------------------------

QString ReverseGeocoding::getAddress() const
{
    return m_sAddress;
}
//------------------------------------------------------------------------------
