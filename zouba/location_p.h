#ifndef LOCATION_P_H
#define LOCATION_P_H

#include <QObject>
#include <QString>
#include <QByteArray>

class LocationPrivate : public QObject
{
    Q_OBJECT

public:
  LocationPrivate( QString x, QString y );

  LocationPrivate();

  void setX( QString x );
  QString x() const;

  void setY( QString y );
  QString y() const;

  void setValid( bool valid );
  bool isValid() const;

  void parseReply( const QByteArray &reply );

private:
  QString m_x;
  QString m_y;
  bool    m_valid;
};

#endif // LOCATION_P_H

