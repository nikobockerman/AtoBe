#include "location.h"

#include "ytv.h"

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QDebug>
#include <QXmlStreamAttributes>
#include <QStringRef>
#include <QGeoPositionInfo>

#include <math.h>

Location::Location( const QString &x, const QString &y, const QString &label, const QString &address ) :
        m_label(label),
        m_address(address),
        m_x(x),
        m_y(y),
        m_valid(true)
{
}

Location::Location(const QString &label, const QString &address) :
        m_label(label),
        m_address(address),
        m_x(QString()),
        m_y(QString()),
        m_valid(false)
{
}

void Location::setPosition(const QString &x, const QString &y, const QString &address)
{
    this->m_x = x;
    this->m_y = y;
    this->m_address = address;
    this->m_valid = true;
}

QString Location::x() const
{
    return m_x;
}

QString Location::y() const
{
    return m_y;
}

void Location::setLabel(const QString &label)
{
    m_label = label;
}

QString Location::label() const
{
    return m_label;
}

QString Location::address() const
{
    return m_address;
}

bool Location::isValid() const
{
    return m_valid;
}
