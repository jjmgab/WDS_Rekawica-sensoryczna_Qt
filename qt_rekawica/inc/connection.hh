#ifndef CONNECTION_HH
#define CONNECTION_HH

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>
#include "ui_connection.hh"

/*! 
 * \brief Klasa definiujaca okno ustawień połączenia.
 * 
 * Klasa modeluje pojęcie okna ustawień połączenia.
 */
class Connection : public QDialog {
    Q_OBJECT

    public:
    /*!
     * \brief Konstruktor parametryczny klasy Connection
     */
    explicit Connection(QWidget* parent = nullptr);
    /*!
     * \brief Destruktor klasy Connection
     */
    ~Connection();

    Ui::dialog_connection* ui;

    public slots:
};

#endif