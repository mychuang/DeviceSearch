#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QNetworkDatagram>

uint8_t mac[6];
QString getMacAddress(uint8_t *mac);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->MacLab->setText(getMacAddress(mac));

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
