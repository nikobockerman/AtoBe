#ifndef LOCATION_P_H
#define LOCATION_P_H

#include <QObject>
#include <QString>
#include <QByteArray>

class LocationPrivate : public QObject
{
    Q_OBJECT

public:
  QString m_label;
  QString m_address;
  QString m_x;
  QString m_y;
  bool    m_valid;
  LocationPrivate( const QString &x, const QString &y, const QString &label );

  LocationPrivate( const QString &label );
  virtual ~LocationPrivate();

  void setX( uint x );
  void setX( const QString &x );
  QString x() const;

  void setY( uint y );
  void setY( const QString &y );
  QString y() const;

  void setAddress( const QString &address );
  QString address() const;

  void setLabel( const QString &label );
  QString label() const;

  void setValid( bool valid );
  bool isValid() const;

  void parseReply( const QByteArray &reply );

};

#endif // LOCATION_P_H

