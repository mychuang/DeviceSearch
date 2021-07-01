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
    ui->ProbBtn->setStyleSheet("background-color: rgb(166,225,252)");
    ui->MacLab->setText(getMacAddress(mac));

    //For udp server
    ui->statusLabel->setText(tr("The server is running on IP: %1 and port: %2")
                             .arg(IPAddress).arg(MCAST_PORT));
    ui->msgLabel->setText("wait for Prob ...");
    connect(ui->ProbBtn, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    ui->modelEdit->setText("VC-A60");
    ui->userEdit->setText("admin");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getMacAddress(uint8_t *mac){
    QString from;
    //QString from(" 0x%02X ");

    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces()){
        qDebug()<<netInterface.addressEntries().at(1).ip();
        IPAddress = netInterface.addressEntries().at(1).ip().toString();

        if(!(netInterface.flags() & QNetworkInterface::IsLoopBack)){
            QString strMac = netInterface.hardwareAddress();
            for(int i=0; i<6; i++){
                mac[i] = (uint8_t)(strMac.mid(i*3, 2).toInt(NULL,16));
                //qDebug()<<mac[i];
            }
            return strMac;
        }
    }
    return NULL;
}


void MainWindow::on_pushButton_clicked(){
    qDebug() << __func__;
    QString getModelName = ui->modelEdit->text();
    QString getUserName = ui->userEdit->text();

    secUdp.Probe(getModelName, getUserName);
    ui->ProbBtn->setEnabled(false);
    ui->ProbBtn->setStyleSheet("background-color: rgb(65,65,65); color: rgb(255,255,255)");
    ui->msgLabel->setText("sending ...");
}
