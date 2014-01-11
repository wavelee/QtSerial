#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QTextBrowser>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QList<QSerialPortInfo> serialPortInfo;
    Ui::MainWindow *ui;
    QLabel *comSelectBoxLabel;
    QComboBox *comSelectBox;

    QLabel *baudRateSelectBoxLabel;
    QComboBox *baudRateSelectBox;
    QComboBox *paritySelectBox;
    QComboBox *stopBitsSelectBox;
    QTextBrowser *reciveTextBrowser;
    \

};

#endif // MAINWINDOW_H
