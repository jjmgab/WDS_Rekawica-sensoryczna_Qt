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

    // customowe tooltipy
    // App->setStyleSheet("QToolTip { color: #000000 ; background-color: #ffffff; border: none; }");

    // -- Zaladowanie obrazka orientacji
    // laduje obrazek ze sciezki qrc z prefixem images oraz aliasem img_orientation
    QPixmap pixmap_orientation(":/images/img_orientation");
    // do zmiennej dodaje scene
    scene_orientation->addPixmap(pixmap_orientation);
    // ustawia przezroczyste tlo sceny
    QPalette palette = ui->graphics_handOrientation->palette();
    palette.setColor(ui->graphics_handOrientation->backgroundRole(), QColor(0, 0, 0, 0));
    ui->graphics_handOrientation->setPalette(palette);
    // ustawia oraz wyswietla scene w QGraphicsview
    ui->graphics_handOrientation->setScene(scene_orientation);
    ui->graphics_handOrientation->show();


    // resetuje wizualizacje ręki do zera przed wczytaniem nowego stanu do sceny - w tym przypadku wczyta
    reset_hand_visualisation_scene();
    ui->graphics_handVisualization->show();


    connectionWindow = nullptr;

    device_isReady = false;
    device_firstWord = false;
    flag_isConnected = false;

    time_now = 0.0f;

    // ładowanie scen do wizualizacji zgięcia
    

    // wskazniki na czujniki zgiecia
    pointers_bendSensor.append(&sensor_bend_01);
    pointers_bendSensor.append(&sensor_bend_02);
    pointers_bendSensor.append(&sensor_bend_03);
    pointers_bendSensor.append(&sensor_bend_04);
    pointers_bendSensor.append(&sensor_bend_05);

    // wskazniki na czujniki dotyku
    pointers_touchSensor.append(&sensor_touch_01);
    pointers_touchSensor.append(&sensor_touch_02);
    pointers_touchSensor.append(&sensor_touch_03);
    pointers_touchSensor.append(&sensor_touch_04);
    pointers_touchSensor.append(&sensor_touch_05);

    //wskazniki na osie akcelereometru
    pointers_accSensor.append(&sensor_acc_x);
    pointers_accSensor.append(&sensor_acc_z);

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
    //qsrand(qrand());

    // KONFIGURACJA WYKRESOW
    QPen p_thumb,
         p_index,
         p_middle,
         p_ring,
         p_pinky,
         ACC_x,
         ACC_z;

    // kolory na palcach (dotyk i zgiecie)
    p_thumb.setColor(Qt::black);
    p_index.setColor(Qt::red);
    p_middle.setColor(Qt::blue);
    p_ring.setColor(Qt::green);
    p_pinky.setColor(Qt::magenta);

    // kolory akcelerometr
    ACC_x.setColor(Qt::black);
    ACC_z.setColor(Qt::red);

    pens.append(p_thumb);
    pens.append(p_index);
    pens.append(p_middle);
    pens.append(p_ring);
    pens.append(p_pinky);

    pens_ACC.append(ACC_x);
    pens_ACC.append(ACC_z);


    // ustawienia wykresu wygiecia
    ui->graph_bending->yAxis->setRange(SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX);
    ui->graph_bending->xAxis->setLabel(tr("Czas pomiaru [s]"));
    ui->graph_bending->yAxis->setLabel(tr("Wart. zgięcia"));
    ui->graph_bending->setBackground(QBrush(Qt::white));
    ui->graph_bending->setInteraction(QCP::iSelectPlottables, true);
    ui->graph_bending->setInteraction(QCP::iRangeDrag, true);
    ui->graph_bending->setInteraction(QCP::iRangeZoom, true);

    for (int i = 0; i < MAX_SENSORS_BEND; i++) {
        ui->graph_bending->addGraph();
        ui->graph_bending->graph(i)->setPen(pens.at(i));
    }

    // ustawienia wykresu dotyku
    ui->graph_touch->yAxis->setRange(SENSOR_RANGE_TOUCH_MIN, SENSOR_RANGE_TOUCH_MAX);
    ui->graph_touch->xAxis->setLabel(tr("Czas pomiaru [s]"));
    ui->graph_touch->yAxis->setLabel(tr("Siła dotyku"));
    ui->graph_touch->setBackground(QBrush(Qt::white));
    // ustaw ze mozna wybierac krzywe
    ui->graph_touch->setInteraction(QCP::iSelectPlottables, true);
    // ustawe ze mozna przesuwac wykres
    ui->graph_touch->setInteraction(QCP::iRangeDrag, true);
    // ui->graph_touch->axisRects().at(0)->setRangeDrag(Qt::Horizontal); // przesuwanie tylko w poziomie
    // ustaw ze mozna zmieniac przyblizenie
    ui->graph_touch->setInteraction(QCP::iRangeZoom, true);

    for (int i = 0; i < MAX_SENSORS_TOUCH; i++) {
        ui->graph_touch->addGraph();
        ui->graph_touch->graph(i)->setPen(pens.at(i));
    }

    // ustawienia wykresu akcelerometru
    ui->graph_orientation->yAxis->setRange(SENSOR_RANGE_ACC_MIN, SENSOR_RANGE_ACC_MAX);
    ui->graph_orientation->xAxis->setLabel(tr("Czas pomiaru [s]"));
    ui->graph_orientation->yAxis->setLabel(tr("Wartości wsp. ACC"));
    ui->graph_orientation->setBackground(QBrush(Qt::white));
    ui->graph_orientation->setInteraction(QCP::iSelectPlottables, true);
    ui->graph_orientation->setInteraction(QCP::iRangeDrag, true);
    ui->graph_orientation->setInteraction(QCP::iRangeZoom, true);

    for (int i = 0; i < MAX_AXIS_ACC; i++) {
        ui->graph_orientation->addGraph();
        ui->graph_orientation->graph(i)->setPen(pens_ACC.at(i));
    }

    ui->graph_orientation->graph(0)->setName("Wart. osi x");
    ui->graph_orientation->graph(1)->setName("Wart. osi z");
    ui->graph_orientation->legend->setVisible(true);

    QObject::connect(ui->action_testrun, SIGNAL(triggered()), this, SLOT(testrun()));
    QObject::connect(debugTimer, SIGNAL(timeout()), this, SLOT(testrun_timeoutHandler()));

    QObject::connect(ui->graphics_finger_5, SIGNAL(clicked()), this, SLOT(vibrate_pinky()));
    QObject::connect(this, SIGNAL(test_vibrate_pinky()), this, SLOT(vibrate_pinky()));

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
    
    std::cout << "~scenes" << std::endl;
    if (scene_visualisation != nullptr) delete scene_visualisation;
    if (scene_orientation != nullptr) delete scene_orientation;

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
     // musi być static przez to że akcja reconnect wywołuje action_connect
    static bool status;        

    // aby sprawdzic czy jest to proba polaczenia czy tez nowe polaczenie oraz do logow, static bo akcja reconnect wywoluje funkcje ponownie 
    static int timeout_counter = 0; 

    device_finished = false;

    // otwieranie ustawien polaczenia
    connectionWindow = new Connection(this);
    if ( timeout_counter == 0 ) status = connectionWindow->exec();
    // Aby nie probowalo laczyc jezeli uzytkownik nie zaakceptuje danych
    if (status) {
        // Aby nie mozna bylo wywolywac ponownie polaczenia kiedy jedno juz jest w trakcie
        ui->action_connect->setEnabled(false); 
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
        
        // proba polaczenia
        serial->open(SERIAL_OPEN_MODE);
        // sukces
        if (serial->isOpen()) {
            flag_isConnected = true;
            ui->action_disconnect->setEnabled(true);
            ui->statusBar->showMessage(tr("Status: Połączony"));
        }
        // ponawianie polaczenia
        else if (timeout_counter < MAX_CONNECTION_TRIES) {

            timeout_counter++;
            ui->terminal->append(tr("Próba połączenia nr ") + QString::number(timeout_counter) + " ");
            for (int i = 0; i < RECONNECT_SECONDS; i++) {
                delay_seconds(1);
                ui->terminal->moveCursor(QTextCursor::End);
                ui->terminal->insertPlainText(". ");
                ui->terminal->moveCursor(QTextCursor::End);
            }
            std::cout << "RECONNECT" << std::endl;
            emit reconnect();
        }
        // porazka
        else {
            timeout_counter = 0;
            ui->action_connect->setEnabled(true);
            ui->terminal->append(tr("Próba połączenia: niepowodzenie"));
            ui->statusBar->showMessage(tr("Status: Nie udalo się połączyć"));
            std::cout << "CONNECTION FAILURE" << std::endl;
        }
    }
    std::cout << "DELETE CONNECTION WINDOW..." << std::endl;
    delete connectionWindow;
    connectionWindow = nullptr;
    std::cout << "DELETED" << std::endl;
}

