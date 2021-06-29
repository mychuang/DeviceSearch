#include "fortuneserver.h"
#include "secureudp.h"
#include <QRandomGenerator>
#include <stdlib.h>

FortuneServer::FortuneServer(QObject *parent):QTcpServer(parent)
{
    fortunes << tr("01 You've been leading a dog's life. Stay off the furniture.")
             << tr("02 You've got to think about tomorrow.")
             << tr("03 You will be surprised by a loud noise.")
             << tr("04 You will feel hungry again in another hour.")
             << tr("05 You might have mail.")
             << tr("06 You cannot kill time without injuring eternity.")
             << tr("07 Computers are not intelligent. They only think they are.");
}

void FortuneServer::incomingConnection(qintptr socketDescriptor){
    QString fortune = fortunes.at(QRandomGenerator::global()->bounded(fortunes.size()));
    qDebug()<<fortune;
    /* passing the incoming socket descriptor and a random fortune to SecureUdp. */
    SecureUdp *thread = new SecureUdp(socketDescriptor, fortune, this);
    thread->start();
}
