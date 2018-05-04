#include "mainwindow.hh"
#include "ui_mainwindow.hh"

/*!
 * \file
 * \brief Definicja metod klasy MainWindow
 * 
 * Definiuje wszystkie metody klasy MainWindow.
 */

/*!
 * \brief Konstruktor parametryczny klasy.
 * 
 * Inicjalizuje wszystkie graficzne elementy okna
 * oraz definiuje połączenia między wykorzystywanymi sygnałami i slotami.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);

    connectionWindow = nullptr;

    device_isReady = false;
    device_firstWord = false;
    flag_isConnected = false;

    timeout_counter = 0;
    time_now = 0.0f;

    pointers_bendSensor.append(&sensor_bend_01);
    pointers_bendSensor.append(&sensor_bend_02);
    pointers_bendSensor.append(&sensor_bend_03);
    pointers_bendSensor.append(&sensor_bend_04);
    pointers_bendSensor.append(&sensor_bend_05);

    // wyswietl poczatkowy status
    ui->statusBar->showMessage(tr("Status: Rozłączony"));

    // Laczenie opcji z menu
    QObject::connect(ui->action_connect, SIGNAL(triggered()), this, SLOT(action_connect_click()));
    QObject::connect(ui->action_disconnect, SIGNAL(triggered()), this, SLOT(action_disconnect_click()));
    QObject::connect(ui->action_exit, SIGNAL(triggered()), this, SLOT(action_exit_click()));

    QObject::connect(this, SIGNAL(disconnect_me()), this, SLOT(action_disconnect_click()));
    QObject::connect(this, SIGNAL(reconnect()), this, SLOT(action_connect_click()));

    // opcje do debugowania
    debugTimer = new QTimer(this);
    debug_on = false;
    qsrand(qrand());

    // KONFIGURACJA WYKRESOW
    QPen p_thumb,
         p_index,
         p_middle,
         p_ring,
         p_pinky;

    p_thumb.setColor(Qt::black);
    p_index.setColor(Qt::red);
    p_middle.setColor(Qt::blue);
    p_ring.setColor(Qt::green);
    p_pinky.setColor(Qt::magenta);

    pens.append(p_thumb);
    pens.append(p_index);
    pens.append(p_middle);
    pens.append(p_ring);
    pens.append(p_pinky);

    ui->graph_bending->yAxis->setRange(SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX);
    ui->graph_bending->xAxis->setLabel(tr("Czas pomiaru, s"));
    ui->graph_bending->yAxis->setLabel(tr("Wartosc zgiecia"));
    ui->graph_bending->setBackground(QBrush(Qt::white));

    for (int i = 0; i < MAX_SENSORS_BEND; i++) {
        ui->graph_bending->addGraph();
        ui->graph_bending->graph(i)->setPen(pens.at(i));
    }

    QObject::connect(ui->action_testrun, SIGNAL(triggered()), this, SLOT(testrun_begin()));
    QObject::connect(debugTimer, SIGNAL(timeout()), this, SLOT(testrun_timeoutHandler()));

}

/*!
 * \brief Destruktor klasy MainWindow.
 */
MainWindow::~MainWindow() {
    debugTimer->stop();

    std::cout << "~serial" << std::endl;
    if (serial != nullptr) delete serial;

    std::cout << "~connectionWindow" << std::endl;
    if (connectionWindow != nullptr) delete connectionWindow;

    std::cout << "~debugTimer" << std::endl;
    if (debugTimer != nullptr) delete debugTimer;

    std::cout << "~ui" << std::endl;
    delete ui;

    std::cout << "destruktory - sukces!" << std::endl;
}

/*!
 * \brief Slot określający reakcję na wciśnięcie przycisku "Połącz"
 * 
 * Uruchamia dodatkowe okno klasy Connection, w którym użytkownik
 * określa ustawienia połączenia. Następnie podejmuje próbę połączenia.
 */
