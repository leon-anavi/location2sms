/*
* ============================================================================
*  Name         : filedownloader.h
*  Part of      : location2sms
*  Description  : download from URL
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

//Standard includes
#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QUrl imageUrl, QObject *parent = 0);

    explicit FileDownloader(QObject *parent = 0);

    virtual ~FileDownloader();

    QByteArray downloadedData() const;

    void downloadUrl(QUrl targetUrl);

    void downloadUrl(QUrl targetUrl, QString sHeader, QByteArray postData);

signals:
        void downloaded();

private slots:

    void fileDownloaded(QNetworkReply* pReply);

private:

    QNetworkAccessManager m_WebCtrl;

    QByteArray m_DownloadedData;

};

#endif // FILEDOWNLOADER_H
