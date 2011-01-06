#include <stdio.h>
#include "location_p.h"

#include <QXmlStreamReader>
#include <QByteArray>
#include <QDebug>
#include <QMaemo5InformationBox>

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
  m_x(QString()),
  m_y(QString()),
  m_valid(false)
{
}

LocationPrivate::~LocationPrivate()
{
  m_label="deleted";
  m_address="";
  m_x="";
  m_y="";
  m_valid=false;
}

void LocationPrivate::parseReply( const QByteArray &reply )
{
  qDebug() << "parsing";
  QXmlStreamReader xml( reply );
  bool responseHasError = false;

  while ( !xml.atEnd() ) {
    xml.readNext();

    if ( xml.isStartElement() ) {
      QString xmlName( xml.name().toString() );

      if ( xmlName == "LOC" ) {
        QXmlStreamAttributes attributes( xml.attributes() );
        QStringRef xAttribute( attributes.value("x") );
        QStringRef yAttribute( attributes.value("y") );
        QString newX( xAttribute.toString() );
        QString newY( yAttribute.toString() );

        m_x = newX;
        m_y = newY;
      }

      if ( xmlName == "ERROR" ) {
        responseHasError = true;
      }

    }
  }

  if ( xml.hasError() || responseHasError ) {
    QMaemo5InformationBox::information( 0, "address resolution error - please check address" );
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
