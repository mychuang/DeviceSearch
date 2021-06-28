#include "secureudp.h"
#include <QtNetwork>

SecureUdp::SecureUdp(int socketDescriptor, const QString &fortune, QObject *parent)
    :QThread(parent), socketDescriptor(socketDescriptor), text(fortune){

}

void SecureUdp::run(){}
