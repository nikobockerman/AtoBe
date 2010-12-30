#include "ytv.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QNetworkRequest>

QNetworkReply* Ytv::searchAddress(const QString &address)
{
    qDebug() << "Searching for address (" << address << ")";

    QUrl fullUrl(Url);

    fullUrl.addEncodedQueryItem( "key", address.toAscii().toPercentEncoding() );
    fullUrl.addQueryItem( "user", Username );
    fullUrl.addQueryItem( "pass", Password );

    qDebug() << "The query url: " << fullUrl.toString();

    return manager.get(QNetworkRequest(fullUrl));
};
