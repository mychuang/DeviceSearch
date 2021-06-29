#include "secureudp.h"
extern uint8_t mac[6];

//SecureUdp::SecureUdp(int socketDescriptor, const QString &fortune, QObject *parent)
//    :QThread(parent), socketDescriptor(socketDescriptor), text(fortune){
SecureUdp::SecureUdp(QObject *parent):QThread(parent){


}

void SecureUdp::run(){
    //for tcp server
    /*
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
    tcpSocket.waitForDisconnected();*/



}

void SecureUdp::Probe(){
    qDebug()<<__func__;
    // this for easy test
    /*QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << QTime::currentTime();
    qDebug()<<QTime::currentTime();
    udpSender.writeDatagram(datagram, QHostAddress::LocalHost, 5555);*/

    // this for search-gui
    struct Message msg;
    msg.magic = MCAST_MSG_MAGIC;
    msg.type  = MCAST_MSG_PROBE;
    memcpy(msg.from, mac, sizeof (msg.from));
    memset(msg.to, 0, sizeof(msg.to));
    msg.size = 0;

    udpSender.writeDatagram((const char *)&msg.from, QHostAddress::LocalHost, 5555);

}
