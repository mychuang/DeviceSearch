#include "secureudp.h"
#include <QtNetwork>

SecureUdp::SecureUdp(int socketDescriptor, const QString &fortune, QObject *parent)
    :QThread(parent), socketDescriptor(socketDescriptor), text(fortune){

}

void SecureUdp::run(){
    QTcpSocket tcpSocket;

    //
    if(!tcpSocket.setSocketDescriptor(socketDescriptor)){
        emit error(tcpSocket.error());
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << text;

    tcpSocket.write(block);
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();

}
