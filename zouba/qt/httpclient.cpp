#include "httpclient.h"

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
  QXmlStreamReader xml( reply->readAll() );

  bool inLine = false;
  bool inStop = false;
  while ( !xml.atEnd() ) {
    xml.readNext();
    //qDebug() << xml.name();
    if ( xml.isStartElement() && xml.name() == "LINE" ) {
      QString lineCode( xml.attributes().value("code").toString() );

      qDebug() << "line code" << lineCode;
      ui->BusNoDisplay->setText( lineCode );

      inLine = true;
    } else
    if ( inLine && xml.name() == "STOP" ) {
      inStop = true;
    } else
    if ( inLine && inStop && xml.name() == "ARRIVAL" ) {
      QString arrivalTime( xml.attributes().value("time").toString() );

      qDebug() << "arrival time" << arrivalTime;
      ui->TimeDisplay->setText( arrivalTime );

      inLine = false;
    } else
    if ( xml.isEndElement() && xml.name() == "STOP" ) {
      inStop = false;
    } else
    if ( xml.isEndElement() && xml.name() == "LINE" ) {
      inLine = false;
    }
  }

  if ( xml.hasError() ) {
    qDebug() << "xml error";
  }
}