void MainWindow::action_connect_click() {
    ui->terminal->append(tr("Próba połączenia nr ") + QString::number(timeout_counter) + ". . .\n");

    if (timeout_counter < 1) {
    // otwieranie ustawien polaczenia
    connectionWindow = new Connection(this);
    if (connectionWindow->exec() == QDialog::Accepted) {
        
        // czyszczenie poprzedniego portu - przy rozlaczeniu i ponownym laczeniu
        if (serial != nullptr) {
            if (serial->isOpen()) {
                serial->close();
            }
            delete serial;
        }
        
        serial = new QSerialPort(this);

        // laczenie reakcji na sygnaly portu szeregowego
        QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(serial_dataAvailable()));
        QObject::connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(serial_errorOccurred(QSerialPort::SerialPortError)));


        QString portName = connectionWindow->ui->portName->currentText().simplified();
        serial->setPortName(portName);

        if(!serial->setBaudRate((QSerialPort::BaudRate) connectionWindow->ui->baudRate->currentText().toInt()))
            ui->terminal->append(tr("QSerialError: błąd ustawienia BaudRate"));
        
        if(!serial->setDataBits((QSerialPort::DataBits) connectionWindow->ui->dataBits->currentText().toInt()))
            ui->terminal->append(tr("QSerialError: błąd ustawienia DataBits"));

        if(!serial->setParity(connectionWindow->ui->parity->currentText() == "Nieparzysty" ? QSerialPort::OddParity : QSerialPort::EvenParity))
            ui->terminal->append(tr("QSerialError: błąd ustawienia Parity"));

        if(!serial->setFlowControl(connectionWindow->ui->flowControl->currentText() == "Hardware" ? QSerialPort::HardwareControl : QSerialPort::SoftwareControl))
            ui->terminal->append(tr("QSerialError: błąd ustawienia FlowControl"));

        if(!serial->setStopBits((QSerialPort::StopBits) connectionWindow->ui->stopBits->currentText().toInt()))
            ui->terminal->append(tr("QSerialError: błąd ustawienia StopBits"));

    }
    delete connectionWindow;
    }

    

    // proba polaczenia
    serial->open(SERIAL_OPEN_MODE);
    // sukces
    if (serial->isOpen()) {
        flag_isConnected = true;
        ui->action_connect->setEnabled(false);
        ui->action_disconnect->setEnabled(true);

        ui->statusBar->showMessage(tr("Status: Połączony"));
    }
    // ponawianie polaczenia
    else if (timeout_counter < MAX_CONNECTION_TRIES) {

        ui->terminal->append(tr("Ponawianie próby połączenia"));
        for (int i = 0; i < RECONNECT_SECONDS; i++) {
            delay_seconds(1);
            ui->terminal->moveCursor(QTextCursor::End);
            ui->terminal->insertPlainText(". ");
            ui->terminal->moveCursor(QTextCursor::End);
        }
        
        timeout_counter++;
        emit reconnect();
    }
    // porazka
    else {
        timeout_counter = 0;
        ui->terminal->append(tr("Próba połączenia: niepowodzenie. . ."));
    }
}

/*!
 * \brief Slot określający reakcję na wciśnięcie przycisku "Rozłącz"
 * 
 * Podejmuje próbę rozłączenia.
 */
void MainWindow::action_disconnect_click() {

    if (serial->isOpen()) {
        ui->terminal->append(tr("Rozłączanie urządzenia. . ."));
        serial->close();
    } else {
        ui->terminal->append(tr("Uwaga: Brak urządzeń do rozłączenia!")); 
    }

    flag_isConnected = false;
    device_isReady = false;
    device_firstWord = false;

    ui->action_connect->setEnabled(true);
    ui->action_disconnect->setEnabled(false);
    ui->statusBar->showMessage(tr("Status: Rozłączony"));
}

/*!
 * \brief Slot określający reakcję na wciśnięcie przycisku "Wyjdź"
 * 
 * Emituje sygnał załączający slot rozłączenia i wychodzi z programu.
 */
void MainWindow::action_exit_click() {
    debugTimer->stop();
    ui->terminal->append(tr("Wyjście. . ."));
    emit disconnect_me();   // trzeba rozlaczyc urzadzenie
    qApp->exit();
}

/*!
 * \brief Slot określający reakcję na pojawienie się danych na porcie szeregowym.
 * 
 * Rozwiązana tu jest kwestia komunikacji między urządzeniem a komputerem.
 */
void MainWindow::serial_dataAvailable() {
    if (flag_isConnected) {
        QByteArray datas = serial->readAll();
        ui->terminal->moveCursor(QTextCursor::End);
        ui->terminal->insertPlainText(datas);
        ui->terminal->moveCursor(QTextCursor::End);

        if (!device_isReady) {
            int value;
            if (!device_firstWord) {
                sscanf(datas.toStdString().c_str(), "%04X", &value);
                if (value == DEVICE_FIRST_WORD) device_firstWord = true;
                
                // proba powitania
                serial->write(DEVICE_HANDSHAKE);
            } else if (!device_isReady) {
                sscanf(datas.toStdString().c_str(), "%02X", &value);
                if (value == DEVICE_HANDSHAKE_RESPONSE) emit device_ready();
            }
        } else {

        }
    }
}

/*!
 * \brief Slot określający reakcję na pojawienie się błędu portu szeregowego.
 * 
 * Wyświetla w terminalu treść błędu.
 */
