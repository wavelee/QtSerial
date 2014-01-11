#include "widget.h"
#include <QLabel>
#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>


/**
 * @brief Widget::Widget
 * @param parent
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,serialPort(new QSerialPort(this))
    ,serialPortStatusBar(new QStatusBar())
    ,serialPortLabel(new QLabel(tr("Serial port:")))
    ,serialPortComboBox(new QComboBox())
    ,serialPortBaudRateLabel(new QLabel(tr("Baud Rate:")))
    ,serialPortBaudRateComboBox(new QComboBox())
    ,serialPortDataBitsLabel(new QLabel(tr("Data Bits:")))
    ,serialPortDataBisComboBox(new QComboBox())
    ,serialPortParityLabel(new QLabel(tr("Parity:")))
    ,serialPortParityComboBox(new QComboBox())
    ,serialPortStopBitsLabel(new QLabel(tr("Stop Bits:")))
    ,serialPortStopBitsComboBox(new QComboBox())
    ,serialPortFlowControlLabel(new QLabel(tr("Flow Control:")))
    ,serialPortFlowControlComboBox(new QComboBox())
    ,closeOrOpenSerialPortBtn(new QPushButton(tr("Open Serial Port")))
    ,senderBtn(new QPushButton(tr("Send")))
    ,serialPortTextBrowser(new QTextBrowser())
    ,serialPortLineEdit(new QLineEdit())
{
    setWindowIcon(QIcon(":/new/Icon/ICON"));
    setWindowTitle(tr("SerialCOM Assistant"));
    setUI();
    openSerialPort();
    activeSignalAndSlot();
}
/**
 * @brief Widget::~Widget
 */
Widget::~Widget()
{

}

/**
 * @brief Widget::setUI
 */
void Widget::setUI(void)
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
       serialPortComboBox->addItem(info.portName());
    }

    serialPortBaudRateComboBox->addItem(tr("1200"),QSerialPort::Baud1200);
    serialPortBaudRateComboBox->addItem(tr("2400"),QSerialPort::Baud2400);
    serialPortBaudRateComboBox->addItem(tr("4800"),QSerialPort::Baud4800);
    serialPortBaudRateComboBox->addItem(tr("9600"),QSerialPort::Baud9600);
    serialPortBaudRateComboBox->addItem(tr("19200"),QSerialPort::Baud19200);
    serialPortBaudRateComboBox->addItem(tr("38400"),QSerialPort::Baud38400);
    serialPortBaudRateComboBox->addItem(tr("57600"),QSerialPort::Baud57600);
    serialPortBaudRateComboBox->addItem(tr("115200"),QSerialPort::Baud115200);
    serialPortBaudRateComboBox->setCurrentIndex(3);

    serialPortDataBisComboBox->addItem(tr("5"),QSerialPort::Data5);
    serialPortDataBisComboBox->addItem(tr("6"),QSerialPort::Data6);
    serialPortDataBisComboBox->addItem(tr("7"),QSerialPort::Data7);
    serialPortDataBisComboBox->addItem(tr("8"),QSerialPort::Data8);
    serialPortDataBisComboBox->setCurrentIndex(3);

    serialPortParityComboBox->addItem(tr("None"),QSerialPort::NoParity);
    serialPortParityComboBox->addItem(tr("Even"),QSerialPort::EvenParity);
    serialPortParityComboBox->addItem(tr("Odd"),QSerialPort::OddParity);
    serialPortParityComboBox->addItem(tr("Mark"),QSerialPort::MarkParity);
    serialPortParityComboBox->addItem(tr("Space"),QSerialPort::SpaceParity);
    serialPortParityComboBox->setCurrentIndex(0);

    serialPortStopBitsComboBox->addItem((tr("1")),QSerialPort::OneStop);
#ifdef Q_OS_WIN
    serialPortStopBitsComboBox->addItem(tr("1.5"),QSerialPort::OneAndHalfStop);
