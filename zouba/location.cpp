#include "location.h"

#include "location_p.h"

#include "ytv.h"

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QDebug>
#include <QXmlStreamAttributes>
#include <QStringRef>

Location::Location( QString x, QString y ) :
  q( new LocationPrivate( x, y ) ),
  manager( new QNetworkAccessManager(this) )
{
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
}

Location::Location( const Location &from ) :
  QObject( 0 ),
  q( new LocationPrivate() ),
  manager( new QNetworkAccessManager(this) )
{
  q->setX( from.x() );
  q->setY( from.y() );
  q->setValid( from.isValid() );
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
}

Location::Location() :
  q( new LocationPrivate() ),
  manager( new QNetworkAccessManager(this) )
{
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
}

Location::~Location()
{
  delete q;
  q=0;
  delete manager;
  manager=0;
}

Location &Location::operator=( const Location &from )
{
  q->setX( from.x() );
  q->setY( from.y() );
  q->setValid( from.isValid() );
  manager = new QNetworkAccessManager(this);
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
  
  return *this;
}

void Location::resolveAddress( QString address )
{
  QUrl fullUrl( ytv );

  fullUrl.addEncodedQueryItem( "key", address.toAscii() );
  fullUrl.addQueryItem( "user", username );
  fullUrl.addQueryItem( "pass", password );

  manager->get( QNetworkRequest( fullUrl ) );
}

void Location::replyFinished( QNetworkReply * reply )
{
  q->parseReply( reply->readAll() );

  if ( q->isValid() ) {
    emit( becomeValid() );
  }
}

QString Location::x() const
{
  return q->x();
}

QString Location::y() const
{
  return q->y();
}

bool Location::isValid() const
{
  return q->isValid();
}
