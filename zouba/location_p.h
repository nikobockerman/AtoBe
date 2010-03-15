#ifndef LOCATION_P_H
#define LOCATION_P_H

#include <QObject>
#include <QString>
#include <QByteArray>

class LocationPrivate : public QObject
{
    Q_OBJECT

public:
  QString m_x;
  QString m_y;
  bool    m_valid;
  LocationPrivate( QString x, QString y );

  LocationPrivate();
  virtual ~LocationPrivate();

  void setX( uint x );
  void setX( QString x );
  QString x() const;

  void setY( uint y );
  void setY( QString y );
  QString y() const;

  void setValid( bool valid );
  bool isValid() const;

  void parseReply( const QByteArray &reply );

};

#endif // LOCATION_P_H

