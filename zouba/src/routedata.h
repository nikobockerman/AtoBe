#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include <QString>

struct RouteData
{
  RouteData():
    lineCode(),
    arrivalTime()
  {
  };

  RouteData( QString lineCode, QString arrivalTime ):
    lineCode(lineCode),
    arrivalTime(arrivalTime)
  {
  };

  QString lineCode;
  QString arrivalTime;
};

#endif // ROUTEDATA_H