#endif
    serialPortStopBitsComboBox->addItem(tr("2"),QSerialPort::TwoStop);
    serialPortStopBitsComboBox->setCurrentIndex(0);


    serialPortFlowControlComboBox->addItem(tr("None"),QSerialPort::NoFlowControl);
    serialPortFlowControlComboBox->addItem(tr("RTS/CTS"),QSerialPort::HardwareControl);
    serialPortFlowControlComboBox->addItem(tr("XON/XOFF"),QSerialPort::SoftwareControl);
    serialPortFlowControlComboBox->setCurrentIndex(0);


    QGridLayout  *leftLayout = new QGridLayout;
    leftLayout->addWidget(serialPortLabel,0,0);
    leftLayout->addWidget(serialPortComboBox,0,1);
    leftLayout->addWidget(serialPortBaudRateLabel,1,0);
    leftLayout->addWidget(serialPortBaudRateComboBox,1,1);
    leftLayout->addWidget(serialPortDataBitsLabel,2,0);
    leftLayout->addWidget(serialPortDataBisComboBox,2,1);
    leftLayout->addWidget(serialPortParityLabel,3,0);
    leftLayout->addWidget(serialPortParityComboBox,3,1);
    leftLayout->addWidget(serialPortStopBitsLabel,4,0);
    leftLayout->addWidget(serialPortStopBitsComboBox,4,1);
    leftLayout->addWidget(serialPortFlowControlLabel,5,0);
    leftLayout->addWidget(serialPortFlowControlComboBox,5,1);
    leftLayout->addWidget(closeOrOpenSerialPortBtn,6,0);
    leftLayout->addWidget(senderBtn,6,1);

    //serialPortTextBrowser->insertPlainText("Copyright wavlee.info\n");
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(serialPortTextBrowser);
    rightLayout->addWidget(serialPortLineEdit);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    serialPortStatusBar->showMessage(tr("Copyright wavelee.info"));

    QVBoxLayout *globleLayout = new QVBoxLayout;
    globleLayout->addLayout(mainLayout);
    globleLayout->addWidget(serialPortStatusBar);

    setLayout(globleLayout);
}

/**
 * @brief Widget::openSerialPort
 *
 */
