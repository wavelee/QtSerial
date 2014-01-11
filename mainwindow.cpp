#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    reciveTextBrowser = new QTextBrowser(this);
    setCentralWidget(reciveTextBrowser);

    comSelectBox = new QComboBox;
    comSelectBoxLabel = new QLabel(tr("&Com Select:"),this);
    comSelectBoxLabel->setBuddy(comSelectBox);
    QHBoxLayout *comSelectBoxLayout = new QHBoxLayout;
    comSelectBoxLayout->addWidget(comSelectBoxLabel);
    comSelectBoxLayout->addWidget(comSelectBox);


    baudRateSelectBox = new QComboBox;
    baudRateSelectBoxLabel = new QLabel(tr("Baudrate Select:"),this);
    baudRateSelectBoxLabel->setBuddy(baudRateSelectBox);
    QHBoxLayout *baudRateSelectBoxLayout = new QHBoxLayout;
    baudRateSelectBoxLayout->addWidget(baudRateSelectBoxLabel);
    baudRateSelectBoxLayout->addWidget(baudRateSelectBox);


    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(comSelectBoxLayout);
    vlayout->addLayout(baudRateSelectBoxLayout);
    setLayout(vlayout);


    serialPortInfo = QSerialPortInfo::availablePorts();

    //没有串口
    if(serialPortInfo.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Can not find the Serial Port"));
        msgBox.exec();
    }
    else
    {
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
