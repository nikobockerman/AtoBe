#ifndef LOCATION_H
#define LOCATION_H

#include "location_p.h"

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Location : public QObject
{
    Q_OBJECT

public:
  Location( QString x, QString y );
  Location( const Location &from );
  Location &operator=( const Location &from );
  Location();

  ~Location();

  QString x() const;

  QString y() const;

  bool isValid() const;

public Q_SLOTS:
  void resolveAddress( QString address );

Q_SIGNALS:
  void becomeValid();

private Q_SLOTS:
  void replyFinished( QNetworkReply * reply );

private:
  LocationPrivate *q;
  QNetworkAccessManager *manager;
};

#endif // LOCATION_H
