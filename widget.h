#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>

class QSerialPort;
class QLabel;
class QComboBox;
class QTextBrowser;
class QStatusBar;
class QLineEdit;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    void openSerialPort(void);
    void closeSerialPort(void);
    void activeSignalAndSlot(void);
    ~Widget();

signals:
   // void serialPortStatusChanged(bool);
public slots:
    void changeSerilPortClsAnDOpenBtnText(bool);
        void serialPortSendData(void);
        void serialPortReadData(void);

private:
    void setUI(void);
    QSerialPort *serialPort;
    QStatusBar *serialPortStatusBar;

    QLabel *serialPortLabel;
    QComboBox *serialPortComboBox;

    QLabel *serialPortBaudRateLabel;
    QComboBox *serialPortBaudRateComboBox;

    QLabel *serialPortDataBitsLabel;
    QComboBox *serialPortDataBisComboBox;

    QLabel *serialPortParityLabel;
    QComboBox *serialPortParityComboBox;

    QLabel *serialPortStopBitsLabel;
    QComboBox *serialPortStopBitsComboBox;

    QLabel *serialPortFlowControlLabel;
    QComboBox *serialPortFlowControlComboBox;

    QPushButton *closeOrOpenSerialPortBtn;

    QPushButton *senderBtn;

    QTextBrowser *serialPortTextBrowser;

    QLineEdit *serialPortLineEdit;

};

#endif // WIDGET_H
