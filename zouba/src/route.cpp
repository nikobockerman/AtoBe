#include "route_p.h"
#include "route.h"

#include "routedata.h"
#include "logic/location.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QXmlStreamReader>
#include <QWidget>

#include "logic/ytv.h"

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
  fullUrl.addQueryItem( "show", QString::number(Ytv::ShowFiveResults) );
  fullUrl.addQueryItem( "walkspeed", QString::number(Ytv::WalkSpeedFast) );
  fullUrl.addQueryItem( "optimize", QString::number(Ytv::OptimizeDefault) );
  fullUrl.addQueryItem( "user", Ytv::Username );
  fullUrl.addQueryItem( "pass", Ytv::Password );

  manager->get( QNetworkRequest( fullUrl ) );
  qDebug() << "getting url" << fullUrl.toEncoded();
  qDebug() << "waiting for reply from Ytv";
  emit( busy( true ) );
}

void Route::replyFinished( QNetworkReply * reply )
{
  qDebug() << "have reply from Ytv";
  QList<RouteData> routeData = q->parseReply( reply->readAll() );

  emit( routeReady( routeData ) );
  emit( busy( false ) );
}

void Route::setFromLocation( Location *location )
{
  qDebug() << "setting new From location (" << location->label() << ")";
  this->setLocation(location, true);
}

void Route::searchRoute()
{
    if (q->fromValid() && q->toValid())
    {
        qDebug() << "From and To addresses are valid.";
        getRoute();
    }
}

Location *Route::fromLocation() const
{
  return q->fromLocation();
}

void Route::setLocation(Location *location, bool from)
{
  if (location != 0)
  {
    if (location->isValid())
    {
      qDebug() << "Location is valid";
      if (from) q->setFromLocation( location );
      else q->setToLocation(location);
    } else {
      qDebug() << "Location is not valid. Try again or fix address";
      qDebug() << "Location = " << location;
      //location->resolveAddress(location->address());
    }
  } else {
    qDebug() << "ERROR:Null location pointer given.";
  }
}

void Route::setToLocation( Location *location )
{
  qDebug() << "setting new To location (" << location->label() << ")";
  this->setLocation(location, false);
}

Location *Route::toLocation() const
{
  return q->toLocation();
}
