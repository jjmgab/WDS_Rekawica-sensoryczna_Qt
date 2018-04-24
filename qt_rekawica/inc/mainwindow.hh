#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QFile>
#include <QtSerialPort/QSerialPort>

#include <stdio.h>

#include "connection.hh"
#include "time.hh"

#define MAX_CONNECTION_TRIES 3
#define RECONNECT_SECONDS 5

#define SERIAL_OPEN_MODE QIODevice::ReadWrite

#define DEVICE_HANDSHAKE "01\n"
#define DEVICE_HANDSHAKE_RESPONSE 0x10
#define DEVICE_FIRST_WORD 0xF005

namespace Ui {
class MainWindow;
}

/*! 
 * \brief Klasa definiujaca glowne okno.
 * 
 * Klasa modeluje pojęcie głównego okna programu.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor parametryczny klasy MainWindow
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief Destruktor klasy MainWindow
     */
    ~MainWindow();

public slots:
    /*!
     * \brief Reakcja na wcisniecie opcji "Polacz"
     */
    void action_connect_click();
    /*!
     * \brief Reakcja na wcisniecie opcji "Rozlacz"
     */
    void action_disconnect_click();
    /*!
     * \brief Reakcja na wcisniecie opcji "Wyjdz"
     */
    void action_exit_click();

    /*!
     * \brief Reakcja na pojawienie sie danych na porcie szeregowym
     */
    void serial_dataAvailable();

    /*!
     * \brief Reakcja na pojawienie sie bledu na porcie szeregowym
     * 
     * \param[in] kod bledu
     */
    void serial_errorOccurred(QSerialPort::SerialPortError error);

    /*!
     * \brief Slot określający gotowość urządzenia do pracy
     */
    void device_ready();

signals:
    /*!
     * \brief Sygnal emitowany w celu realizacji rozłączenia urządzenia
     */
    void disconnect_me();
    void reconnect();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

    Connection *connectionWindow;

    bool flag_isConnected;
    bool device_isReady;
    bool device_firstWord;

    int timeout_counter;
};

#endif // MAINWINDOW_H
