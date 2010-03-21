#ifndef STLHELPERS4QT_H
#define STLHELPERS4QT_H

#include <ostream>
#include <QList>
#include <QVariant>

/**
 * Outputs the contents of a QList<QVariant> container to a std::ostream object.
 * @param stream the stream to output to
 * @param val the container that is put to the stream
 * @return the same stream that was passed as the parameter @a stream
 */
std::ostream& operator<<(std::ostream& stream, const QList<QVariant> &val)
{
    bool first = true;

    foreach (const QVariant &v, val) {
        if (!first) {
            stream << ", ";
        }
        stream << v.toString().toStdString();
        first = false;
    }
    return stream;
}

#endif // STLHELPERS4QT_H
