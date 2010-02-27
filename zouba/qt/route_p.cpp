#include "route_p.h"
#include "location.h"

#include <QXmlStreamReader>
#include <QDebug>

RoutePrivate::RoutePrivate( QObject *parent ) :
    m_fromLocation(0,0),
    m_toLocation(0,0)
{
  Q_UNUSED( parent )
}

RoutePrivate::~RoutePrivate()
{
}

RouteData RoutePrivate::parseReply( const QByteArray &reply )
{
  RouteData retVal;

  QXmlStreamReader xml( reply );

  bool inLine = false;
  bool inStop = false;
  while ( !xml.atEnd() ) {
    xml.readNext();
    if ( xml.isStartElement() && xml.name() == "LINE" ) {
      QString lineCode( xml.attributes().value("code").toString() );

      retVal.lineCode = lineCode;

      inLine = true;
    } else
    if ( inLine && xml.name() == "STOP" ) {
      inStop = true;
    } else
    if ( inLine && inStop && xml.name() == "ARRIVAL" ) {
      QString arrivalTime( xml.attributes().value("time").toString() );

      retVal.arrivalTime = arrivalTime;

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

  return retVal;
}

void RoutePrivate::setFromLocation( Location fromLocation )
{
  m_fromLocation = fromLocation;
}

Location RoutePrivate::fromLocation()
{
  return m_fromLocation;
}

void RoutePrivate::setToLocation( Location toLocation )
{
  m_toLocation = toLocation;
}

Location RoutePrivate::toLocation()

{
  return m_toLocation;
}
