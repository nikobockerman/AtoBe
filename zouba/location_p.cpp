#include "location_p.h"

#include <QXmlStreamReader>
#include <QByteArray>
#include <QDebug>

LocationPrivate::LocationPrivate( QString x, QString y ) :
  m_x(x),
  m_y(y),
  m_valid(true)
{
}

LocationPrivate::LocationPrivate() :
  m_x(0),
  m_y(0),
  m_valid(false)
{
}

void LocationPrivate::parseReply( const QByteArray &reply )
{
  QXmlStreamReader xml( reply );

  while ( !xml.atEnd() ) {
    xml.readNext();
    if ( xml.isStartElement() && xml.name() == "LOC" ) {
      QXmlStreamAttributes attributes( xml.attributes() );
      QStringRef xAttribute( attributes.value("x") );
      QStringRef yAttribute( attributes.value("y") );
      QString newX( xAttribute.toString() );
      QString newY( yAttribute.toString() );

      m_x = newX;
      m_y = newY;
    }
  }

  if ( xml.hasError() ) {
    qDebug() << "xml error";
  } else {
    m_valid = true;
  }
}

void LocationPrivate::setX( QString x )
{
  m_x = x;
}

QString LocationPrivate::x() const
{
  return m_x;
}

void LocationPrivate::setY( QString y )
{
  m_y = y;
}

QString LocationPrivate::y() const
{
  return m_y;
}

void LocationPrivate::setValid( bool valid )
{
  m_valid = valid;
}

bool LocationPrivate::isValid() const
{
  return m_valid;
}
