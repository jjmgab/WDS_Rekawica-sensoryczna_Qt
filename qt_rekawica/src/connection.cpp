#include "connection.hh"

Connection::Connection(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::dialog_connection)
    {
        ui->setupUi(this);

        QObject::connect(ui->button_ok, SIGNAL(clicked()), this, SLOT(accepted()));
    }

Connection::~Connection() {
    delete ui;
}

void Connection::accepted() {
    if (ui->portName->text() != QString("")) {
        this->accept();
    }
}