/*!
 * \brief Slot określający reakcję na wciśnięcie przycisku "Rozłącz"
 * 
 * Podejmuje próbę rozłączenia.
 */
void MainWindow::action_disconnect_click() {
    
    int disconnect_try = 0;

    if (serial->isOpen()) {
        ui->terminal->append(tr("Rozłączanie urządzenia. . ."));

        while (!device_finished) {
            if (serial->isOpen() && device_isReady)
                ui->terminal->append(tr("Próba rozłączenia nr ") + QString::number(disconnect_try) + QString("\n"));
                serial->write(DEVICE_STOP);
                delay_seconds(1);
                disconnect_try++;
        }

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
        
        int value;

        if (!device_isReady) {
            if (!device_firstWord) {
                std::cout << "DEVICE FIRST WORD" << std::endl;
                sscanf(datas.toStdString().c_str(), "%04X", &value);
                if (value == DEVICE_FIRST_WORD) device_firstWord = true;
                
                // proba powitania
                std::cout << "DEVICE HANDSHAKE" << std::endl;
                serial->write(DEVICE_HANDSHAKE);

            } else if (!device_isReady) {
                std::cout << "DEVICE READY" << std::endl;
                sscanf(datas.toStdString().c_str(), "%02X", &value);
                if (value == DEVICE_HANDSHAKE_RESPONSE) emit device_ready();
            }
        } else if (device_isReady && datas.size() > 0) {
            sscanf(datas.toStdString().c_str(), "%02X", &value);
            if (value == DEVICE_STOP_RESPONSE) {
                std::cout << "STOPPING" << std::endl;
                device_finished = true;
            }
            else if (value != DEVICE_START_RESPONSE && (value & 0xF0) != DEVICE_VIBRATE) {
                handle_data(datas.toStdString());
            }
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
    std::cout << "DEVICE READY" << std::endl;
    serial->write(DEVICE_START);
}

/*!
 * \brief Uruchomienie testowego zbierania danych
 * 
 * Wypisuje w terminalu i na pasku stanu informacje o uruchomieniu testowego przebiegu.
 * Ignoruje wbudowane flagi -- sluzy za test parsowania ramki i wyswietlania na wykresie danych.
 */
void MainWindow::testrun() {
    if (!debug_on)                              // jezeli debug == false
    {
        device_isReady = true;
        debug_on = true;
        // zablokowanie przyciskow aby nie mozna bylo wejsc w okna podczas testrun
        ui->action_connect->setEnabled(false);
        ui->action_info->setEnabled(false);
    
        debugTimer->start(TIMER_TIMEOUT_MS);
        ui->terminal->append(tr("Testrun: Uruchomiono przebieg testowy"));
        ui->statusBar->showMessage(tr("Testrun: Uruchomiono przebieg testowy"));

    } else {
        device_isReady = false;
        debug_on = false;

        reset_hand_visualisation_scene();       // aby po zatrzymaniu przebiegu testowego wylaczyla sie wizualizacja na dloni
        ui->progressBar_finger_1->setValue(0);  // Wyzerowujemy progress bary wskazujace sile dotyku po rozlaczeniu (zatrzymaniu testu)
        ui->progressBar_finger_2->setValue(0);
        ui->progressBar_finger_3->setValue(0);
        ui->progressBar_finger_4->setValue(0);
        ui->progressBar_finger_5->setValue(0);
        debugTimer->stop();
        // zablokowanie przyciskow po wyjsciu z testrun
        ui->action_connect->setEnabled(true);
        ui->action_info->setEnabled(true);
        ui->terminal->append(tr("Testrun: Zatrzymano przebieg testowy"));
        ui->statusBar->showMessage(tr("Testrun: Zatrzymano przebieg testowy"));
    }
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
    //qsrand(qrand());

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

    // akcelerometr osie
    data += generate_data(SENSOR_TYPE_ACC, SENSOR_ID_ACC_XAXIS, random_value(SENSOR_RANGE_ACC_MIN, SENSOR_RANGE_ACC_MAX));
    data += generate_data(SENSOR_TYPE_ACC, SENSOR_ID_ACC_ZAXIS, random_value(SENSOR_RANGE_ACC_MIN, SENSOR_RANGE_ACC_MAX));

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
        ui->graph_touch->xAxis->setRange(-1.0f * ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)) + time_now, time_now);
        ui->graph_orientation->xAxis->setRange(-1.0f * ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)) + time_now, time_now);
    }
    else {
        graph_time.append(time_now);
        // skaluje zakres, poki nie zostal przekroczony
        ui->graph_bending->xAxis->setRange(0, time_now);
        ui->graph_touch->xAxis->setRange(0, time_now);
        ui->graph_orientation->xAxis->setRange(0, time_now);
    }

    // resetuje scene aby moc przyjac nowe dane
    reset_hand_visualisation_scene();

    // inicjalizacja wizualizacji wartosciami "zielonymi", numery grafik i prefix zdefiniowany w pliku qrc
    for (int i = 0; i < MAX_SENSORS_BEND; i++){
        QPixmap pixmap_element(":/visualisation_element_static_bend/" + QString::number(i)); //-1 bo indexy od 0
        scene_visualisation->addPixmap(pixmap_element);
    }

    for (int i = 0; i < MAX_SENSORS_TOUCH; i++){
        QPixmap pixmap_element(":/visualisation_element_static_touch/" + QString::number(i)); //-1 bo indexy od 0
        scene_visualisation->addPixmap(pixmap_element);
    }

    // laduje wczytane dane do wykresow oraz wizualizacji
    // odnosi sie do poszczegolnych danych poprzez wektor wskaznikow na wektory danych
    for (int i = 0; i < pointers_bendSensor.size(); i++) {
        ui->graph_bending->graph(i)->setData(graph_time, *(pointers_bendSensor.at(i)));
        set_hand_visualisation_scene(SENSOR_TYPE_BEND, i+1, pointers_bendSensor.at(i)->at(pointers_bendSensor.at(i)->size()-1)); //i+1 bo indexy define od 1
    }

    // wyswietla wczytane dane na wykresach, wizualizacjach, progress barach
    // odnosi sie do najnowszej danej w wektorze danych z ktorych korzystaja wykresy
    for (int i = 0; i < pointers_touchSensor.size(); i++) 
    {
        ui->graph_touch->graph(i)->setData(graph_time, *(pointers_touchSensor.at(i)));
        set_hand_visualisation_scene(SENSOR_TYPE_TOUCH, i+1, pointers_touchSensor.at(i)->at(pointers_touchSensor.at(i)->size()-1)); //i+1 bo indexy define od 1
        switch (i) 
        {
            case 0:
                ui->progressBar_finger_1->setValue(convert_touch_value(sensor_touch_01.at(sensor_touch_01.size()-1)));
                break;
            
            case 1:
                ui->progressBar_finger_2->setValue(convert_touch_value(sensor_touch_02.at(sensor_touch_02.size()-1)));
                break;
            
            case 2:
                ui->progressBar_finger_3->setValue(convert_touch_value(sensor_touch_03.at(sensor_touch_03.size()-1)));
                break;
            
            case 3:
                ui->progressBar_finger_4->setValue(convert_touch_value(sensor_touch_04.at(sensor_touch_04.size()-1)));
                break;

            case 4:
                ui->progressBar_finger_5->setValue(convert_touch_value(sensor_touch_05.at(sensor_touch_05.size()-1)));
                break;
        }
    }

    // laduje wczytane dane do wykresow,
    // odnosi sie do poszczegolnych danych poprzez wektor wskaznikow na wektory danych
    for (int i = 0; i < pointers_accSensor.size(); i++)
        ui->graph_orientation->graph(i)->setData(graph_time, *(pointers_accSensor.at(i)));

    QString value;
    value = (QString::number(sensor_acc_x.at(sensor_acc_x.size()-1))).rightJustified(3, '0'); // rightJustified odnosi się do zer a nie całego tesktu
    ui->value_orientationX->setText(value);                                                   // wyświetlanie jest dopiero tutaj
    value = (QString::number(sensor_acc_z.at(sensor_acc_z.size()-1))).rightJustified(3, '0');
    ui->value_orientationZ->setText(value);

    
    // rysuje wykres
    ui->graph_bending->replot();
    ui->graph_touch->replot();
    ui->graph_orientation->replot();

    // rysuje wizualizacje
    ui->graphics_handVisualization->setScene(scene_visualisation);
    ui->graphics_handVisualization->show();

    // czas pomiarow sie zwieksza
    time_now += (double)TIMER_TIMEOUT_MS / 1000.0f;
}

