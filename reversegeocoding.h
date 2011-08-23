#ifndef REVERSEGEOCODING_H
#define REVERSEGEOCODING_H

#include <QObject>
#include <QString>

#include "filedownloader.h"

class ReverseGeocoding : public QObject
{
    Q_OBJECT

private:

    FileDownloader* m_pReverseGeoCoder;

    QString m_sAddress;

public:
    explicit ReverseGeocoding(QObject *parent = 0);

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
