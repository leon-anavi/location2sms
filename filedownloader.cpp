#include "filedownloader.h"

#include <QDebug>

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

    qDebug() << "FileDownloader created";
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
