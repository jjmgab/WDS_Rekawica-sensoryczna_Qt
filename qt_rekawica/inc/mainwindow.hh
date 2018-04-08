#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>

#define SERIAL_OPEN_MODE QIODevice::ReadWrite

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void action_connect_click();
    void action_disconnect_click();
    void action_exit_click();
    void serial_dataAvailable();
    void serial_errorOccurred(QSerialPort::SerialPortError error);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

    bool flag_isConnected;
};

#endif // MAINWINDOW_H
