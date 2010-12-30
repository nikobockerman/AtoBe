#include "locationfinder.h"
#include "ytv.h"

#include <QString>
#include <QUrl>
#include <QXmlStreamReader>
#include <QDebug>
#include <QNetworkRequest>
#include <stdexcept>

#include <QTimer>

LocationFinder::LocationFinder(QString address, QObject *parent) :
    QObject(parent), address(address), reply(NULL),
    places(QList<Location*>()), roadNames(QList<Location*>()),
    stops(QList<Location*>()), invalidResponse(false)
{
    QUrl fullUrl(Ytv::Url);

    fullUrl.addEncodedQueryItem( "key", this->address.toAscii().toPercentEncoding() );
    fullUrl.addQueryItem( "user", Ytv::Username );
    fullUrl.addQueryItem( "pass", Ytv::Password );

    qDebug() << "The query url: " << fullUrl.toString();

    this->reply = Ytv::manager.get(QNetworkRequest(fullUrl));
    connect(this->reply, SIGNAL(finished()), this, SLOT(processReply()));
}

LocationFinder::~LocationFinder()
{
    if (this->reply)
        this->reply->deleteLater();

    while (!this->places.isEmpty())
    {
        Location *loc = this->places.takeLast();
        delete loc;
    }
    while (!this->roadNames.isEmpty())
    {
        Location *loc = this->roadNames.takeLast();
        delete loc;
    }
    while (!this->stops.isEmpty())
    {
        Location *loc = this->stops.takeLast();
        delete loc;
    }
}


void LocationFinder::processReply()
{
    qDebug() << "Processing reply from Reittiopas in LocationFinder";
    QXmlStreamReader xml(this->reply->readAll());

    this->reply->disconnect(this, SLOT(searchFinished()));
    this->reply->deleteLater();
    this->reply = NULL;

    while (!xml.atEnd())
    {
        qDebug() << "Reading next element";
        xml.readNext();

        if (xml.isStartElement())
        {
            QString xmlName(xml.name().toString());

            if (xmlName == "LOC")
            {
                QXmlStreamAttributes attributes(xml.attributes());
                QStringRef xAttribute( attributes.value("x") );
                QStringRef yAttribute( attributes.value("y") );
                QString newX( xAttribute.toString() );
                QString newY( yAttribute.toString() );
                QString category(attributes.value("category").toString());
                QString name(attributes.value("name1").toString());
                QString number(attributes.value("number").toString());
                if (!number.isEmpty())
                {
                    name.append(" ");
                    name.append(number);
                }
                name.append(", ");
                name.append(attributes.value("city").toString());

                if (category == "poi")
                {
                    this->places.append(new Location(newX, newY, name));
                }
                else if (category == "street")
                {
                    this->roadNames.append(new Location(newX, newY, name));
                }
                else if (category == "stop")
                {
                    this->stops.append(new Location(newX, newY, name));
                }
                else
                {
                    QString errorMessage("Unknown category: ");
                    errorMessage.append(category);
                    qDebug() << errorMessage;
                }
            }

            if (xmlName == "ERROR") {
                this->invalidResponse = true;
            }

        }
    }

    qDebug() << xml.errorString();
    if ( xml.hasError() ) {
        qDebug() << "Invalid response received from Ytv";
        this->invalidResponse = true;
    } else {
        int locationsFound = this->places.size() + this->roadNames.size() + this->stops.size();
        qDebug() << "Number of locations received: " + locationsFound;
    }
    qDebug() << "Exiting xml parsing.";

    emit(finished());
}

bool LocationFinder::responseWasValid() const
{
    return !this->invalidResponse;
}

bool LocationFinder::locationsFound() const
{
    return (this->numberOfLocationsFound() > 0);
}

int LocationFinder::numberOfLocationsFound() const
{
    return this->numberOfPlaces() + this->numberOfRoadNames() + this->numberOfStops();
}

int LocationFinder::numberOfPlaces() const
{
    return this->places.size();
}

int LocationFinder::numberOfRoadNames() const
{
    return this->roadNames.size();
}

int LocationFinder::numberOfStops() const
{
    return this->stops.size();
}

Location* LocationFinder::getPlace(int index) const
{
    if (index < 0 || index >= this->places.size())
        throw std::invalid_argument("Given index out of bounds.");

    return new Location(*(this->places.at(index)));
}

Location* LocationFinder::getRoadName(int index) const
{
    if (index < 0 || index >= this->roadNames.size())
        throw std::invalid_argument("Given index out of bounds.");

    return new Location(*(this->roadNames.at(index)));
}

Location* LocationFinder::getStop(int index) const
{
    if (index < 0 || index >= this->stops.size())
        throw std::invalid_argument("Given index out of bounds.");

    return new Location(*(this->stops.at(index)));
}

const QList<Location*>& LocationFinder::getPlaces() const
{
    return this->places;
}

const QList<Location*>& LocationFinder::getRoadNames() const
{
    return this->roadNames;
}

const QList<Location*>& LocationFinder::getStops() const
{
    return this->stops;
}
