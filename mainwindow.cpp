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

    if(!server.listen()){
        ui->errLabel->setText(tr("Threaded Fortune Server"
                              "Unable to start the server: %1.").arg(server.errorString()));
        return;
    }else{
        ui->errLabel->setText("server listenning ...");
    }

    ui->MacLab->setText(getMacAddress(mac));
    ui->statusLabel->setText(tr("The server is running on IP: %1 and port: %2")
                             .arg(IPAddress).arg(server.serverPort()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getMacAddress(uint8_t *mac){

    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces()){
    /* addressEntries():  Returns the list of IP addresses that
       this interface possesses along with their associated netmasks and broadcast addresses */
        qDebug()<<netInterface.addressEntries().at(1).ip();
        IPAddress = netInterface.addressEntries().at(1).ip().toString();

        if(!(netInterface.flags() & QNetworkInterface::IsLoopBack)){
            QString strMac = netInterface.hardwareAddress();
            for(int i=0; i<6; i++){
                mac[i] = (uint8_t)(strMac.mid(i*3, 2).toInt(NULL,16));
            }
            return strMac;
        }
    }
    return NULL;
}
