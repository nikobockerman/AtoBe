#include "messagehandler.h"

#include "messagetable.h"
#include <QString>
#include <QtGlobal>
#include <QTime>

void messageHandler( QtMsgType type, const char *msg )
{
  Q_UNUSED( type );

  if ( Ui::messageTable != 0 ) {
    Ui::messageTable->displayMessage( 
        QTime::currentTime().toString()+" "+QString::fromLatin1( msg )
        );
  }
}

