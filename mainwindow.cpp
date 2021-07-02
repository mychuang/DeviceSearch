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
    ui->centralwidget->setStyleSheet("background: rgba(32, 80, 96, 100)");
    ui->ProbBtn->setStyleSheet("color: white; background-color: rgba(244, 233, 154, 100)");
    ui->ClnBtn->setStyleSheet("color: white; background-color: rgba(152, 246, 186, 100)");

    ui->userEdit->setStyleSheet("background-color: white; color: purple; border-radius: 6px");
    ui->modelEdit->setStyleSheet("background-color: white; color: purple; border-radius: 6px");

    ui->userlab->setStyleSheet("color: white");
    ui->TitleLab->setStyleSheet("color: white");
    ui->modelLab->setStyleSheet("color: white");
    ui->msgLabel->setStyleSheet("color: white");
    ui->statusLabel->setStyleSheet("color: white");
    ui->MacLab->setStyleSheet("color: white");
    ui->MacLab->setText(getMacAddress(mac));

    //For udp server
    ui->statusLabel->setText(tr("The server is running on IP: %1 and port: %2")
                             .arg(IPAddress).arg(MCAST_PORT));
    ui->msgLabel->setText("wait for Prob ...");
    connect(ui->ProbBtn, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->ClnBtn, &QPushButton::clicked, this, &MainWindow::on_clean_clicked);

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

void MainWindow::on_clean_clicked(){
    qDebug() << __func__;
    ui->modelEdit->setText("");
    ui->userEdit->setText("");
    ui->msgLabel->setText("wait for Prob ...");
    ui->ProbBtn->setEnabled(true);
    ui->ProbBtn->setStyleSheet("background-color: rgba(244, 233, 154, 100)");
}