void MainWindow::handle_data(const std::string& _data) {
    // WCZYTYWANIE I WYSWIETLANIE DANYCH

    // czy punktow jest wiecej niz zalozony zakres
    bool full_range = (time_now > ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)));

    // (do wczytywania) liczba sensorow
    int devices_no = -1;
    sscanf(_data.c_str(), "%02X", &devices_no);

    // wczytuje i parsuje po 4*4 bity z ramki
    for (int i = 0; i < MAX_SENSORS; i++) {
        parse(_data.substr(2 + 4 * i, 4));
    }

    // weryfikuje, czy przekroczony zostal zalozony zakres na osi x
    if (full_range) { 
        graph_time.pop_front();
        graph_time.append(time_now);
        // przesuwa wykres wzdluz osi x po przekroczeniu zakresu
        ui->graph_bending->xAxis->setRange(-1.0f * ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)) + time_now, time_now);
        ui->graph_touch->xAxis->setRange(-1.0f * ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)) + time_now, time_now);
        ui->graph_orientation->xAxis->setRange(-1.0f * ((double) X_RANGE_POINTS / (1000.0f / (double) TIMER_TIMEOUT_MS)) + time_now, time_now);
    }
    else {
        graph_time.append(time_now);
        // skaluje zakres, poki nie zostal przekroczony
        ui->graph_bending->xAxis->setRange(0, time_now);
        ui->graph_touch->xAxis->setRange(0, time_now);
        ui->graph_orientation->xAxis->setRange(0, time_now);
    }

    // resetuje scene aby moc przyjac nowe dane
    reset_hand_visualisation_scene();

    // inicjalizacja wizualizacji wartosciami "zielonymi", numery grafik i prefix zdefiniowany w pliku qrc
    for (int i = 0; i < MAX_SENSORS_BEND; i++){
        QPixmap pixmap_element(":/visualisation_element_static_bend/" + QString::number(i)); //-1 bo indexy od 0
        scene_visualisation->addPixmap(pixmap_element);
    }

    for (int i = 0; i < MAX_SENSORS_TOUCH; i++){
        QPixmap pixmap_element(":/visualisation_element_static_touch/" + QString::number(i)); //-1 bo indexy od 0
        scene_visualisation->addPixmap(pixmap_element);
    }

    // laduje wczytane dane do wykresow oraz wizualizacji
    // odnosi sie do poszczegolnych danych poprzez wektor wskaznikow na wektory danych
    for (int i = 0; i < pointers_bendSensor.size(); i++) {
        ui->graph_bending->graph(i)->setData(graph_time, *(pointers_bendSensor.at(i)));
        set_hand_visualisation_scene(SENSOR_TYPE_BEND, i+1, pointers_bendSensor.at(i)->at(pointers_bendSensor.at(i)->size()-1)); //i+1 bo indexy define od 1
    }

    // wyswietla wczytane dane na wykresach, wizualizacjach, progress barach
    // odnosi sie do najnowszej danej w wektorze danych z ktorych korzystaja wykresy
    for (int i = 0; i < pointers_touchSensor.size(); i++) 
    {
        ui->graph_touch->graph(i)->setData(graph_time, *(pointers_touchSensor.at(i)));
        set_hand_visualisation_scene(SENSOR_TYPE_TOUCH, i+1, pointers_touchSensor.at(i)->at(pointers_touchSensor.at(i)->size()-1)); //i+1 bo indexy define od 1
        switch (i) 
        {
            case 0:
                ui->progressBar_finger_1->setValue(convert_touch_value(sensor_touch_01.at(sensor_touch_01.size()-1)));
                break;
            
            case 1:
                ui->progressBar_finger_2->setValue(convert_touch_value(sensor_touch_02.at(sensor_touch_02.size()-1)));
                break;
            
            case 2:
                ui->progressBar_finger_3->setValue(convert_touch_value(sensor_touch_03.at(sensor_touch_03.size()-1)));
                break;
            
            case 3:
                ui->progressBar_finger_4->setValue(convert_touch_value(sensor_touch_04.at(sensor_touch_04.size()-1)));
                break;

            case 4:
                ui->progressBar_finger_5->setValue(convert_touch_value(sensor_touch_05.at(sensor_touch_05.size()-1)));
                break;
        }
    }

    // laduje wczytane dane do wykresow,
    // odnosi sie do poszczegolnych danych poprzez wektor wskaznikow na wektory danych
    for (int i = 0; i < pointers_accSensor.size(); i++)
        ui->graph_orientation->graph(i)->setData(graph_time, *(pointers_accSensor.at(i)));

    QString value;
    value = (QString::number(sensor_acc_x.at(sensor_acc_x.size()-1))).rightJustified(3, '0'); // rightJustified odnosi się do zer a nie całego tesktu
    ui->value_orientationX->setText(value);                                                   // wyświetlanie jest dopiero tutaj
    value = (QString::number(sensor_acc_z.at(sensor_acc_z.size()-1))).rightJustified(3, '0');
    ui->value_orientationZ->setText(value);

    
    // rysuje wykres
    ui->graph_bending->replot();
    ui->graph_touch->replot();
    ui->graph_orientation->replot();

    // rysuje wizualizacje
    ui->graphics_handVisualization->setScene(scene_visualisation);
    ui->graphics_handVisualization->show();

    // czas pomiarow sie zwieksza
    time_now += (double)TIMER_TIMEOUT_MS / 1000.0f;
}

