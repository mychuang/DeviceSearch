#ifndef SECUREUDP_H
#define SECUREUDP_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class SecureUdp : public QThread
{
    Q_OBJECT
public:
    SecureUdp(int socketDescriptor, const QString &fortune, QObject *parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
};

#endif // SECUREUDP_H
