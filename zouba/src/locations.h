#ifndef LOCATIONS_H
#define LOCATIONS_H

#include "location.h"

#include <QHash>
#include <QString>
#include <QObject>

class Locations: public QObject
{
  Q_OBJECT

public:
  Locations();
  ~Locations();

  static Locations *instance();
  bool addLocation( Location *location );

  Location *location( const QString &label );

public Q_SLOTS:
  void saveLocation();

private:
  void restoreLocations();
  static QHash<QString,Location *> locationHash;
  static bool initialised;

  void saveLocation( Location *location );
};
#endif // LOCATIONS_H
