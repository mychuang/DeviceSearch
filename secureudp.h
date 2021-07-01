#ifndef SECUREUDP_H
#define SECUREUDP_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QtNetwork>

#include "message.h"


class SecureUdp : public QThread
{
    Q_OBJECT
public:

    SecureUdp(QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
    QUdpSocket udpSender;

public slots:
    void Probe(QString modelName, QString userName);

};

#endif // SECUREUDP_H
