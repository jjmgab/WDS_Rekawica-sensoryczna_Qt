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

    device_isReady = false;
    device_firstWord = false;
    flag_isConnected = false;

    timeout_counter = 0;

    // wyswietl poczatkowy status
    ui->statusBar->showMessage(tr("Status: Rozłączony"));

    // Laczenie opcji z menu
    QObject::connect(ui->action_connect, SIGNAL(triggered()), this, SLOT(action_connect_click()));
    QObject::connect(ui->action_disconnect, SIGNAL(triggered()), this, SLOT(action_disconnect_click()));
    QObject::connect(ui->action_exit, SIGNAL(triggered()), this, SLOT(action_exit_click()));

    QObject::connect(this, SIGNAL(disconnect_me()), this, SLOT(action_disconnect_click()));
    QObject::connect(this, SIGNAL(reconnect()), this, SLOT(action_connect_click()));

    // Laczenie reakcji na sygnaly portu szeregowego
    //QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(serial_dataAvailable()));
    //QObject::connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(serial_errorOccurred(QSerialPort::SerialPortError)));

}

/*!
 * \brief Destruktor klasy MainWindow.
 */
MainWindow::~MainWindow()
{
    delete ui;
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
            } else {
                sscanf(datas.toStdString().c_str(), "%02X", &value);
                if (value == DEVICE_HANDSHAKE_RESPONSE) emit device_ready();
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
}
