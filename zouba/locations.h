#ifndef LOCATIONS_H
#define LOCATIONS_H

#include "location.h"

#include <QHash>
#include <QString>

class Locations
{
public:
  Locations();
  ~Locations();

  bool addLocation( Location *location );

  Location *location( const QString &label );

private:
  static QHash<QString,Location *> locationHash;
};
#endif // LOCATIONS_H
