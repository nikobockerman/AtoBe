#include "route_p.h"
#include "location.h"

#include <QXmlStreamReader>
#include <QDebug>
#include <QList>
#include <QFile>

RoutePrivate::RoutePrivate( QObject *parent ) :
    m_fromValid(false),
    m_toValid(false),
    m_fromLocation(0),
    m_toLocation(0)
{
  Q_UNUSED( parent )
}

RoutePrivate::~RoutePrivate()
{
}

QList<RouteData> RoutePrivate::parseReply( const QByteArray &reply )
{
  qDebug() << "parsing route";
  QFile file( "/home/user/route.txt" );
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << reply;
    file.close();
  } else {
    qDebug() << "Could not open /home/user/route.txt";
  }


  QList<RouteData> retVal;
  RouteData routeData;

  QXmlStreamReader xml( reply );

  QHash<QString, bool> in;
  QHash<QString, bool> have;

  have[ "LINE" ] = false;
  have[ "TIME" ] = false;

  in[ "ROUTE" ] = false;
  in[ "LINE" ]  = false;
  in[ "STOP" ]  = false;

  while ( !xml.atEnd() ) {
    xml.readNext();
    if ( xml.isStartElement() ) {
        in[ xml.name().toString() ] = true;

        if ( xml.name() == "ROUTE" ) {
          have[ "TIME" ] = false;
          have[ "LINE" ] = false;
        }
    }

    if ( xml.isEndElement() ) {
        in[ xml.name().toString() ] = false;
    }

    if ( !have[ "LINE" ] && in[ "ROUTE" ] && xml.isStartElement() && xml.name() == "LINE" ) {
      QString lineCode( xml.attributes().value("code").toString() );

      routeData.lineCode = parseJORECode( lineCode );
      have[ "LINE" ] = true;

      if ( have[ "LINE" ] && have[ "TIME" ] ) {
        retVal.append( routeData );
      }
    }

    if ( !have[ "TIME" ] && in[ "ROUTE" ] && in[ "LINE" ] && in[ "STOP" ] && xml.name() == "ARRIVAL" ) {
      QString arrivalTime( xml.attributes().value("time").toString() );

      routeData.arrivalTime = arrivalTime.rightJustified(4).insert(2,":");
      have[ "TIME" ] = true;

      if ( have[ "LINE" ] && have[ "TIME" ] ) {
        retVal.append( routeData );
      }
    }

  }

  if ( xml.hasError() ) {
    qDebug() << "xml error:" << xml.errorString();
  }

  if ( retVal.isEmpty() ) {
    qDebug() << "no routes found";
  }

  return retVal;
}

void RoutePrivate::setFromLocation( Location *location )
{
  m_fromLocation = location;
  m_fromValid = true;
}

Location *RoutePrivate::fromLocation() const
{
  return m_fromLocation;
}

void RoutePrivate::setToLocation( Location *toLocation )
{
  m_toLocation = toLocation;
  m_toValid = true;
}

QString RoutePrivate::parseJORECode( const QString &joreCode ) const
{
  QString retVal;

  QString areaTransportTypeCode( joreCode.mid(0,1) );
  QString lineCode( joreCode.mid(1,3) );
  QString letterVariant( joreCode.mid(4,1) );
  QString letterNumberVariant( joreCode.mid(5,1) );
  QString direction( joreCode.mid(6,1) );

  lineCode.setNum( lineCode.toInt() );

  retVal = lineCode;

  if ( letterVariant != " " ) {
    retVal += letterVariant;
  }

  return retVal;
}

Location *RoutePrivate::toLocation() const
{
  return m_toLocation;
}

bool RoutePrivate::fromValid()
{
  return m_fromValid;
}

bool RoutePrivate::toValid()
{
  return m_toValid;
}
