#include <QUrl>
#include <QString>

namespace Ytv {
  const QString Url( "http://api.reittiopas.fi/public-ytv/fi/api/" );
  const QString Username( "zouba" );
  const QString Password( "caf9r3ee" );

  const QString Home( QByteArray::fromPercentEncoding( "Taivaanvuohentie%207%2CHelsinki" ) );
  const QString Work( QByteArray::fromPercentEncoding( "It%E4merenkatu%2011%2CHelsinki" ) );

  enum {
    Slow=1,
    Fast=2,
    Normal=3,
    Running=4,
    Cycling=5,
    NoWalkSpeeds=5
  };

  enum {
    OneResult=1,
    ThreeResults=3,
    FiveResults=5
  };

};

