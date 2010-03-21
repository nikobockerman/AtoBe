#ifndef MESSAGETABLE_H
#define MESSAGETABLE_H

#include <QWidget>
#include <QTableWidget>

class MessageTable : public QTableWidget
{
  Q_OBJECT

  enum {
    NumberOfRows=20,
    OneColumn=1
  };

public:
  MessageTable( QWidget *parent=0 );
  ~MessageTable();

  void displayMessage( const QString &message );

  /*
  QSize minimumSizeHint() const;
  QSize sizeHint() const;
  */
};
#endif //MESSAGETABLE_H