/*!
* \brief Przelicza wartosci 8 bitowe na wartosci procentowe
* 
* \param[in] wartosc 8 bitowa
* \param[out] wartosc procentowa 0-100% double
*/
double MainWindow::convert_touch_value(double touch_value)
{
    return map(touch_value, SENSOR_RANGE_TOUCH_MIN, SENSOR_RANGE_TOUCH_MAX, BAR_PERCENTAGE_MIN, BAR_PERCENTAGE_MAX);
}

/*!
* \brief Ustawia scene wizualizacji
*
* \param[in] int typ sensora (1-2)
* \param[in] int id palca (1-5)
* \param[in] int wartosc chwili obecnej (0-255)
*/
void MainWindow::set_hand_visualisation_scene(int sensor_type, int sensor_id, int sensor_value)
{
    if (sensor_type == SENSOR_TYPE_BEND) {
        // Konstruktor QPixmap ze sciezka qrc
        QPixmap pixmap_element(":/visualisation_element_bend/" + QString::number(sensor_id-1));
        // nowy Qpixmap z takim samym wymiarem
        QPixmap result(pixmap_element.size());
        // ustawienie przezroczystosci nowego QPixmap
        result.fill(Qt::transparent);
        // Utworzenie obiektu QPainter ktory pozwoli nam zmienic obrazek
        QPainter painter;
        // - - "Startujemy" paintera z obrazkiem result (pustka)
        painter.begin(&result);
        // Ustawiamy przezroczystosc wszystkich pikseli na zalezna od wartosci przeliczana za pomoca funkcji map
        painter.setOpacity(map(sensor_value, SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX, 0.0, 1.0));
        // Bierzemy i od pozycji 0, 0 kopiujemy nasz obrazek (na warstwe przezroczystosci)
        painter.drawPixmap(0, 0, pixmap_element);
        // - - "Kończymy" paintera 
        painter.end();
        // dodajemy na scene nasz nowy obrazek
        scene_visualisation->addPixmap(result);
    }

    if (sensor_type == SENSOR_TYPE_TOUCH) {
        QPixmap pixmap_element(":/visualisation_element_touch/" + QString::number(sensor_id-1));
        QPixmap result(pixmap_element.size());
        result.fill(Qt::transparent);
        QPainter painter;
        painter.begin(&result);
        painter.setOpacity(map(sensor_value, SENSOR_RANGE_BEND_MIN, SENSOR_RANGE_BEND_MAX, 0.0, 1.0));
        painter.drawPixmap(0, 0, pixmap_element);
        painter.end();
        scene_visualisation->addPixmap(result);
    }

    // ustawiamy nasza scene na QGraphicsView, teraz wystarszy wyswietlic za pomoca show()
    ui->graphics_handVisualization->setScene(scene_visualisation);
}

