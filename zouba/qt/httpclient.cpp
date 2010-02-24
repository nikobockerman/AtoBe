#include "httpclient_p.h"
#include "httpclient.h"

#include "routedata.h"

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

  QString workX( "2551042" );
  QString workY( "6672829" );
  QString homeX( "2549183" );
  QString homeY( "6672570" );
}
  
HttpClient::HttpClient( Ui::MainWindow *ui ) :
  q( new HttpClientPrivate( this ) ),
  manager( new QNetworkAccessManager(this) ),
  ui( ui )
{
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
}

HttpClient::~HttpClient()
{
  delete manager;
  manager = 0;
}

void HttpClient::get()
{
  QUrl fullUrl( ytv );

  QStringList a;
  a << workX << workY;
  QStringList b;
  b << homeX << homeY;

  fullUrl.addQueryItem( "a", a.join(",") );
  fullUrl.addQueryItem( "b", b.join(",") );
  fullUrl.addQueryItem( "user", username );
  fullUrl.addQueryItem( "pass", password );

  manager->get( QNetworkRequest( fullUrl ) );
}

void HttpClient::replyFinished( QNetworkReply * reply )
{
  RouteData routeData = q->parseReply( reply->readAll() );

  ui->BusNoDisplay->setText( routeData.lineCode );
  ui->TimeDisplay->setText( routeData.arrivalTime );
}
