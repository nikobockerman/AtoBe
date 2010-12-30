#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

#include <QThread>
#include <QMutex>

#include "location.h"
#include "routenew.h"
#include "locationfinder.h"

class RouteFinder : public QObject
{
    Q_OBJECT
public:
    explicit RouteFinder(const Location &from, const Location &to, QObject *parent = 0);
    ~RouteFinder();

    RouteNew* getRoute(int index) const;
    int getNumberOfRoutes() const;

signals:
    void finished();

public slots:

private slots:
    void fromLocationFound();
    void toLocationFound();
    void requestFinished();

private:
    void startRouteSearch();

    Location *from, *to;
    LocationFinder *fromFinder, *toFinder;
    QNetworkReply *reply;

    QList<RouteNew*> routes;
};

#endif // ROUTENEW_H