/*!
* \brief Resetuje wizualizacje do stanu niepodlaczonego
*/
void MainWindow::reset_hand_visualisation_scene()
{
    delete scene_visualisation;
    scene_visualisation = new QGraphicsScene;

    QPixmap pixmap_visualisation(":/images/img_bg_visualisation");
    // do zmiennej dodaje scene
    scene_visualisation->addPixmap(pixmap_visualisation);
    // ustawia przezroczyste tlo sceny
    QPalette palette = ui->graphics_handVisualization->palette();
    palette.setColor(ui->graphics_handVisualization->backgroundRole(), QColor(0, 0, 0, 0));
    ui->graphics_handVisualization->setPalette(palette);
    // ustawia oraz wyswietla scene w QGraphicsview
    ui->graphics_handVisualization->setScene(scene_visualisation);
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

                case SENSOR_ID_ACC_ZAXIS:
                    if (full_range) sensor_acc_z.pop_front();  
                    sensor_acc_z.append(sensor_value);
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

void MainWindow::vibrate_pinky() {

    if (device_isReady) {
        char vibr[4];
        sprintf(vibr, "%02X\n", DEVICE_VIBRATE|SENSOR_ID_FINGER_PINKY);
        ui->terminal->append(tr("Wibracje, palec mały\n"));
        if (serial->isWritable() && serial->isOpen()) 
            serial->write(vibr);
    }
}