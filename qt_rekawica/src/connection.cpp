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

        QDialog::connect(ui->button_ok, SIGNAL(clicked()), this, SLOT(accept()));
        QDialog::connect(ui->button_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }

/*!
 * \brief Destruktor klasy Connection.
 */
Connection::~Connection() {
    delete ui;
}