void MainWindow::serial_errorOccurred(QSerialPort::SerialPortError error) {
    char code[4];
    sprintf(code, "%d", (int)error);

    if (flag_isConnected) {
        switch (error) {
            case QSerialPort::SerialPortError::NoError:
                break;

            case QSerialPort::SerialPortError::DeviceNotFoundError:
                ui->terminal->append(tr("QSerialError: Nie znaleziono urządzenia"));
                ui->statusBar->showMessage(tr("QSerialError: Nie znaleziono urządzenia"));
                break;

            default:
                ui->terminal->append(serial->portName());
                ui->terminal->append(tr("QSerialError: Błąd "));
                ui->terminal->moveCursor(QTextCursor::End);
                ui->terminal->insertPlainText(code);
                ui->terminal->moveCursor(QTextCursor::End);
                ui->terminal->append(serial->errorString());
                ui->statusBar->showMessage(tr("QSerialError: Błąd"));
        }
        
        if (error != QSerialPort::SerialPortError::NoError) {
            flag_isConnected = false;
            ui->action_connect->setEnabled(true);
            ui->action_disconnect->setEnabled(false);
        }

    }
}

/*!
 * \brief Slot określający gotowość urządzenia do pracy.
 * 
 * Wypisuje w terminalu i na pasku stanu informację o gotowości urządzenia.
 */
void MainWindow::device_ready() {
    ui->terminal->append(tr("QSerial: Urządzenie gotowe do pracy."));
    ui->statusBar->showMessage(tr("QSerial: Urządzenie gotowe do pracy"));
    device_isReady = true;
}

/*!
 * \brief Uruchomienie testowego zbierania danych
 * 
 * Wypisuje w terminalu i na pasku stanu informacje o uruchomieniu testowego przebiegu.
 * Ignoruje wbudowane flagi -- sluzy za test parsowania ramki i wyswietlania na wykresie danych.
 */
void MainWindow::testrun_begin() {
    ui->terminal->append(tr("Testrun: Uruchomiono przebieg testowy"));
    ui->statusBar->showMessage(tr("Testrun: Uruchomiono przebieg testowy"));

    device_isReady = true;
    debug_on = true;
    
    debugTimer->start(TIMER_TIMEOUT_MS);
}

/*!
 * \brief Reakcja na timeout timera testowego
 * 
 * Generuje dane dla wszystkich mozliwych czujnikow, nastepnie parsuje je
 * i wyswietla na wykresach.
 */
void MainWindow::testrun_timeoutHandler() {

    // GENEROWANIE DANYCH
    std::string data = "";
    qsrand(qrand());

    // ilosc sensorow
    char devices[3];
    sprintf(devices, "%02X", MAX_SENSORS);
    std::string devs(devices);

    // dodaje do ramki zakodowana liczbe sensorow
    data += devs;

    // generuje i dodaje dane
    // "czujniki" zgiecia
    data += generate_data(SENSOR_TYPE_BEND, SENSOR_ID_FINGER_THUMB, random_value(SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX));
    data += generate_data(SENSOR_TYPE_BEND, SENSOR_ID_FINGER_INDEX, random_value(SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX));
    data += generate_data(SENSOR_TYPE_BEND, SENSOR_ID_FINGER_MIDDLE, random_value(SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX));
    data += generate_data(SENSOR_TYPE_BEND, SENSOR_ID_FINGER_RING, random_value(SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX));
    data += generate_data(SENSOR_TYPE_BEND, SENSOR_ID_FINGER_PINKY, random_value(SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX));

    // "czujniki" dotyku
    data += generate_data(SENSOR_TYPE_TOUCH, SENSOR_ID_FINGER_THUMB, random_value(SENSOR_RANGE_TOUCH_MIN, SENSOR_RANGE_TOUCH_MAX));
    data += generate_data(SENSOR_TYPE_TOUCH, SENSOR_ID_FINGER_INDEX, random_value(SENSOR_RANGE_TOUCH_MIN, SENSOR_RANGE_TOUCH_MAX));
    data += generate_data(SENSOR_TYPE_TOUCH, SENSOR_ID_FINGER_MIDDLE, random_value(SENSOR_RANGE_TOUCH_MIN, SENSOR_RANGE_TOUCH_MAX));
    data += generate_data(SENSOR_TYPE_TOUCH, SENSOR_ID_FINGER_RING, random_value(SENSOR_RANGE_TOUCH_MIN, SENSOR_RANGE_TOUCH_MAX));
    data += generate_data(SENSOR_TYPE_TOUCH, SENSOR_ID_FINGER_PINKY, random_value(SENSOR_RANGE_TOUCH_MIN, SENSOR_RANGE_TOUCH_MAX));

    // ------------------------------------------------

    // WCZYTYWANIE I WYSWIETLANIE DANYCH

    // czy punktow jest wiecej niz zalozony zakres
    bool full_range = (time_now > ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)));

    // (do wczytywania) liczba sensorow
    int devices_no = -1;
    sscanf(data.c_str(), "%02X", &devices_no);

    // wczytuje i parsuje po 4*4 bity z ramki
    for (int i = 0; i < MAX_SENSORS; i++) {
        parse(data.substr(2 + 4 * i, 4));
    }

    

    // weryfikuje, czy przekroczony zostal zalozony zakres na osi x
    if (full_range) { 
        graph_time.pop_front();
        graph_time.append(time_now);
        // przesuwa wykres wzdluz osi x po przekroczeniu zakresu
        ui->graph_bending->xAxis->setRange(-1.0f * ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)) + time_now, time_now);
    }
    else {
        graph_time.append(time_now);
        // skaluje zakres, poki nie zostal przekroczony
        ui->graph_bending->xAxis->setRange(0, time_now);
    }

    // laduje wczytane dane do wykresow,
    // odnosi sie do poszczegolnych danych poprzez wektor wskaznikow na wektory danych
    for (int i = 0; i < pointers_bendSensor.size(); i++)
        ui->graph_bending->graph(i)->setData(graph_time, *(pointers_bendSensor.at(i)));
    
    // rysuje wykres
    ui->graph_bending->replot();

    // czas pomiarow sie zwieksza
    time_now += (double)TIMER_TIMEOUT_MS / 1000.0f;
}

