#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "ui_zouba.h"

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class HttpClientPrivate;

class HttpClient: public QObject
{
  Q_OBJECT

public:
  HttpClient( Ui::MainWindow *ui );
  ~HttpClient();

  void get();

public Q_SLOTS:
  void replyFinished(QNetworkReply*);

private:
  HttpClientPrivate *q;
  QNetworkAccessManager *manager;
  Ui::MainWindow *ui;

};
#endif // HTTPCLIENT_H
