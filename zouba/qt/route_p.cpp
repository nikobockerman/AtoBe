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

      retVal.lineCode = parseJORECode( lineCode );

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

QString RoutePrivate::parseJORECode( const QString &joreCode ) const
{
    QString areaTransportTypeCode( joreCode.mid(0,1) );
    QString lineCode( joreCode.mid(1,3) );
    QString letterVariant( joreCode.mid(4,1) );
    QString letterNumberVariant( joreCode.mid(5,1) );
    QString direction( joreCode.mid(6,1) );

    lineCode.setNum( lineCode.toInt() );
    
    return lineCode+letterVariant;
}

Location RoutePrivate::toLocation()
{
  return m_toLocation;
}
