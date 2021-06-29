#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QNetworkDatagram>
#include <QtNetwork>
#include <QMessageBox>

uint8_t mac[6];
QString getMacAddress(uint8_t *mac);
QString IPAddress;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //For Tcp server
    /*if(!server.listen()){
        ui->msgLabel->setText(tr("Threaded Fortune Server"
                              "Unable to start the server: %1.").arg(server.errorString()));
        return;
    }else{
        ui->magLabel->setText("server listenning ...");
    }
    ui->statusLabel->setText(tr("The server is running on IP: %1 and port: %2")
                             .arg(IPAddress).arg(server.serverPort()));*/

    ui->MacLab->setText(getMacAddress(mac));

    //For udp server
    ui->statusLabel->setText(tr("The server is running on IP: %1 and port: %2")
                             .arg(IPAddress).arg(MCAST_PORT));
    ui->msgLabel->setText("wait for Prob ...");
    connect(ui->ProbBtn, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getMacAddress(uint8_t *mac){
    QString from;
    //QString from(" 0x%02X ");

    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces()){
    /* addressEntries():  Returns the list of IP addresses that
       this interface possesses along with their associated netmasks and broadcast addresses */
        qDebug()<<netInterface.addressEntries().at(1).ip();
        IPAddress = netInterface.addressEntries().at(1).ip().toString();

        if(!(netInterface.flags() & QNetworkInterface::IsLoopBack)){
            QString strMac = netInterface.hardwareAddress();
            for(int i=0; i<6; i++){
                qDebug()<<strMac.mid(i*3, 2);
                mac[i] = (uint8_t)(strMac.mid(i*3, 2).toInt(NULL,16));
                qDebug()<<strMac.mid(i*3, 2).toInt(NULL,16);
            }

            //from.sprintf("%02x", mac[0]);

            //qDebug()<<from.sprintf("%02x", mac[0]);
            //from = from.arg(mac[0]);
            //qDebug()<<from;

            return strMac;
        }
    }
    return NULL;
}


void MainWindow::on_pushButton_clicked(){
    qDebug() << __func__;
    ui->tableWidget->setRowCount(0);
    secUdp.Probe();
    ui->msgLabel->setText("sending ...");

}
