#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkInterface>
//#include "fortuneserver.h"
#include "secureudp.h"

#include "message.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SecureUdp secUdp;

    //for Tcp Server
    //FortuneServer server;


private slots:
    void on_pushButton_clicked();
    void on_clean_clicked();

};
#endif // MAINWINDOW_H
