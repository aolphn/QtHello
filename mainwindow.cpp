#include "mainwindow.h"
#include "application.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <iostream>
#include <Application.cpp>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("点击查看连接的设备");

    ui->listView->setVisible(false);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(executeCmd()));
    QObject::connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleDevicesItemClick(QModelIndex)));

}
void MainWindow::executeCmd(){
    QProcess p(0);
    p.start("adb devices");
    p.waitForStarted();
    p.waitForFinished();
    QString info = QString::fromLocal8Bit(p.readAllStandardOutput());
    QStringList list = info.split("\r\n");
    QStringList devices;
    for(QString s:list){
        if(s.contains("\t")){
            devices+=s.split("\t").at(0);
        }
     qDebug()<<"check splited string:"+s;
    }
    qDebug()<<info;

    ui->listView->setVisible(true);
    QStringListModel *models = new QStringListModel(devices);
    ui->listView->setModel(models);
}

void MainWindow::handleDevicesItemClick(QModelIndex index){
    qDebug()<<"click list view row:"+index.row();
}

MainWindow::~MainWindow()
{
    delete ui;
}
