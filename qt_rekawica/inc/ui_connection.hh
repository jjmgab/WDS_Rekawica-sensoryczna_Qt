/********************************************************************************
** Form generated from reading UI file 'connection.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog_connection
{
public:
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *layout_baudRate;
    QLabel *label_baudRate;
    QComboBox *baudRate;
    QHBoxLayout *layout_stopBits;
    QLabel *label_stopBits;
    QComboBox *stopBits;
    QHBoxLayout *layout_dataBits;
    QLabel *label_dataBits;
    QComboBox *dataBits;
    QHBoxLayout *layout_parity;
    QLabel *label_parity;
    QComboBox *parity;
    QHBoxLayout *layout_portName;
    QLabel *label_portName;
    QLineEdit *portName;
    QHBoxLayout *layout_flowControl;
    QLabel *label_flowControl;
    QComboBox *flowControl;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_ok;
    QPushButton *button_cancel;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *dialog_connection)
    {
        if (dialog_connection->objectName().isEmpty())
            dialog_connection->setObjectName(QStringLiteral("dialog_connection"));
        dialog_connection->resize(320, 250);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dialog_connection->sizePolicy().hasHeightForWidth());
        dialog_connection->setSizePolicy(sizePolicy);
        dialog_connection->setMinimumSize(QSize(320, 250));
        dialog_connection->setMaximumSize(QSize(320, 250));
        QIcon icon;
        icon.addFile(QStringLiteral(":/button_connect/icons/connect"), QSize(), QIcon::Normal, QIcon::Off);
        dialog_connection->setWindowIcon(icon);
        verticalLayoutWidget = new QWidget(dialog_connection);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 297, 231));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        layout_baudRate = new QHBoxLayout();
        layout_baudRate->setObjectName(QStringLiteral("layout_baudRate"));
        label_baudRate = new QLabel(verticalLayoutWidget);
        label_baudRate->setObjectName(QStringLiteral("label_baudRate"));

        layout_baudRate->addWidget(label_baudRate);

        baudRate = new QComboBox(verticalLayoutWidget);
        baudRate->setObjectName(QStringLiteral("baudRate"));

        layout_baudRate->addWidget(baudRate);


        gridLayout->addLayout(layout_baudRate, 1, 0, 1, 1);

        layout_stopBits = new QHBoxLayout();
        layout_stopBits->setObjectName(QStringLiteral("layout_stopBits"));
        label_stopBits = new QLabel(verticalLayoutWidget);
        label_stopBits->setObjectName(QStringLiteral("label_stopBits"));

        layout_stopBits->addWidget(label_stopBits);

        stopBits = new QComboBox(verticalLayoutWidget);
        stopBits->setObjectName(QStringLiteral("stopBits"));

        layout_stopBits->addWidget(stopBits);


        gridLayout->addLayout(layout_stopBits, 5, 0, 1, 1);

        layout_dataBits = new QHBoxLayout();
        layout_dataBits->setObjectName(QStringLiteral("layout_dataBits"));
        label_dataBits = new QLabel(verticalLayoutWidget);
        label_dataBits->setObjectName(QStringLiteral("label_dataBits"));

        layout_dataBits->addWidget(label_dataBits);

        dataBits = new QComboBox(verticalLayoutWidget);
        dataBits->setObjectName(QStringLiteral("dataBits"));

        layout_dataBits->addWidget(dataBits);


        gridLayout->addLayout(layout_dataBits, 3, 0, 1, 1);

        layout_parity = new QHBoxLayout();
        layout_parity->setObjectName(QStringLiteral("layout_parity"));
        label_parity = new QLabel(verticalLayoutWidget);
        label_parity->setObjectName(QStringLiteral("label_parity"));

        layout_parity->addWidget(label_parity);

        parity = new QComboBox(verticalLayoutWidget);
        parity->setObjectName(QStringLiteral("parity"));

        layout_parity->addWidget(parity);


        gridLayout->addLayout(layout_parity, 2, 0, 1, 1);

        layout_portName = new QHBoxLayout();
        layout_portName->setObjectName(QStringLiteral("layout_portName"));
        label_portName = new QLabel(verticalLayoutWidget);
        label_portName->setObjectName(QStringLiteral("label_portName"));

        layout_portName->addWidget(label_portName);

        portName = new QLineEdit(verticalLayoutWidget);
        portName->setObjectName(QStringLiteral("portName"));

        layout_portName->addWidget(portName);


        gridLayout->addLayout(layout_portName, 0, 0, 1, 1);

        layout_flowControl = new QHBoxLayout();
        layout_flowControl->setObjectName(QStringLiteral("layout_flowControl"));
        label_flowControl = new QLabel(verticalLayoutWidget);
        label_flowControl->setObjectName(QStringLiteral("label_flowControl"));

        layout_flowControl->addWidget(label_flowControl);

        flowControl = new QComboBox(verticalLayoutWidget);
        flowControl->setObjectName(QStringLiteral("flowControl"));

        layout_flowControl->addWidget(flowControl);


        gridLayout->addLayout(layout_flowControl, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        button_ok = new QPushButton(verticalLayoutWidget);
        button_ok->setObjectName(QStringLiteral("button_ok"));

        horizontalLayout->addWidget(button_ok);

        button_cancel = new QPushButton(verticalLayoutWidget);
        button_cancel->setObjectName(QStringLiteral("button_cancel"));

        horizontalLayout->addWidget(button_cancel);


        gridLayout->addLayout(horizontalLayout, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);


        retranslateUi(dialog_connection);

        QMetaObject::connectSlotsByName(dialog_connection);
    } // setupUi

    void retranslateUi(QDialog *dialog_connection)
    {
        dialog_connection->setWindowTitle(QApplication::translate("dialog_connection", "Po\305\202\304\205czenie", 0));
        label_baudRate->setText(QApplication::translate("dialog_connection", "BaudRate", 0));
        baudRate->clear();
        baudRate->insertItems(0, QStringList()
         << QApplication::translate("dialog_connection", "115200", 0)
         << QApplication::translate("dialog_connection", "9600", 0)
        );
        label_stopBits->setText(QApplication::translate("dialog_connection", "Bit stopu", 0));
        stopBits->clear();
        stopBits->insertItems(0, QStringList()
         << QApplication::translate("dialog_connection", "1", 0)
        );
        label_dataBits->setText(QApplication::translate("dialog_connection", "Data bits", 0));
        dataBits->clear();
        dataBits->insertItems(0, QStringList()
         << QApplication::translate("dialog_connection", "8", 0)
        );
        label_parity->setText(QApplication::translate("dialog_connection", "Parzysto\305\233\304\207", 0));
        parity->clear();
        parity->insertItems(0, QStringList()
         << QApplication::translate("dialog_connection", "Nieparzysty", 0)
         << QApplication::translate("dialog_connection", "Parzysty", 0)
        );
        label_portName->setText(QApplication::translate("dialog_connection", "<html><head/><body><p>Port</p></body></html>", 0));
        label_flowControl->setText(QApplication::translate("dialog_connection", "Flow control", 0));
        flowControl->clear();
        flowControl->insertItems(0, QStringList()
         << QApplication::translate("dialog_connection", "Hardware", 0)
         << QApplication::translate("dialog_connection", "Software", 0)
        );
        button_ok->setText(QApplication::translate("dialog_connection", "OK", 0));
        button_cancel->setText(QApplication::translate("dialog_connection", "Anuluj", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog_connection: public Ui_dialog_connection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONNECTION_H
