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
    /*tcp server*/
    //SecureUdp(int socketDescriptor, const QString &fortune, QObject *parent);
    /*udp server*/
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
    void Probe();

};

#endif // SECUREUDP_H
