#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include <QString>
#include <QList>

struct LegData
{
  LegData() :
    m_how(),
    m_tripTime(),
    m_tripDistance(),
    m_departureTime(),
    m_arrivalTime(),
    m_lineCode()
  {
  };

  LegData( QString how, QString tripTime, QString tripDistance, QString departureTime, QString arrivalTime, QString lineCode=QString() ) :
    m_how(how),
    m_tripTime(tripTime),
    m_tripDistance(tripDistance),
    m_departureTime(departureTime),
    m_arrivalTime(arrivalTime),
    m_lineCode(lineCode)
  {
  };

  void clear()
  {
    m_how = "";
    m_tripTime = "";
    m_tripDistance = "";
    m_departureTime = "";
    m_arrivalTime = "";
    m_lineCode = "";
  };

  QString m_how;
  QString m_tripTime;
  QString m_tripDistance;
  QString m_departureTime;
  QString m_arrivalTime;
  QString m_lineCode;

};

struct RouteData
{
  RouteData():
    m_tripTime(),
    m_tripDistance(),
    m_departureTime(),
    m_lineCode(),
    m_legData()
  {
  };

  RouteData( QString tripTime, QString tripDistance, QString departureTime, QString lineCode ):
    m_tripTime(tripTime),
    m_tripDistance(tripDistance),
    m_departureTime(departureTime),
    m_lineCode(lineCode),
    m_legData()
  {
  };

  RouteData &operator <<(const LegData &legData)
  {
    m_legData.append( legData );
    return *this;
  };

  void clear()
  {
    m_tripTime = "";
    m_tripDistance = "";
    m_departureTime = "";
    m_lineCode = "";
    m_legData.clear();
  };

  QString m_tripTime;
  QString m_tripDistance;
  QString m_departureTime;
  QString m_lineCode;
  QList<LegData> m_legData;

};

#endif // ROUTEDATA_H
