#include "mainwindow.hh"
#include "ui_mainwindow.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);

    device_isReady = false;

    // wyswietl poczatkowy status
    ui->statusBar->showMessage(tr("Status: Rozłączony"));

    // Laczenie opcji z menu
    QObject::connect(ui->action_connect, SIGNAL(triggered()), this, SLOT(action_connect_click()));
    QObject::connect(ui->action_disconnect, SIGNAL(triggered()), this, SLOT(action_disconnect_click()));
    QObject::connect(ui->action_exit, SIGNAL(triggered()), this, SLOT(action_exit_click()));

    QObject::connect(this, SIGNAL(disconnect_me()), this, SLOT(action_disconnect_click()));

    // Laczenie reakcji na sygnaly portu szeregowego
    QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(serial_dataAvailable()));
    QObject::connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(serial_errorOccurred(QSerialPort::SerialPortError)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::action_connect_click() {
    ui->terminal->append(tr("Próba połączenia. . .\n"));

    // otwieranie ustawien polaczenia
    connectionWindow = new Connection(this);
    if (connectionWindow->exec() == QDialog::Accepted) {

        serial->setPortName(connectionWindow->ui->portName->text());

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

    flag_isConnected = true;
    ui->action_connect->setEnabled(false);
    ui->action_disconnect->setEnabled(true);

    // proba polaczenia
    serial->open(SERIAL_OPEN_MODE);
    // sukces
    if (serial->isOpen()) ui->statusBar->showMessage(tr("Status: Połączony"));

    // proba powitania
    serial->write(DEVICE_HANDSHAKE);
}

void MainWindow::action_disconnect_click() {
    
    if (serial->isOpen()) {
        ui->terminal->append(tr("Rozłączanie urządzenia. . ."));
        serial->close();
    } else {
        ui->terminal->append(tr("Uwaga: Brak urządzeń do rozłączenia!")); 
    }

    flag_isConnected = false;
    device_isReady = false;
    ui->action_connect->setEnabled(true);
    ui->action_disconnect->setEnabled(false);
    ui->statusBar->showMessage(tr("Status: Rozłączony"));
}

void MainWindow::action_exit_click() {
    ui->terminal->append(tr("Wyjście. . ."));
    emit disconnect_me();   // trzeba rozlaczyc urzadzenie
    qApp->exit();
}

void MainWindow::serial_dataAvailable() {
    if (flag_isConnected) {
        QByteArray datas = serial->readAll();
        ui->terminal->moveCursor(QTextCursor::End);
        ui->terminal->insertPlainText(datas);
        ui->terminal->moveCursor(QTextCursor::End);

        if (!device_isReady) {
            int value;
            sscanf(datas.toStdString().c_str(), "%02X", &value);
            if (value == DEVICE_HANDSHAKE_RESPONSE) emit device_ready();
        }
    }
}

void MainWindow::serial_errorOccurred(QSerialPort::SerialPortError error) {
    if (flag_isConnected) {
        switch (error) {
            case QSerialPort::SerialPortError::NoError:
                break;

            case QSerialPort::SerialPortError::DeviceNotFoundError:
                ui->terminal->append(tr("QSerialError: Nie znaleziono urządzenia"));
                ui->statusBar->showMessage(tr("QSerialError: Nie znaleziono urządzenia"));
                break;

            default:
                ui->terminal->append(tr("QSerialError: Błąd"));
                ui->statusBar->showMessage(tr("QSerialError: Błąd"));
        }
        
        if (error != QSerialPort::SerialPortError::NoError) {
            flag_isConnected = false;
            ui->action_connect->setEnabled(true);
            ui->action_disconnect->setEnabled(false);
        }

    }
}

void MainWindow::device_ready() {
    ui->terminal->append(tr("QSerial: Urządzenie gotowe do pracy."));
    ui->statusBar->showMessage(tr("QSerial: Urządzenie gotowe do pracy"));
    device_isReady = true;
}
