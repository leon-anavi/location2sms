/*
* ============================================================================
*  Name         : filedownloader.cpp
*  Part of      : location2sms
*  Description  : download from URL
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

//Project specific includes
#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl imageUrl, QObject *parent) :
    QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)),
                SLOT(fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
}
//------------------------------------------------------------------------------

FileDownloader::FileDownloader(QObject *parent) :
    QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)),
                SLOT(fileDownloaded(QNetworkReply*)));
}
//------------------------------------------------------------------------------

FileDownloader::~FileDownloader()
{
    //Nothing to do
}
//------------------------------------------------------------------------------

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    emit downloaded();
}
//------------------------------------------------------------------------------

QByteArray FileDownloader::downloadedData() const
{
    return m_DownloadedData;
}
//------------------------------------------------------------------------------

void FileDownloader::downloadUrl(QUrl targetUrl)
{
    QNetworkRequest request(targetUrl);
    m_WebCtrl.get(request);

}
//------------------------------------------------------------------------------

void FileDownloader::downloadUrl(QUrl targetUrl,
                                 QString sHeader,
                                 QByteArray postData)
{
    QNetworkRequest request(targetUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, sHeader);
    m_WebCtrl.post(request, postData);
}
//------------------------------------------------------------------------------

