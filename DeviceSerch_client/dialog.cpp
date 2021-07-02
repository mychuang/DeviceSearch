#include "dialog.h"
#include "ui_dialog.h"
#include <message.h>
#include <QDataStream>
#include <QtNetwork>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
//ui
    ui->ipLabel->setStyleSheet("color: white");
    ui->MACLabel->setStyleSheet("color: white");
    ui->userLabel->setStyleSheet("color: white");
    ui->modelLabel->setStyleSheet("color: white");

    ui->ipEdit->setStyleSheet("color: yellow");
    ui->MACEdit->setStyleSheet("color: yellow");
    ui->userEdit->setStyleSheet("color: yellow");
    ui->modelEdit->setStyleSheet("color: yellow");

//udp binding
    udpSocket.bind(5555);
    connect(&udpSocket, &QUdpSocket::readyRead, this, &Dialog::processPendingDatagrams);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::processPendingDatagrams(){
    QHostAddress Fipstr;
    Message msg;
    do{
        udpSocket.readDatagram((char *)&msg, sizeof(msg), &Fipstr);

    }while(udpSocket.hasPendingDatagrams());

    //get mac
    uint8_t Fmac[6];
    QString from;
    memcpy(Fmac, msg.from, 6);
    from.sprintf("%02X:%02X:%02X:%02X:%02X:%02X",
                 Fmac[0],Fmac[1],Fmac[2],Fmac[3],Fmac[4],Fmac[5]);
    ui->MACEdit->setText(from);


    //get others
    ui->modelEdit->setText(QString(msg.Model_Name));
    ui->userEdit->setText(QString(msg.User_Name));

    QString str = QString("%1").arg(Fipstr.toString());
    ui->ipEdit->setText(str);
}
