#include "locations.h"

#include <QDebug>

QHash<QString,Location *> Locations::locationHash;

Locations::Locations()
{
}

Locations::~Locations()
{
}

bool Locations::addLocation( Location *location )
{
  bool succeeded=false;

  if ( !locationHash.contains( location->label() ) ) {
    qDebug() << "Adding location" << location->label();
    locationHash[ location->label() ] = location;
    succeeded = true;
  }

  return succeeded;
}

Location *Locations::location( const QString &label )
{
  Location *retVal = 0;

  if ( locationHash.contains( label ) ) {
    retVal = locationHash[ label ];
  }

  return retVal;
}