void Widget::openSerialPort()
{
    serialPort->setPortName(serialPortComboBox->currentText());

    if(!serialPort->open(QIODevice::ReadWrite))
    {
        serialPortStatusBar->showMessage(tr("Can't open %1 error code %2")
                                         .arg(serialPortComboBox->currentText())
                                         .arg(serialPort->error()));

        serialPort->close();

        return;
    }
    else
    {
//        serialPortStatusBar->showMessage(tr("Open %1 Success!")
//                                         .arg(serialPort->portName()),1000);
    }

     QSerialPort::BaudRate currentBaudRate = static_cast<QSerialPort::BaudRate> \
                                ( serialPortBaudRateComboBox->currentData().toInt() );
     if( serialPort->setBaudRate(currentBaudRate) )
     {
//         serialPortStatusBar->showMessage(tr("Success set Buad Rate:%1")\
//                                          .arg(serialPortBaudRateComboBox->currentText()),
//                                          1000);
     }
     else
     {
         serialPortStatusBar->showMessage(tr("Can't set Baud Rate:%1,Error Code %2")
                                          .arg(serialPortBaudRateComboBox->currentText())
                                          .arg(serialPort->error()));
         serialPort->close();
         return;
     }

     QSerialPort::DataBits currentDataBits =
             static_cast<QSerialPort::DataBits>
             ( serialPortDataBisComboBox->currentData().toInt() );
     if( serialPort->setDataBits(currentDataBits) )
     {
//        serialPortStatusBar->showMessage(tr("Success set Data Bits %1")
//                                         .arg(serialPortDataBisComboBox->currentText()));
     }
     else
     {
         serialPortStatusBar->showMessage(tr("Can't set Data Bits:%1,Error Code %2")
                                          .arg(serialPortDataBisComboBox->currentText())
                                          .arg(serialPort->error()));
         serialPort->close();
         return;
     }

     QSerialPort::Parity currentParity =
             static_cast<QSerialPort::Parity>
             (serialPortParityComboBox->currentData().toInt());

     if(serialPort->setParity(currentParity))
     {
//         serialPortStatusBar->showMessage(tr("Success set Parity： %1")
//                                          .arg(serialPortParityComboBox->currentText()),
//                                          1000);
     }
     else
     {
        serialPortStatusBar->showMessage(tr("Can,t set Parity:%1,Error Code %2")
                                         .arg(serialPortParityComboBox->currentText())
                                         .arg(serialPort->error()));
        serialPort->close();
        return;
     }

     QSerialPort::StopBits currentStopBits =
             static_cast<QSerialPort::StopBits>
             (serialPortStopBitsComboBox->currentData().toInt());

     if(serialPort->setStopBits(currentStopBits))
     {
//         serialPortStatusBar->showMessage(tr("Success set Stop Bits:%1")
//                                          .arg(serialPortStopBitsComboBox->currentText()));
     }
     else
     {
        serialPortStatusBar->showMessage(tr("Can't set Stop Bits:%1,The Error Code is%2")
                                         .arg(serialPortStopBitsComboBox->currentText())
                                         .arg(serialPort->error()));

        serialPort->close();
        return;
     }

     QSerialPort::FlowControl currentFlowControl =
             static_cast<QSerialPort::FlowControl>
             (serialPortFlowControlComboBox->currentData().toInt());

     if(serialPort->setFlowControl(currentFlowControl))
     {
         serialPortStatusBar->showMessage(tr("Success set Flow Control:%1")
                                          .arg(serialPortFlowControlComboBox->currentText()));
     }
     else
     {
        serialPortStatusBar->showMessage(tr("Can't set Flow Control:%1,the Error Code is:%2")
                                         .arg(serialPortFlowControlComboBox->currentText())
                                         .arg(serialPort->error()));

        serialPort->close();
        return;
     }

     closeOrOpenSerialPortBtn->setText(tr("Close Serial Port"));
     serialPortStatusBar->showMessage(tr("Success Open Port: %1, "
                                         "Buad Rate: %2 "
                                         "Data Bits: %3 "
                                         "Parity: %4 "
                                         "Stop Bits: %5 "
                                         "Flow Control: %6 ")
                                      .arg(serialPortComboBox->currentText())
                                      .arg(serialPortBaudRateComboBox->currentText())
                                      .arg(serialPortDataBisComboBox->currentText())
                                      .arg(serialPortParityComboBox->currentText())
                                      .arg(serialPortStopBitsComboBox->currentText())
                                      .arg(serialPortFlowControlComboBox->currentText())
                                      );
     return;

}
/**
 * @brief Widget::closeSerialPort
 */
void Widget::closeSerialPort()
{
    QString currenPortName = serialPort->portName();
    serialPort->close();
    serialPortStatusBar->showMessage(tr("Success Close：%1")
                                     .arg(currenPortName));
}

/**
 * @brief Widget::activeSignalAndSlot
 */
void Widget::activeSignalAndSlot()
{
    QObject::connect(closeOrOpenSerialPortBtn,&QPushButton::clicked,
                     this,&Widget::changeSerilPortClsAnDOpenBtnText);


    QObject::connect(senderBtn,&QPushButton::clicked,this,
                     &Widget::serialPortSendData);

    QObject::connect(serialPort,&QSerialPort::readyRead,
                     this,&Widget::serialPortReadData);
}

void Widget::changeSerilPortClsAnDOpenBtnText(bool status)
{
    Q_UNUSED(status);
    if(serialPort->isOpen())
    {
        closeSerialPort();
        closeOrOpenSerialPortBtn->setText(tr("Open Serial Port"));
    }
    else
    {
        openSerialPort();
        closeOrOpenSerialPortBtn->setText(tr("Close Serial Port"));
    }

}

void Widget::serialPortSendData()
{
    QString sendText = serialPortLineEdit->text();
    if(sendText.isNull())
    {
        serialPortStatusBar->
                showMessage(tr("Send Line is NuLL"));
        QMessageBox::warning(this,tr("Warning"),
                             tr("Send Line is NUll,Please ensure the Send Data!"),
                             QMessageBox::Ok);
    }
    else
    {
        serialPort->write(sendText.toLatin1());
        //serialPortTextBrowser->insertPlainText(sendText);
    }
}


void Widget::serialPortReadData()
{
    QByteArray readData = serialPort->readAll();
    serialPortTextBrowser->
            insertPlainText( QString(readData) );
}
