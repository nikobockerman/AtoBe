#include "locations.h"

#include <QDebug>
#include <QHash>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QCoreApplication>

QHash<QString,Location *> Locations::locationHash;
Locations Locations::singleton;

Locations::Locations()
{
  QCoreApplication::setOrganizationName("ZouBa");
  QCoreApplication::setOrganizationDomain("zouba.yi.org");
  QCoreApplication::setOrganizationName("ZouBa");

  restoreLocations();
}

Locations::~Locations()
{
}

Locations *Locations::instance()
{
  return &singleton;
}

bool Locations::addLocation( Location *location )
{
  bool succeeded=false;

  // if it's valid now, save the setting
  if ( location->isValid() ) {
    saveLocation( location );
  }

  if ( !locationHash.contains( location->label() ) ) {
    qDebug() << "Adding location" << location->label();
    locationHash[ location->label() ] = location;
    succeeded = true;
  } else {
    qDebug() << "FAILED to add location" << location->label();
  }

  return succeeded;
}

void Locations::restoreLocations()
{
  QSettings settings;

  settings.beginGroup( "Locations" );
  QStringList labels = settings.childGroups();

  for( int i=0; i<labels.size(); ++i ) {
    QString label = labels[i];
    settings.beginGroup( label );
    QString x       = settings.value( "x" ).toString();
    QString y       = settings.value( "y" ).toString();
    QString address = settings.value( "address" ).toString();
    settings.endGroup();

    qDebug() << "restoring" << label;
    Location *location = new Location( x, y, label );
    location->setAddress( address );

    locationHash[ label ] = location;
  }

  settings.endGroup();
}

void Locations::saveLocation( Location *location )
{
  qDebug() << "Saving location" << location->label();
  QSettings settings;
  settings.beginGroup( "Locations" );
  settings.beginGroup( location->label() );
  settings.setValue( "address", location->address() );
  settings.setValue( "x", location->x() );
  settings.setValue( "y", location->y() );
  settings.endGroup();
  settings.endGroup();
}

void Locations::saveLocation()
{
  Location *location = qobject_cast<Location*>(sender());

  saveLocation( location );
}

Location *Locations::location( const QString &label )
{
  qDebug() << "requesting location" << label;
  Location *retVal = 0;

  if ( locationHash.contains( label ) ) {
    qDebug() << "found location" << label;
    retVal = locationHash[ label ];
  } else {
    qDebug() << "didn't find location" << label;
  }

  return retVal;
}
