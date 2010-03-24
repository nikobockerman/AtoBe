#include <QUrl>
#include <QString>

namespace Ytv {
  const QString Url( "http://api.reittiopas.fi/public-ytv/fi/api/" );
  const QString Username( "zouba" );
  const QString Password( "caf9r3ee" );

  //const QString Home( QByteArray::fromPercentEncoding( "Taivaanvuohentie%207%2CHelsinki" ) );
  //const QString Work( QByteArray::fromPercentEncoding( "It%E4merenkatu%2011%2CHelsinki" ) );

  enum {
    WalkSpeedSlow=1,
    WalkSpeedFast=2,
    WalkSpeedNormal=3,
    WalkSpeedRunning=4,
    WalkSpeedCycling=5,
    NoWalkSpeeds=5
  };

  enum {
    ShowOneResult=1,
    ShowThreeResults=3,
    ShowFiveResults=5
  };

  enum {
    OptimizeDefault=1,
    OptimizeFastest=2,
    OptimizeLeastTransfers=3,
    OptimizeLeastWalking=4
  };

};

