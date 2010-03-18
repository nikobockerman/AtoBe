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
  QUrl fullUrl( Ytv::Url );

  QStringList a;
  a << q->fromLocation().x() << q->fromLocation().y();
  QStringList b;
  b << q->toLocation().x() << q->toLocation().y();

  fullUrl.addQueryItem( "a", a.join(",") );
  fullUrl.addQueryItem( "b", b.join(",") );
  fullUrl.addQueryItem( "show", QString::number(Ytv::FiveResults) );
  fullUrl.addQueryItem( "walkspeed", QString::number(Ytv::Fast) );
  fullUrl.addQueryItem( "user", Ytv::Username );
  fullUrl.addQueryItem( "pass", Ytv::Password );

  manager->get( QNetworkRequest( fullUrl ) );
}

void Route::replyFinished( QNetworkReply * reply )
{
  QList<RouteData> routeData = q->parseReply( reply->readAll() );

  emit( routeReady( routeData ) );
}

void Route::setFromLocation( const Location &location )
{
  if ( location.isValid() ) {
    q->setFromLocation( location );
    if ( q->toValid() ) {
        getRoute();
    }
  } else {
    Location *locationPtr = qobject_cast<Location*>(sender());
    if ( locationPtr ) {
      q->setFromLocation( *locationPtr );
      if ( q->toValid() ) {
        getRoute();
      }
    } else {
      qDebug() << "locationPtr is zero - cast didn't work";
    }
  }
}

const Location &Route::fromLocation()
{
  return q->fromLocation();
}

void Route::setToLocation( const Location &location )
{
  if ( location.isValid() ) {
    q->setToLocation( location );
    if ( q->fromValid() ) {
      getRoute();
    }
  } else {
    Location *locationPtr = qobject_cast<Location*>(sender());
    if ( locationPtr ) {
      q->setToLocation( *locationPtr );
      if ( q->fromValid() ) {
        getRoute();
      }
    } else {
      qDebug() << "locationPtr is zero; cast failed";
    }
  }
}

const Location &Route::toLocation()
{
  return q->toLocation();
}

void Route::toggleDirection()
{
  Location oldFromLocation = fromLocation();
  setFromLocation( toLocation() );
  setToLocation( oldFromLocation );

  getRoute();
}
