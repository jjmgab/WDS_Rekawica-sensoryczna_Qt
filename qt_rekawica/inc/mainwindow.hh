#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QtGlobal>

#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QVector>

#include <stdio.h>
#include <iostream>

#include "connection.hh"
#include "time.hh"
#include "qcustomplot.hh"
#include "functions.hh"

// opcje polaczenia
#define MAX_CONNECTION_TRIES        3
#define RECONNECT_SECONDS           5
#define SERIAL_OPEN_MODE            QIODevice::ReadWrite

// KOMUNIKACJA Z URZADZENIEM
// -- typy czujnikow
#define SENSOR_TYPE_BEND            0x1
#define SENSOR_TYPE_TOUCH           0x2
#define SENSOR_TYPE_ACC             0x3

// -- ID czujnika
#define SENSOR_ID_FINGER_THUMB      0x1
#define SENSOR_ID_FINGER_INDEX      0x2
#define SENSOR_ID_FINGER_MIDDLE     0x3
#define SENSOR_ID_FINGER_RING       0x4
#define SENSOR_ID_FINGER_PINKY      0x5
#define SENSOR_ID_ACC_XAXIS         0xA
#define SENSOR_ID_ACC_YAXIS         0xB

// -- zakresy czujnikow
#define SENSOR_RANGE_BEND_MIN       0x00
#define SENSOR_RANGE_BEND_MAX       0xFF
#define SENSOR_RANGE_TOUCH_MIN      0x00
#define SENSOR_RANGE_TOUCH_MAX      0xFF
#define SENSOR_RANGE_ACC_MIN        0x00
#define SENSOR_RANGE_ACC_MAX        0xFF

// -- komunikaty wysylane
#define DEVICE_HANDSHAKE            "01\n"

// -- komunikaty odbierane
#define DEVICE_HANDSHAKE_RESPONSE   0x10
#define DEVICE_FIRST_WORD           0xF005

// WYKRESY
#define X_RANGE_POINTS              20
#define TIMER_TIMEOUT_MS            100
// -- debugging i testy
#define MAX_SENSORS                 10
#define MAX_SENSORS_BEND            5

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

    void parse(const std::string&);

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



    /*!
     * \brief Uruchomienie testowego zbierania danych
     */
    void testrun_begin();

    /*!
     * \brief Reakcja na timeout timera testowego
     */
    void testrun_timeoutHandler();

signals:
    /*!
     * \brief Sygnal emitowany w celu realizacji rozłączenia urządzenia
     */
    void disconnect_me();

    /*!
     * \brief Sygnal emitowany w celu realizacji powtornej proby polaczenia
     */
    void reconnect();

private:
    Ui::MainWindow *ui;
    
    // -- ustawienia polaczenia
    Connection *connectionWindow;

    // -- polaczenie
    QSerialPort *serial;
    int timeout_counter;    // ilosc powtornych prob polaczenia

    // flagi komunikacji
    bool flag_isConnected;  // podlaczony
    bool device_firstWord;  // przeslal pierwszy komunikat
    bool device_isReady;    // gotowy do transmisji

    // -- dane do wykresow
    QVector<double> graph_time,         // czas

                    sensor_bend_01,     // kciuk zgiecie
                    sensor_bend_02,     // wskazujacy zgiecie
                    sensor_bend_03,     // srodkowy zgiecie
                    sensor_bend_04,     // serdeczny zgiecie
                    sensor_bend_05,     // maly zgiecie

                    sensor_touch_01,    // kciuk dotyk
                    sensor_touch_02,    // wskazujacy dotyk
                    sensor_touch_03,    // srodkowy dotyk
                    sensor_touch_04,    // serdeczny dotyk
                    sensor_touch_05,    // maly dotyk

                    sensor_acc_x,       // akcelerometr os x
                    sensor_acc_y;       // akcelerometr os y

    QVector<QVector<double>*> pointers_bendSensor;  // wskazniki na wektory danych czujnikow zgiecia

    double time_now;        // przechowuje aktualny czas polaczenia

    // -- ustawienia wykresow
    // zgiecie
    QVector<QPen> pens;

    // -- debug
    QTimer* debugTimer;
    bool debug_on;
    char* debug_frame;
};

#endif // MAINWINDOW_H
