#include <stdio.h>
#include "location_p.h"

#include <QXmlStreamReader>
#include <QByteArray>
#include <QDebug>

LocationPrivate::LocationPrivate( const QString &x, const QString &y, const QString &label ) :
  m_label(label),
  m_address(),
  m_x(x),
  m_y(y),
  m_valid(true)
{
}

LocationPrivate::LocationPrivate( const QString &label ) :
  m_label(label),
  m_address(),
  m_x(0),
  m_y(0),
  m_valid(false)
{
}

LocationPrivate::~LocationPrivate()
{
}

void LocationPrivate::parseReply( const QByteArray &reply )
{
  qDebug() << "parsing";
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
    m_valid = false;
  } else {
    qDebug() << "(" << m_x << "," << m_y << ")";
    if ( m_x.isEmpty() ||  m_y.isEmpty() ) {
      qDebug() << "is NOT valid";
      m_valid = false;
    } else {
      qDebug() << "is now valid";
      m_valid = true;
    }
  }
}

void LocationPrivate::setLabel( const QString &label)
{
  m_label = label;
}

QString LocationPrivate::label() const
{
  return m_label;
}

void LocationPrivate::setAddress( const QString &address)
{
  m_address = address;
}

QString LocationPrivate::address() const
{
  return m_address;
}

void LocationPrivate::setX( uint x )
{
  m_x = QString( "%1" ).arg( x );
}

void LocationPrivate::setX( const QString &x )
{
  m_x = x;
}

QString LocationPrivate::x() const
{
  return m_x;
}

void LocationPrivate::setY( uint y )
{
  m_y = QString( "%1" ).arg( y );
}

void LocationPrivate::setY( const QString &y )
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
