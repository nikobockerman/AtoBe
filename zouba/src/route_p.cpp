#include "route_p.h"
#include "location.h"

#include <QXmlStreamReader>
#include <QDebug>
#include <QList>

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

  QList<RouteData> retVal;
  RouteData routeData;

  QXmlStreamReader xml( reply );

  bool haveLine = false;
  bool haveTime = false;

  bool inLine = false;
  bool inStop = false;
  while ( !xml.atEnd() ) {
    xml.readNext();
    if ( xml.isStartElement() && xml.name() == "LINE" ) {
      QString lineCode( xml.attributes().value("code").toString() );

      routeData.lineCode = parseJORECode( lineCode );
      haveLine = true;

      inLine = true;
    } else
    if ( inLine && xml.name() == "STOP" ) {
      inStop = true;
    } else
    if ( inLine && inStop && xml.name() == "ARRIVAL" ) {
      QString arrivalTime( xml.attributes().value("time").toString() );

      routeData.arrivalTime = arrivalTime.rightJustified(4).insert(2,":");
      haveTime = true;

      inLine = false;
    } else
    if ( xml.isEndElement() && xml.name() == "STOP" ) {
      inStop = false;
      haveTime = false;
    } else
    if ( xml.isEndElement() && xml.name() == "LINE" ) {
      inLine = false;
      haveLine = false;
    }

    if ( haveLine && haveTime ) {
      retVal.append( routeData );

      // only want first STOP per LINE
      haveTime = false;
      haveLine = false;
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
