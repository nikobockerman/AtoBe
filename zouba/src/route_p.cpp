#include "route_p.h"
#include "location.h"

#include <QXmlStreamReader>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QStringList>
#ifdef Q_WS_MAEMO_5
#include <QMaemo5InformationBox>
#endif

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
  LegData legData;

  QXmlStreamReader xml( reply );

  QHash<QString, bool> in;
  QHash<QString, bool> have;

  QStringList haveKeys;
  QStringList inKeys;

  haveKeys
    << "LINE"
    << "TIME"
    << "TRIP"
    << "DEPARTURE"
    << "ARRIVAL"
    ;

  inKeys
    << "ROUTE"
    << "LINE"
    << "STOP"
    << "WALK"
    << "POINT"
    ;

  foreach( QString key, haveKeys ) {
    have[ key ] = false;
  }

  foreach( QString key, inKeys ) {
    in[ key ] = false;
  }

  while ( !xml.atEnd() ) {
    xml.readNext();

    QString xmlName = xml.name().toString();

    if ( xml.isStartElement() ) {
      if ( inKeys.contains( xmlName ) ) {
        in[ xmlName ] = true;
        //qDebug() << "in[" << xmlName << "] = true";
      }

      if ( xmlName == "ROUTE" ) {
        foreach( QString key, haveKeys ) {
          have[ key ] = false;
        }
      }

      if ( xmlName == "WALK" ) {
        legData.m_how = "WALK";
        have[ "DEPARTURE" ] = false;
        have[ "ARRIVAL" ]   = false;
        have[ "LENGTH" ]    = false;
      }

      if ( xmlName == "LINE" ) {
        legData.m_how = "LINE";
        QString lineCode( xml.attributes().value("code").toString() );
        legData.m_lineCode = parseJORECode( lineCode );
        have[ "DEPARTURE" ] = false;
        have[ "ARRIVAL" ]   = false;
        have[ "LENGTH" ]    = false;
      }
    }

    if ( xml.isEndElement() ) {
      if ( inKeys.contains( xmlName ) ) {
        in[ xmlName ] = false;
        //qDebug() << "in[" << xmlName << "] = false";
      }

      if ( xmlName == "ROUTE" ) {
        retVal.append( routeData );
        routeData.clear();
      }

      if ( xmlName == "WALK" || xmlName == "LINE" ) {
        routeData.m_legData.append( legData );
        legData.clear();
        have[ "LENGTH" ] = false;
      }
    }

    if ( !have[ "ARRIVAL" ] && ( in[ "WALK" ] || in[ "LINE" ] ) && ( in[ "STOP" ] || in[ "POINT" ] ) && xml.isStartElement() && xmlName == "ARRIVAL" ) {
      QString arrivalTime( xml.attributes().value("time").toString() );
      legData.m_arrivalTime = arrivalTime.rightJustified(4).insert(2,":");

      // don't set have[ "ARRIVAL" ] since we want the last one of many STOPs
    }

    if ( !have[ "DEPARTURE" ] && in[ "LINE" ] && in[ "STOP" ] && xml.isStartElement() && xmlName == "DEPARTURE" ) {
      QString departureTime( xml.attributes().value("time").toString() );
      legData.m_departureTime = departureTime.rightJustified(4).insert(2,":");

      have[ "DEPARTURE" ] = true;
    }

    if ( !have[ "DEPARTURE" ] && in[ "WALK" ] && ( in[ "POINT" ] || in[ "STOP" ] ) && xml.isStartElement() && xmlName == "DEPARTURE" ) {
      QString departureTime( xml.attributes().value("time").toString() );
      legData.m_departureTime = departureTime.rightJustified(4).insert(2,":");

      have[ "DEPARTURE" ] = true;
    }

    if ( !have[ "LENGTH" ] && ( in[ "WALK" ] || in[ "LINE" ] ) && xml.isStartElement() && xmlName == "LENGTH" ) {
      legData.m_tripTime     = xml.attributes().value("time").toString();
      legData.m_tripDistance = xml.attributes().value("dist").toString();

      have[ "LENGTH" ] = true;
    }

    if ( !have[ "TRIP" ] && in[ "ROUTE" ] && xml.isStartElement() && xmlName == "LENGTH" ) {
      routeData.m_tripTime     = xml.attributes().value("time").toString();
      routeData.m_tripDistance = xml.attributes().value("dist").toString();

      have[ "TRIP" ] = true;
    }

    if ( !have[ "LINE" ] && in[ "ROUTE" ] && xml.isStartElement() && xmlName == "LINE" ) {
      QString lineCode( xml.attributes().value("code").toString() );

      routeData.m_lineCode = parseJORECode( lineCode );
      have[ "LINE" ] = true;
    }

    if ( !have[ "TIME" ] && in[ "ROUTE" ] && in[ "LINE" ] && in[ "STOP" ] && xmlName == "DEPARTURE" ) {
      QString departureTime( xml.attributes().value("time").toString() );

      routeData.m_departureTime = departureTime.rightJustified(4).insert(2,":");
      have[ "TIME" ] = true;
    }

  }

  if ( xml.hasError() ) {
    qDebug() << "xml error:" << xml.errorString();
  }

  if ( retVal.isEmpty() ) {
    qDebug() << "no routes found";
#ifdef Q_WS_MAEMO_5
    QMaemo5InformationBox::information( 0, "no routes found" );
#endif
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
