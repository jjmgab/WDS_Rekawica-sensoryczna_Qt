/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_connect;
    QAction *action_disconnect;
    QAction *action_exit;
    QAction *action_info;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *layout_handVisualization;
    QGraphicsView *graphics_handVisualization;
    QFrame *line_vertical_1;
    QVBoxLayout *layout_mainInfo;
    QHBoxLayout *layout_orientation;
    QGraphicsView *graphics_handOrientation;
    QFrame *line_vertical_2;
    QHBoxLayout *layout_orientation_dataView;
    QVBoxLayout *layout_orientation_dataView_labels;
    QLabel *label_orientationX;
    QLabel *label_orientationY;
    QVBoxLayout *layout_orientation_dataView_values;
    QLabel *value_orientationX;
    QLabel *value_orientationY;
    QSpacerItem *horizontalSpacer_1;
    QVBoxLayout *layout_touchVisualization;
    QFrame *line_horizontal_1;
    QHBoxLayout *layout_touchVisualization_graphics;
    QGraphicsView *graphics_finger_1;
    QFrame *line_vertical_3;
    QGraphicsView *graphics_finger_2;
    QFrame *line_vertical_4;
    QGraphicsView *graphics_finger_3;
    QFrame *line_vertical_5;
    QGraphicsView *graphics_finger_4;
    QFrame *line_vertical_6;
    QGraphicsView *graphics_finger_5;
    QHBoxLayout *layout_touchVisualization_progressBars;
    QProgressBar *progressBar_finger_1;
    QFrame *line_vertical_7;
    QProgressBar *progressBar_finger_2;
    QFrame *line_vertical_8;
    QProgressBar *progressBar_finger_3;
    QFrame *line_vertical_9;
    QProgressBar *progressBar_finger_4;
    QFrame *line_vertical_10;
    QProgressBar *progressBar_finger_5;
    QFrame *line_horizontal_2;
    QTextEdit *terminal;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(860, 508);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(860, 508));
        MainWindow->setMaximumSize(QSize(860, 508));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        action_connect = new QAction(MainWindow);
        action_connect->setObjectName(QStringLiteral("action_connect"));
        action_connect->setCheckable(false);
        QIcon icon;
        QString iconThemeName = QStringLiteral("main");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral(":/button_connect/icons/connect"), QSize(), QIcon::Normal, QIcon::Off);
        }
        action_connect->setIcon(icon);
        action_disconnect = new QAction(MainWindow);
        action_disconnect->setObjectName(QStringLiteral("action_disconnect"));
        action_disconnect->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/button_disconnect/icons/disconnect"), QSize(), QIcon::Normal, QIcon::Off);
        action_disconnect->setIcon(icon1);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/button_exit/icons/exit"), QSize(), QIcon::Normal, QIcon::Off);
        action_exit->setIcon(icon2);
        action_info = new QAction(MainWindow);
        action_info->setObjectName(QStringLiteral("action_info"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/button_about/icons/about"), QSize(), QIcon::Normal, QIcon::Off);
        action_info->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setSizeIncrement(QSize(0, 0));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        layout_handVisualization = new QHBoxLayout();
        layout_handVisualization->setSpacing(6);
        layout_handVisualization->setObjectName(QStringLiteral("layout_handVisualization"));
        graphics_handVisualization = new QGraphicsView(centralWidget);
        graphics_handVisualization->setObjectName(QStringLiteral("graphics_handVisualization"));
        graphics_handVisualization->setMinimumSize(QSize(240, 400));

        layout_handVisualization->addWidget(graphics_handVisualization);

        line_vertical_1 = new QFrame(centralWidget);
        line_vertical_1->setObjectName(QStringLiteral("line_vertical_1"));
        line_vertical_1->setFrameShape(QFrame::VLine);
        line_vertical_1->setFrameShadow(QFrame::Sunken);

        layout_handVisualization->addWidget(line_vertical_1);


        gridLayout->addLayout(layout_handVisualization, 0, 0, 1, 1);

        layout_mainInfo = new QVBoxLayout();
        layout_mainInfo->setSpacing(6);
        layout_mainInfo->setObjectName(QStringLiteral("layout_mainInfo"));
        layout_orientation = new QHBoxLayout();
        layout_orientation->setSpacing(6);
        layout_orientation->setObjectName(QStringLiteral("layout_orientation"));
        graphics_handOrientation = new QGraphicsView(centralWidget);
        graphics_handOrientation->setObjectName(QStringLiteral("graphics_handOrientation"));
        graphics_handOrientation->setMinimumSize(QSize(170, 110));

        layout_orientation->addWidget(graphics_handOrientation);

        line_vertical_2 = new QFrame(centralWidget);
        line_vertical_2->setObjectName(QStringLiteral("line_vertical_2"));
        line_vertical_2->setFrameShape(QFrame::VLine);
        line_vertical_2->setFrameShadow(QFrame::Sunken);

        layout_orientation->addWidget(line_vertical_2);

        layout_orientation_dataView = new QHBoxLayout();
        layout_orientation_dataView->setSpacing(6);
        layout_orientation_dataView->setObjectName(QStringLiteral("layout_orientation_dataView"));
        layout_orientation_dataView_labels = new QVBoxLayout();
        layout_orientation_dataView_labels->setSpacing(6);
        layout_orientation_dataView_labels->setObjectName(QStringLiteral("layout_orientation_dataView_labels"));
        label_orientationX = new QLabel(centralWidget);
        label_orientationX->setObjectName(QStringLiteral("label_orientationX"));

        layout_orientation_dataView_labels->addWidget(label_orientationX);

        label_orientationY = new QLabel(centralWidget);
        label_orientationY->setObjectName(QStringLiteral("label_orientationY"));

        layout_orientation_dataView_labels->addWidget(label_orientationY);


        layout_orientation_dataView->addLayout(layout_orientation_dataView_labels);

        layout_orientation_dataView_values = new QVBoxLayout();
        layout_orientation_dataView_values->setSpacing(6);
        layout_orientation_dataView_values->setObjectName(QStringLiteral("layout_orientation_dataView_values"));
        layout_orientation_dataView_values->setContentsMargins(-1, -1, 10, -1);
        value_orientationX = new QLabel(centralWidget);
        value_orientationX->setObjectName(QStringLiteral("value_orientationX"));

        layout_orientation_dataView_values->addWidget(value_orientationX);

        value_orientationY = new QLabel(centralWidget);
        value_orientationY->setObjectName(QStringLiteral("value_orientationY"));

        layout_orientation_dataView_values->addWidget(value_orientationY);


        layout_orientation_dataView->addLayout(layout_orientation_dataView_values);


        layout_orientation->addLayout(layout_orientation_dataView);

        horizontalSpacer_1 = new QSpacerItem(320, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        layout_orientation->addItem(horizontalSpacer_1);


        layout_mainInfo->addLayout(layout_orientation);

        layout_touchVisualization = new QVBoxLayout();
        layout_touchVisualization->setSpacing(6);
        layout_touchVisualization->setObjectName(QStringLiteral("layout_touchVisualization"));
        line_horizontal_1 = new QFrame(centralWidget);
        line_horizontal_1->setObjectName(QStringLiteral("line_horizontal_1"));
        line_horizontal_1->setFrameShape(QFrame::HLine);
        line_horizontal_1->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization->addWidget(line_horizontal_1);

        layout_touchVisualization_graphics = new QHBoxLayout();
        layout_touchVisualization_graphics->setSpacing(6);
        layout_touchVisualization_graphics->setObjectName(QStringLiteral("layout_touchVisualization_graphics"));
        graphics_finger_1 = new QGraphicsView(centralWidget);
        graphics_finger_1->setObjectName(QStringLiteral("graphics_finger_1"));

        layout_touchVisualization_graphics->addWidget(graphics_finger_1);

        line_vertical_3 = new QFrame(centralWidget);
        line_vertical_3->setObjectName(QStringLiteral("line_vertical_3"));
        line_vertical_3->setFrameShape(QFrame::VLine);
        line_vertical_3->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_graphics->addWidget(line_vertical_3);

        graphics_finger_2 = new QGraphicsView(centralWidget);
        graphics_finger_2->setObjectName(QStringLiteral("graphics_finger_2"));

        layout_touchVisualization_graphics->addWidget(graphics_finger_2);

        line_vertical_4 = new QFrame(centralWidget);
        line_vertical_4->setObjectName(QStringLiteral("line_vertical_4"));
        line_vertical_4->setFrameShape(QFrame::VLine);
        line_vertical_4->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_graphics->addWidget(line_vertical_4);

        graphics_finger_3 = new QGraphicsView(centralWidget);
        graphics_finger_3->setObjectName(QStringLiteral("graphics_finger_3"));

        layout_touchVisualization_graphics->addWidget(graphics_finger_3);

        line_vertical_5 = new QFrame(centralWidget);
        line_vertical_5->setObjectName(QStringLiteral("line_vertical_5"));
        line_vertical_5->setFrameShape(QFrame::VLine);
        line_vertical_5->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_graphics->addWidget(line_vertical_5);

        graphics_finger_4 = new QGraphicsView(centralWidget);
        graphics_finger_4->setObjectName(QStringLiteral("graphics_finger_4"));

        layout_touchVisualization_graphics->addWidget(graphics_finger_4);

        line_vertical_6 = new QFrame(centralWidget);
        line_vertical_6->setObjectName(QStringLiteral("line_vertical_6"));
        line_vertical_6->setFrameShape(QFrame::VLine);
        line_vertical_6->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_graphics->addWidget(line_vertical_6);

        graphics_finger_5 = new QGraphicsView(centralWidget);
        graphics_finger_5->setObjectName(QStringLiteral("graphics_finger_5"));

        layout_touchVisualization_graphics->addWidget(graphics_finger_5);


        layout_touchVisualization->addLayout(layout_touchVisualization_graphics);

        layout_touchVisualization_progressBars = new QHBoxLayout();
        layout_touchVisualization_progressBars->setSpacing(6);
        layout_touchVisualization_progressBars->setObjectName(QStringLiteral("layout_touchVisualization_progressBars"));
        progressBar_finger_1 = new QProgressBar(centralWidget);
        progressBar_finger_1->setObjectName(QStringLiteral("progressBar_finger_1"));
        progressBar_finger_1->setValue(24);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_1);

        line_vertical_7 = new QFrame(centralWidget);
        line_vertical_7->setObjectName(QStringLiteral("line_vertical_7"));
        line_vertical_7->setFrameShape(QFrame::VLine);
        line_vertical_7->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_progressBars->addWidget(line_vertical_7);

        progressBar_finger_2 = new QProgressBar(centralWidget);
        progressBar_finger_2->setObjectName(QStringLiteral("progressBar_finger_2"));
        progressBar_finger_2->setValue(24);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_2);

        line_vertical_8 = new QFrame(centralWidget);
        line_vertical_8->setObjectName(QStringLiteral("line_vertical_8"));
        line_vertical_8->setFrameShape(QFrame::VLine);
        line_vertical_8->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_progressBars->addWidget(line_vertical_8);

        progressBar_finger_3 = new QProgressBar(centralWidget);
        progressBar_finger_3->setObjectName(QStringLiteral("progressBar_finger_3"));
        progressBar_finger_3->setValue(24);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_3);

        line_vertical_9 = new QFrame(centralWidget);
        line_vertical_9->setObjectName(QStringLiteral("line_vertical_9"));
        line_vertical_9->setFrameShape(QFrame::VLine);
        line_vertical_9->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_progressBars->addWidget(line_vertical_9);

        progressBar_finger_4 = new QProgressBar(centralWidget);
        progressBar_finger_4->setObjectName(QStringLiteral("progressBar_finger_4"));
        progressBar_finger_4->setValue(24);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_4);

        line_vertical_10 = new QFrame(centralWidget);
        line_vertical_10->setObjectName(QStringLiteral("line_vertical_10"));
        line_vertical_10->setFrameShape(QFrame::VLine);
        line_vertical_10->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_progressBars->addWidget(line_vertical_10);

        progressBar_finger_5 = new QProgressBar(centralWidget);
        progressBar_finger_5->setObjectName(QStringLiteral("progressBar_finger_5"));
        progressBar_finger_5->setValue(24);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_5);


        layout_touchVisualization->addLayout(layout_touchVisualization_progressBars);

        line_horizontal_2 = new QFrame(centralWidget);
        line_horizontal_2->setObjectName(QStringLiteral("line_horizontal_2"));
        line_horizontal_2->setFrameShape(QFrame::HLine);
        line_horizontal_2->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization->addWidget(line_horizontal_2);


        layout_mainInfo->addLayout(layout_touchVisualization);

        terminal = new QTextEdit(centralWidget);
        terminal->setObjectName(QStringLiteral("terminal"));
        QFont font;
        font.setFamily(QStringLiteral("Courier 10 Pitch"));
        terminal->setFont(font);
        terminal->setUndoRedoEnabled(false);
        terminal->setReadOnly(true);

        layout_mainInfo->addWidget(terminal);


        gridLayout->addLayout(layout_mainInfo, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 860, 19));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(action_connect);
        menuMenu->addAction(action_disconnect);
        menuMenu->addAction(action_exit);
        menuMenu->addAction(action_info);
        mainToolBar->addAction(action_connect);
        mainToolBar->addAction(action_disconnect);
        mainToolBar->addAction(action_exit);
        mainToolBar->addAction(action_info);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rekawica_sensoryczna", 0));
        action_connect->setText(QApplication::translate("MainWindow", "&Pod\305\202\304\205cz", 0));
        action_connect->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+C", 0));
        action_disconnect->setText(QApplication::translate("MainWindow", "&Roz\305\202\304\205cz", 0));
        action_disconnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+X", 0));
        action_exit->setText(QApplication::translate("MainWindow", "&Wyjd\305\272", 0));
        action_exit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", 0));
        action_info->setText(QApplication::translate("MainWindow", "&Info", 0));
        label_orientationX->setText(QApplication::translate("MainWindow", "Wsp\303\263\305\202rz\304\231dna X: ", 0));
        label_orientationY->setText(QApplication::translate("MainWindow", "Wsp\303\263\305\202rz\304\231dna Y: ", 0));
        value_orientationX->setText(QApplication::translate("MainWindow", "---", 0));
        value_orientationY->setText(QApplication::translate("MainWindow", "---", 0));
        terminal->setPlaceholderText(QApplication::translate("MainWindow", "Communication Terminal", 0));
        menuMenu->setTitle(QApplication::translate("MainWindow", "&Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
