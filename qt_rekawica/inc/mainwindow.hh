#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QFile>
#include <QtSerialPort/QSerialPort>

#include <stdio.h>

#include "connection.hh"

#define SERIAL_OPEN_MODE QIODevice::ReadWrite

#define DEVICE_HANDSHAKE "01\n"
#define DEVICE_HANDSHAKE_RESPONSE 0x10
#define DEVICE_FIRST_WORD 0xF005

namespace Ui {
class MainWindow;
}

/**
 * 
 * Klasa definiujaca glowne okno.
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /**
     * Reakcja na wcisniecie opcji "Polacz"
     */
    void action_connect_click();
    /**
     * Reakcja na wcisniecie opcji "Rozlacz"
     */
    void action_disconnect_click();
    /**
     * Reakcja na wcisniecie opcji "Wyjdz"
     */
    void action_exit_click();

    /**
     * Reakcja na pojawienie sie danych na porcie szeregowym
     */
    void serial_dataAvailable();
    /**
     * Reakcja na pojawienie sie bledu na porcie szeregowym
     * 
     * @param kod bledu
     */
    void serial_errorOccurred(QSerialPort::SerialPortError error);

    void device_ready();

signals:
    void disconnect_me();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

    Connection *connectionWindow;

    bool flag_isConnected;
    bool device_isReady;
    bool device_firstWord;
};

#endif // MAINWINDOW_H
