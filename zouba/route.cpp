#include "route_p.h"
#include "route.h"

#include "routedata.h"
#include "location.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QXmlStreamReader>

#include "ytv.h"

Route::Route() :
  q( new RoutePrivate( this ) ),
  manager( new QNetworkAccessManager(this) )
{
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
}

Route::~Route()
{
  delete manager;
  manager = 0;
}

void Route::getRoute()
{
  qDebug() << "getting route from Ytv";

  QUrl fullUrl( Ytv::Url );

  QStringList a;
  a << q->fromLocation()->x() << q->fromLocation()->y();
  QStringList b;
  b << q->toLocation()->x() << q->toLocation()->y();

  fullUrl.addQueryItem( "a", a.join(",") );
  fullUrl.addQueryItem( "b", b.join(",") );
  fullUrl.addQueryItem( "show", QString::number(Ytv::FiveResults) );
  fullUrl.addQueryItem( "walkspeed", QString::number(Ytv::Fast) );
  fullUrl.addQueryItem( "user", Ytv::Username );
  fullUrl.addQueryItem( "pass", Ytv::Password );

  manager->get( QNetworkRequest( fullUrl ) );
  qDebug() << "waiting for reply from Ytv";
}

void Route::replyFinished( QNetworkReply * reply )
{
  qDebug() << "have reply from Ytv";
  QList<RouteData> routeData = q->parseReply( reply->readAll() );

  emit( routeReady( routeData ) );
}

void Route::setFromLocation( Location *location )
{
  qDebug() << "setting new From location";

  if ( location && location->isValid() ) {
    qDebug() << "From is valid";
    q->setFromLocation( location );
    if ( q->toValid() ) {
      qDebug() << "To is also valid";
      getRoute();
    } else {
      qDebug() << "To not valid - waiting";
    }
  } else {
    qDebug() << "From is not valid";
    qDebug() << "getting From from signal sender";
    location = qobject_cast<Location*>(sender());
    if ( location ) {
      q->setFromLocation( location );
      if ( q->toValid() ) {
        qDebug() << "To is also valid";
        getRoute();
      } else {
        qDebug() << "To not valid - waiting";
      }
    } else {
      qDebug() << "location is zero - cast didn't work";
    }
  }
}

Location *Route::fromLocation() const
{
  return q->fromLocation();
}

void Route::setToLocation( Location *location )
{
  qDebug() << "setting new To location";

  if ( location && location->isValid() ) {
    qDebug() << "To is valid";
    q->setToLocation( location );
    if ( q->fromValid() ) {
      qDebug() << "From is also valid";
      getRoute();
    } else {
      qDebug() << "From not valid - waiting";
    }
  } else {
    qDebug() << "To is not valid";
    qDebug() << "getting To from signal sender";
    Location *location = qobject_cast<Location*>(sender());
    if ( location ) {
      q->setToLocation( location );
      if ( q->fromValid() ) {
        qDebug() << "From is also valid";
        getRoute();
      } else {
        qDebug() << "From not valid - waiting";
      }
    } else {
      qDebug() << "location is zero; cast failed";
    }
  }
}

Location *Route::toLocation() const
{
  return q->toLocation();
}
