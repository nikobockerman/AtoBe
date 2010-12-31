#ifndef LOCATION_H
#define LOCATION_H

#include <QString>


class Location
{

public:
    Location( const QString &x, const QString &y, const QString &label, const QString &address = QString());

    //Location( const QGeoPositionInfo &positionInfo, const QString &label=QString() );
    Location( const QString &label, const QString &address);
    //Location(const Location &location);
    //Location(const Location *location);

    Location& operator=(const Location &other);

    QString x() const;
    QString y() const;

    void setPosition(const QString &x, const QString &y, const QString &address = QString());

    //void setAddress( const QString &address );
    QString address() const;

    void setLabel( const QString &label );
    QString label() const;

    bool isValid() const;

protected:
    QString m_label;
    QString m_address;
    QString m_x;
    QString m_y;
    bool m_valid;
};




#endif // LOCATION_H
