#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QStringList>

class FortuneServer: public QTcpServer
{
    Q_OBJECT
public:
    FortuneServer(QObject *parent = 0);
};

#endif // FORTUNESERVER_H