void MainWindow::parse(const std::string& dataframe_chunk) {
    int sensor_type = -1,
        sensor_id = -1,
        sensor_value = -1;

    // wczytuje dane z ramki
    sscanf(dataframe_chunk.c_str(), "%01X%01X%02X", &sensor_type, &sensor_id, &sensor_value);

    // sprawdza, czy przekroczony zostal zalozony zakres
    bool full_range = (time_now > ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)));

    // zagniezdzone switch'e:
    // najpierw sprawdza typ czujnika (bend, touch, acc)
    // nastepnie jego id (dany palec/os akc.)
    // i laduje w odpowiedni wektor
    switch(sensor_type) {
        case SENSOR_TYPE_BEND:
            switch(sensor_id) {
                case SENSOR_ID_FINGER_THUMB:
                    if (full_range) sensor_bend_01.pop_front();  
                    sensor_bend_01.append(sensor_value);
                    break;

                case SENSOR_ID_FINGER_INDEX:
                    if (full_range) sensor_bend_02.pop_front();  
                    sensor_bend_02.append(sensor_value);
                    break;

                case SENSOR_ID_FINGER_MIDDLE:
                    if (full_range) sensor_bend_03.pop_front();  
                    sensor_bend_03.append(sensor_value);
                    break;

                case SENSOR_ID_FINGER_RING:
                    if (full_range) sensor_bend_04.pop_front();  
                    sensor_bend_04.append(sensor_value);
                    break;

                case SENSOR_ID_FINGER_PINKY:
                    if (full_range) sensor_bend_05.pop_front();  
                    sensor_bend_05.append(sensor_value);
                    break;

                default:
                    exit(-1);
                    break;
            }
            break;

        case SENSOR_TYPE_TOUCH:
            switch(sensor_id) {
                case SENSOR_ID_FINGER_THUMB:
                    if (full_range) sensor_touch_01.pop_front();  
                    sensor_touch_01.append(sensor_value);
                    break;

                case SENSOR_ID_FINGER_INDEX:
                    if (full_range) sensor_touch_02.pop_front();  
                    sensor_touch_02.append(sensor_value);
                    break;

                case SENSOR_ID_FINGER_MIDDLE:
                    if (full_range) sensor_touch_03.pop_front();  
                    sensor_touch_03.append(sensor_value);
                    break;

                case SENSOR_ID_FINGER_RING:
                    if (full_range) sensor_touch_04.pop_front();  
                    sensor_touch_04.append(sensor_value);
                    break;

                case SENSOR_ID_FINGER_PINKY:
                    if (full_range) sensor_touch_05.pop_front();  
                    sensor_touch_05.append(sensor_value);
                    break;

                default:
                    exit(-1);
                    break;
            }
            break;

        case SENSOR_TYPE_ACC:
            switch(sensor_id) {
                case SENSOR_ID_ACC_XAXIS:
                    if (full_range) sensor_acc_x.pop_front();  
                    sensor_acc_x.append(sensor_value);
                    break;

                case SENSOR_ID_ACC_YAXIS:
                    if (full_range) sensor_acc_y.pop_front();  
                    sensor_acc_y.append(sensor_value);
                    break;

                default:
                    exit(-1);
                    break;
            }
            break;

        default:
            exit(-1);
            break;
    }
}
