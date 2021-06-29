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

protected:
    // reimplements TcpServer::incomingConnection().
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QStringList fortunes;
};

#endif // FORTUNESERVER_H
