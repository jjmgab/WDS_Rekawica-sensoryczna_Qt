#include "connection.hh"

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

Connection::~Connection() {
    delete ui;
}

void Connection::accepted() {
    //if (ui->portName->text() != QString("")) {
        this->accept();
    //}
}