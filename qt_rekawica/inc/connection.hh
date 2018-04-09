#ifndef CONNECTION_HH
#define CONNECTION_HH

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>
#include "ui_connection.hh"

class Connection : public QDialog {
    Q_OBJECT

    public:
    explicit Connection(QWidget* parent = nullptr);
    ~Connection();

    Ui::dialog_connection* ui;

    public slots:
    void accepted();

};

#endif