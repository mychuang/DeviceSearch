#include "secureudp.h"
extern uint8_t mac[6];
extern QString IPAddress;


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

void SecureUdp::Probe(QString modelName, QString userName){
    qDebug()<<__func__;

    struct Message msg;
    memcpy(msg.from, mac, sizeof (msg.from));

    QByteArray charModelName = modelName.toLocal8Bit();
    QByteArray charUserName = userName.toLocal8Bit();

    strcpy(msg.Model_Name, charModelName);
    strcpy(msg.User_Name, charUserName);

    udpSender.writeDatagram((char *)&msg, sizeof(msg), QHostAddress(IPAddress), 5555);
}


