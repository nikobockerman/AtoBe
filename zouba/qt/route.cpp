#include "route_p.h"
#include "route.h"

#include "routedata.h"
#include "location.h"

#include "ui_zouba.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QXmlStreamReader>

namespace {
  QUrl ytv( "http://api.reittiopas.fi/public-ytv/fi/api/" );
  QString username( "zouba" );
  QString password( "caf9r3ee" );

  QString homeKey( "taivaanvuohentie%207%2Chelsinki" );
  QString workKey( "it%E4merenkatu%2011%2Chelsinki" );

}
  
Route::Route( Ui::MainWindow *ui ) :
  q( new RoutePrivate( this ) ),
  manager( new QNetworkAccessManager(this) ),
  ui( ui )
{
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
}

Route::~Route()
{
  delete manager;
  manager = 0;
}

void Route::get()
{
  QUrl fullUrl( ytv );

  QStringList a;
  a << q->fromLocation().x << q->fromLocation().y;
  QStringList b;
  b << q->toLocation().x << q->toLocation().y;

  fullUrl.addQueryItem( "a", a.join(",") );
  fullUrl.addQueryItem( "b", b.join(",") );
  fullUrl.addQueryItem( "user", username );
  fullUrl.addQueryItem( "pass", password );

  manager->get( QNetworkRequest( fullUrl ) );
}

void Route::replyFinished( QNetworkReply * reply )
{
  RouteData routeData = q->parseReply( reply->readAll() );

  ui->BusNoDisplay->setText( routeData.lineCode );
  ui->TimeDisplay->setText( routeData.arrivalTime );
}

void Route::setFromLocation( Location fromLocation )
{
  q->setFromLocation( fromLocation );
}

Location Route::fromLocation()
{
  return q->fromLocation();
}

void Route::setToLocation( Location toLocation )
{
  q->setToLocation( toLocation );
}

Location Route::toLocation()
{
  return q->toLocation();
}

