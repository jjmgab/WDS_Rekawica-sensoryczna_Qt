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
#define SENSOR_ID_ACC_ZAXIS         0xB

// -- zakresy czujnikow
#define SENSOR_RANGE_BEND_MIN       0x00
#define SENSOR_RANGE_BEND_MAX       0xFF
#define SENSOR_RANGE_TOUCH_MIN      0x00
#define SENSOR_RANGE_TOUCH_MAX      0xFF
#define SENSOR_RANGE_ACC_MIN        0x00
#define SENSOR_RANGE_ACC_MAX        0xFF

// -- zakresy progress barow
#define BAR_PERCENTAGE_MAX              0x64
#define BAR_PERCENTAGE_MIN              0x00

// -- komunikaty wysylane
#define DEVICE_HANDSHAKE            "01\n"
#define DEVICE_START                "02\n"

// -- komunikaty odbierane
#define DEVICE_HANDSHAKE_RESPONSE   0x10
#define DEVICE_START_RESPONSE       0x20
#define DEVICE_FIRST_WORD           0xF0

// WYKRESY
#define X_RANGE_POINTS              20
#define TIMER_TIMEOUT_MS            250

// -- debugging i testy
#define MAX_SENSORS_BEND            5
#define MAX_SENSORS_TOUCH           5
#define MAX_AXIS_ACC                2
#define MAX_SENSORS                 MAX_SENSORS_BEND + MAX_SENSORS_TOUCH + MAX_AXIS_ACC

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
private:
    QGraphicsScene *scene_visualisation = new QGraphicsScene;
    QGraphicsScene *scene_orientation = new QGraphicsScene;

    /*!
    * \brief Ustawia scene wizualizacji
    *
    * \param[in] int typ sensora (1-2)
    * \param[in] int id palca (1-5)
    * \param[in] int wartosc chwili obecnej (0-255)
    */
    void set_hand_visualisation_scene(int sensor_type, int sensor_id, int sensor_value);

    /*!
     * \brief Resetuje wizualizacje do stanu niepodlaczonego
     */
    void reset_hand_visualisation_scene();


public:
    /*!
     * \brief Konstruktor parametryczny klasy MainWindow
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief Destruktor klasy MainWindow
     */
    ~MainWindow();

    /*!
     * \brief Parsuje ramke danych
     */
    void parse(const std::string&);

    /*!
    * \brief Przelicza wartosci 8 bitowe na wartosci procentowe
    * 
    * \param[in] wartosc 8 bitowa
    * \param[out] wartosc procentowa 0-100% double
    */
    double convert_touch_value(double touch_value);

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

    void handle_data(const std::string& _data);


    /*!
     * \brief Uruchomienie testowego zbierania danych
     */
    void testrun();

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

                                        // w przypadku sensorow dotyku dane dotycza rowniez progress barow
                    sensor_touch_01,    // kciuk dotyk
                    sensor_touch_02,    // wskazujacy dotyk
                    sensor_touch_03,    // srodkowy dotyk
                    sensor_touch_04,    // serdeczny dotyk
                    sensor_touch_05,    // maly dotyk

                    sensor_acc_x,       // akcelerometr os x
                    sensor_acc_z;       // akcelerometr os z

    QVector<QVector<double>*> pointers_bendSensor;  // wskazniki na wektory danych czujnikow zgiecia
    QVector<QVector<double>*> pointers_touchSensor; // wskazniki na wektory danych czujnikow dotyku
    QVector<QVector<double>*> pointers_accSensor;   // wskazniki na wektory danych akcelerometru

    double time_now;        // przechowuje aktualny czas polaczenia

    // -- ustawienia wykresow
    // zgiecie 
    QVector<QPen> pens;
    QVector<QPen> pens_ACC;

    // -- debug
    QTimer* debugTimer;
    bool debug_on;
    char* debug_frame;
};

#endif // MAINWINDOW_H
