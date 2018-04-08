#include "mainwindow.hh"
#include "ui_mainwindow.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);

    ui->statusBar->showMessage(tr("Status: Rozłączony"));

    QObject::connect(ui->action_connect, SIGNAL(triggered()), this, SLOT(action_connect_click()));
    QObject::connect(ui->action_disconnect, SIGNAL(triggered()), this, SLOT(action_disconnect_click()));
    QObject::connect(ui->action_exit, SIGNAL(triggered()), this, SLOT(action_exit_click()));

    QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(serial_dataAvailable()));
    QObject::connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(serial_errorOccurred(QSerialPort::SerialPortError)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::action_connect_click() {
    ui->terminal->append(tr("Próba połączenia. . ."));
    flag_isConnected = true;
    ui->action_connect->setEnabled(false);
    ui->action_disconnect->setEnabled(true);

    serial->open(SERIAL_OPEN_MODE);
}

void MainWindow::action_disconnect_click() {
    ui->terminal->append(tr("Rozłączanie urządzenia. . ."));
    flag_isConnected = false;
    ui->action_connect->setEnabled(true);
    ui->action_disconnect->setEnabled(false);

    if (serial->isOpen()) serial->close();
}

void MainWindow::action_exit_click() {
    ui->terminal->append(tr("Wyjście. . ."));
    if (serial->isOpen()) serial->close();
    qApp->exit();
}

void MainWindow::serial_dataAvailable() {
    if (flag_isConnected) {
        QByteArray datas = serial->readAll();
        ui->terminal->append(datas);
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
