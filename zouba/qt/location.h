#ifndef LOCATION_H
#define LOCATION_H

class Location
{
public:
  Location( QString x, QString y ) :
    x(x),
    y(y)
  {
  };

  QString x;
  QString y;
};
#endif // LOCATION_H
