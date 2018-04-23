#include "connection.hh"

/*!
 * \file
 * \brief Definicja metod klasy Connection
 * 
 * Definiuje wszystkie metody klasy Connection.
 */

/*!
 * \brief Konstruktor parametryczny klasy.
 * 
 * Inicjalizuje wszystkie graficzne elementy okna
 * oraz definiuje połączenia między wykorzystywanymi sygnałami i slotami.
 */
Connection::Connection(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::dialog_connection)
    {
        ui->setupUi(this);
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        QList<QSerialPortInfo>::iterator i;
        for (i = ports.begin(); i != ports.end(); ++i)
            ui->portName->addItem(i->portName());

        QObject::connect(ui->button_ok, SIGNAL(clicked()), this, SLOT(accepted()));
    }

/*!
 * \brief Destruktor klasy Connection.
 */
Connection::~Connection() {
    delete ui;
}

/*!
 * \brief Reakcja na wciśnięcie przycisku zatwierdzenia ustawień.
 */
void Connection::accepted() {
    this->accept();
}