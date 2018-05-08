/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.hh>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_connect;
    QAction *action_disconnect;
    QAction *action_exit;
    QAction *action_info;
    QAction *action_testrun;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *layout_mainInfo;
    QHBoxLayout *layout_orientation;
    QGraphicsView *graphics_handOrientation;
    QFrame *line_vertical_2;
    QHBoxLayout *layout_orientation_dataView;
    QVBoxLayout *layout_orientation_dataView_labels;
    QLabel *label_orientationX;
    QLabel *label_orientationZ;
    QVBoxLayout *layout_orientation_dataView_values;
    QLabel *value_orientationX;
    QLabel *value_orientationZ;
    QCustomPlot *graph_orientation;
    QVBoxLayout *layout_touchVisualization;
    QFrame *line_horizontal_1;
    QLabel *info1;
    QHBoxLayout *layout_touchVisualization_graphics;
    QPushButton *graphics_finger_1;
    QFrame *line_vertical_3;
    QPushButton *graphics_finger_2;
    QFrame *line_vertical_4;
    QPushButton *graphics_finger_3;
    QFrame *line_vertical_5;
    QPushButton *graphics_finger_4;
    QFrame *line_vertical_6;
    QPushButton *graphics_finger_5;
    QFrame *line;
    QLabel *info2;
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
    QHBoxLayout *layout_handVisualization;
    QVBoxLayout *layout_visualization;
    QGraphicsView *graphics_handVisualization;
    QFrame *line_2;
    QCustomPlot *graph_bending;
    QFrame *line_3;
    QCustomPlot *graph_touch;
    QFrame *line_vertical_1;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(960, 700);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 700));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/button_connect/icons/connect"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        action_connect = new QAction(MainWindow);
        action_connect->setObjectName(QStringLiteral("action_connect"));
        action_connect->setCheckable(false);
        QIcon icon1;
        QString iconThemeName = QStringLiteral("main");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral(":/menu_buttons/img_connect"), QSize(), QIcon::Normal, QIcon::Off);
        }
        action_connect->setIcon(icon1);
        action_disconnect = new QAction(MainWindow);
        action_disconnect->setObjectName(QStringLiteral("action_disconnect"));
        action_disconnect->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/menu_buttons/img_disconnect"), QSize(), QIcon::Normal, QIcon::Off);
        action_disconnect->setIcon(icon2);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/menu_buttons/img_buttonexit"), QSize(), QIcon::Normal, QIcon::Off);
        action_exit->setIcon(icon3);
        action_info = new QAction(MainWindow);
        action_info->setObjectName(QStringLiteral("action_info"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/menu_buttons/img_about"), QSize(), QIcon::Normal, QIcon::Off);
        action_info->setIcon(icon4);
        action_testrun = new QAction(MainWindow);
        action_testrun->setObjectName(QStringLiteral("action_testrun"));
        action_testrun->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/menu_buttons/img_testrun"), QSize(), QIcon::Normal, QIcon::Off);
        action_testrun->setIcon(icon5);
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
        centralWidget->setBaseSize(QSize(970, 700));
        centralWidget->setLocale(QLocale(QLocale::Polish, QLocale::Poland));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        layout_mainInfo = new QVBoxLayout();
        layout_mainInfo->setSpacing(6);
        layout_mainInfo->setObjectName(QStringLiteral("layout_mainInfo"));
        layout_orientation = new QHBoxLayout();
        layout_orientation->setSpacing(6);
        layout_orientation->setObjectName(QStringLiteral("layout_orientation"));
        graphics_handOrientation = new QGraphicsView(centralWidget);
        graphics_handOrientation->setObjectName(QStringLiteral("graphics_handOrientation"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphics_handOrientation->sizePolicy().hasHeightForWidth());
        graphics_handOrientation->setSizePolicy(sizePolicy2);
        graphics_handOrientation->setMinimumSize(QSize(0, 0));
        graphics_handOrientation->setMaximumSize(QSize(16777215, 16777215));
        graphics_handOrientation->setBaseSize(QSize(0, 0));
        graphics_handOrientation->viewport()->setProperty("cursor", QVariant(QCursor(Qt::WhatsThisCursor)));
        graphics_handOrientation->setToolTipDuration(2000);
        graphics_handOrientation->setAutoFillBackground(false);
        graphics_handOrientation->setFrameShape(QFrame::NoFrame);
        graphics_handOrientation->setFrameShadow(QFrame::Plain);
        graphics_handOrientation->setLineWidth(0);
        graphics_handOrientation->setInteractive(false);

        layout_orientation->addWidget(graphics_handOrientation, 0, Qt::AlignHCenter|Qt::AlignVCenter);

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
        QFont font;
        font.setPointSize(13);
        label_orientationX->setFont(font);
        label_orientationX->setCursor(QCursor(Qt::IBeamCursor));

        layout_orientation_dataView_labels->addWidget(label_orientationX);

        label_orientationZ = new QLabel(centralWidget);
        label_orientationZ->setObjectName(QStringLiteral("label_orientationZ"));
        label_orientationZ->setFont(font);
        label_orientationZ->setCursor(QCursor(Qt::IBeamCursor));

        layout_orientation_dataView_labels->addWidget(label_orientationZ);


        layout_orientation_dataView->addLayout(layout_orientation_dataView_labels);

        layout_orientation_dataView_values = new QVBoxLayout();
        layout_orientation_dataView_values->setSpacing(6);
        layout_orientation_dataView_values->setObjectName(QStringLiteral("layout_orientation_dataView_values"));
        layout_orientation_dataView_values->setContentsMargins(-1, -1, 10, -1);
        value_orientationX = new QLabel(centralWidget);
        value_orientationX->setObjectName(QStringLiteral("value_orientationX"));
        value_orientationX->setFont(font);
        value_orientationX->setCursor(QCursor(Qt::WhatsThisCursor));
        value_orientationX->setToolTipDuration(2000);

        layout_orientation_dataView_values->addWidget(value_orientationX);

        value_orientationZ = new QLabel(centralWidget);
        value_orientationZ->setObjectName(QStringLiteral("value_orientationZ"));
        value_orientationZ->setFont(font);
        value_orientationZ->setCursor(QCursor(Qt::WhatsThisCursor));
        value_orientationZ->setToolTipDuration(2000);

        layout_orientation_dataView_values->addWidget(value_orientationZ);


        layout_orientation_dataView->addLayout(layout_orientation_dataView_values);


        layout_orientation->addLayout(layout_orientation_dataView);

        graph_orientation = new QCustomPlot(centralWidget);
        graph_orientation->setObjectName(QStringLiteral("graph_orientation"));
        graph_orientation->setCursor(QCursor(Qt::CrossCursor));
        graph_orientation->setToolTipDuration(2000);

        layout_orientation->addWidget(graph_orientation);

        layout_orientation->setStretch(0, 4);
        layout_orientation->setStretch(1, 1);
        layout_orientation->setStretch(2, 3);
        layout_orientation->setStretch(3, 6);

        layout_mainInfo->addLayout(layout_orientation);

        layout_touchVisualization = new QVBoxLayout();
        layout_touchVisualization->setSpacing(6);
        layout_touchVisualization->setObjectName(QStringLiteral("layout_touchVisualization"));
        line_horizontal_1 = new QFrame(centralWidget);
        line_horizontal_1->setObjectName(QStringLiteral("line_horizontal_1"));
        line_horizontal_1->setFrameShape(QFrame::HLine);
        line_horizontal_1->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization->addWidget(line_horizontal_1);

        info1 = new QLabel(centralWidget);
        info1->setObjectName(QStringLiteral("info1"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        info1->setFont(font1);
        info1->setCursor(QCursor(Qt::WhatsThisCursor));
        info1->setToolTipDuration(2000);
        info1->setAlignment(Qt::AlignCenter);

        layout_touchVisualization->addWidget(info1);

        layout_touchVisualization_graphics = new QHBoxLayout();
        layout_touchVisualization_graphics->setSpacing(6);
        layout_touchVisualization_graphics->setObjectName(QStringLiteral("layout_touchVisualization_graphics"));
        graphics_finger_1 = new QPushButton(centralWidget);
        graphics_finger_1->setObjectName(QStringLiteral("graphics_finger_1"));
        graphics_finger_1->setCursor(QCursor(Qt::PointingHandCursor));
        graphics_finger_1->setToolTipDuration(2000);

        layout_touchVisualization_graphics->addWidget(graphics_finger_1);

        line_vertical_3 = new QFrame(centralWidget);
        line_vertical_3->setObjectName(QStringLiteral("line_vertical_3"));
        line_vertical_3->setFrameShape(QFrame::VLine);
        line_vertical_3->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_graphics->addWidget(line_vertical_3);

        graphics_finger_2 = new QPushButton(centralWidget);
        graphics_finger_2->setObjectName(QStringLiteral("graphics_finger_2"));
        graphics_finger_2->setCursor(QCursor(Qt::PointingHandCursor));
        graphics_finger_2->setToolTipDuration(2000);

        layout_touchVisualization_graphics->addWidget(graphics_finger_2);

        line_vertical_4 = new QFrame(centralWidget);
        line_vertical_4->setObjectName(QStringLiteral("line_vertical_4"));
        line_vertical_4->setFrameShape(QFrame::VLine);
        line_vertical_4->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_graphics->addWidget(line_vertical_4);

        graphics_finger_3 = new QPushButton(centralWidget);
        graphics_finger_3->setObjectName(QStringLiteral("graphics_finger_3"));
        graphics_finger_3->setCursor(QCursor(Qt::PointingHandCursor));
        graphics_finger_3->setToolTipDuration(2000);

        layout_touchVisualization_graphics->addWidget(graphics_finger_3);

        line_vertical_5 = new QFrame(centralWidget);
        line_vertical_5->setObjectName(QStringLiteral("line_vertical_5"));
        line_vertical_5->setFrameShape(QFrame::VLine);
        line_vertical_5->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_graphics->addWidget(line_vertical_5);

        graphics_finger_4 = new QPushButton(centralWidget);
        graphics_finger_4->setObjectName(QStringLiteral("graphics_finger_4"));
        graphics_finger_4->setCursor(QCursor(Qt::PointingHandCursor));
        graphics_finger_4->setToolTipDuration(2000);

        layout_touchVisualization_graphics->addWidget(graphics_finger_4);

        line_vertical_6 = new QFrame(centralWidget);
        line_vertical_6->setObjectName(QStringLiteral("line_vertical_6"));
        line_vertical_6->setFrameShape(QFrame::VLine);
        line_vertical_6->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_graphics->addWidget(line_vertical_6);

        graphics_finger_5 = new QPushButton(centralWidget);
        graphics_finger_5->setObjectName(QStringLiteral("graphics_finger_5"));
        graphics_finger_5->setCursor(QCursor(Qt::PointingHandCursor));
        graphics_finger_5->setToolTipDuration(2000);

        layout_touchVisualization_graphics->addWidget(graphics_finger_5);


        layout_touchVisualization->addLayout(layout_touchVisualization_graphics);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization->addWidget(line);

        info2 = new QLabel(centralWidget);
        info2->setObjectName(QStringLiteral("info2"));
        info2->setFont(font1);
        info2->setCursor(QCursor(Qt::IBeamCursor));
        info2->setToolTipDuration(-1);
        info2->setAlignment(Qt::AlignCenter);

        layout_touchVisualization->addWidget(info2);

        layout_touchVisualization_progressBars = new QHBoxLayout();
        layout_touchVisualization_progressBars->setSpacing(6);
        layout_touchVisualization_progressBars->setObjectName(QStringLiteral("layout_touchVisualization_progressBars"));
        progressBar_finger_1 = new QProgressBar(centralWidget);
        progressBar_finger_1->setObjectName(QStringLiteral("progressBar_finger_1"));
        progressBar_finger_1->setCursor(QCursor(Qt::WhatsThisCursor));
        progressBar_finger_1->setToolTipDuration(2000);
        progressBar_finger_1->setValue(0);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_1);

        line_vertical_7 = new QFrame(centralWidget);
        line_vertical_7->setObjectName(QStringLiteral("line_vertical_7"));
        line_vertical_7->setFrameShape(QFrame::VLine);
        line_vertical_7->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_progressBars->addWidget(line_vertical_7);

        progressBar_finger_2 = new QProgressBar(centralWidget);
        progressBar_finger_2->setObjectName(QStringLiteral("progressBar_finger_2"));
        progressBar_finger_2->setCursor(QCursor(Qt::WhatsThisCursor));
        progressBar_finger_2->setToolTipDuration(2000);
        progressBar_finger_2->setValue(0);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_2);

        line_vertical_8 = new QFrame(centralWidget);
        line_vertical_8->setObjectName(QStringLiteral("line_vertical_8"));
        line_vertical_8->setFrameShape(QFrame::VLine);
        line_vertical_8->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_progressBars->addWidget(line_vertical_8);

        progressBar_finger_3 = new QProgressBar(centralWidget);
        progressBar_finger_3->setObjectName(QStringLiteral("progressBar_finger_3"));
        progressBar_finger_3->setCursor(QCursor(Qt::WhatsThisCursor));
        progressBar_finger_3->setToolTipDuration(2000);
        progressBar_finger_3->setValue(0);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_3);

        line_vertical_9 = new QFrame(centralWidget);
        line_vertical_9->setObjectName(QStringLiteral("line_vertical_9"));
        line_vertical_9->setFrameShape(QFrame::VLine);
        line_vertical_9->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_progressBars->addWidget(line_vertical_9);

        progressBar_finger_4 = new QProgressBar(centralWidget);
        progressBar_finger_4->setObjectName(QStringLiteral("progressBar_finger_4"));
        progressBar_finger_4->setCursor(QCursor(Qt::WhatsThisCursor));
        progressBar_finger_4->setToolTipDuration(2000);
        progressBar_finger_4->setValue(0);

        layout_touchVisualization_progressBars->addWidget(progressBar_finger_4);

        line_vertical_10 = new QFrame(centralWidget);
        line_vertical_10->setObjectName(QStringLiteral("line_vertical_10"));
        line_vertical_10->setFrameShape(QFrame::VLine);
        line_vertical_10->setFrameShadow(QFrame::Sunken);

        layout_touchVisualization_progressBars->addWidget(line_vertical_10);

        progressBar_finger_5 = new QProgressBar(centralWidget);
        progressBar_finger_5->setObjectName(QStringLiteral("progressBar_finger_5"));
        progressBar_finger_5->setCursor(QCursor(Qt::WhatsThisCursor));
        progressBar_finger_5->setToolTipDuration(2000);
        progressBar_finger_5->setValue(0);

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
        QFont font2;
        font2.setFamily(QStringLiteral("Courier 10 Pitch"));
        terminal->setFont(font2);
        terminal->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        terminal->setToolTipDuration(2000);
        terminal->setUndoRedoEnabled(false);
        terminal->setReadOnly(true);

        layout_mainInfo->addWidget(terminal);

        layout_mainInfo->setStretch(0, 7);
        layout_mainInfo->setStretch(1, 5);
        layout_mainInfo->setStretch(2, 5);

        gridLayout->addLayout(layout_mainInfo, 0, 1, 1, 1);

        layout_handVisualization = new QHBoxLayout();
        layout_handVisualization->setSpacing(6);
        layout_handVisualization->setObjectName(QStringLiteral("layout_handVisualization"));
        layout_visualization = new QVBoxLayout();
        layout_visualization->setSpacing(6);
        layout_visualization->setObjectName(QStringLiteral("layout_visualization"));
        graphics_handVisualization = new QGraphicsView(centralWidget);
        graphics_handVisualization->setObjectName(QStringLiteral("graphics_handVisualization"));
        sizePolicy2.setHeightForWidth(graphics_handVisualization->sizePolicy().hasHeightForWidth());
        graphics_handVisualization->setSizePolicy(sizePolicy2);
        graphics_handVisualization->setMinimumSize(QSize(0, 0));
        graphics_handVisualization->setMaximumSize(QSize(16777215, 9999999));
        graphics_handVisualization->setSizeIncrement(QSize(0, 0));
        graphics_handVisualization->setBaseSize(QSize(0, 0));
        graphics_handVisualization->viewport()->setProperty("cursor", QVariant(QCursor(Qt::WhatsThisCursor)));
        graphics_handVisualization->setToolTipDuration(2000);
        graphics_handVisualization->setAutoFillBackground(false);
        graphics_handVisualization->setFrameShape(QFrame::NoFrame);
        graphics_handVisualization->setFrameShadow(QFrame::Plain);
        graphics_handVisualization->setLineWidth(0);

        layout_visualization->addWidget(graphics_handVisualization, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        layout_visualization->addWidget(line_2);

        graph_bending = new QCustomPlot(centralWidget);
        graph_bending->setObjectName(QStringLiteral("graph_bending"));
        sizePolicy1.setHeightForWidth(graph_bending->sizePolicy().hasHeightForWidth());
        graph_bending->setSizePolicy(sizePolicy1);
        graph_bending->setMinimumSize(QSize(240, 0));
        graph_bending->setMaximumSize(QSize(16777215, 16777215));
        graph_bending->setCursor(QCursor(Qt::CrossCursor));
        graph_bending->setToolTipDuration(2000);

        layout_visualization->addWidget(graph_bending);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        layout_visualization->addWidget(line_3);

        graph_touch = new QCustomPlot(centralWidget);
        graph_touch->setObjectName(QStringLiteral("graph_touch"));
        graph_touch->setCursor(QCursor(Qt::CrossCursor));
        graph_touch->setToolTipDuration(2000);

        layout_visualization->addWidget(graph_touch);

        layout_visualization->setStretch(0, 2);
        layout_visualization->setStretch(1, 1);
        layout_visualization->setStretch(2, 2);
        layout_visualization->setStretch(3, 1);
        layout_visualization->setStretch(4, 2);

        layout_handVisualization->addLayout(layout_visualization);

        line_vertical_1 = new QFrame(centralWidget);
        line_vertical_1->setObjectName(QStringLiteral("line_vertical_1"));
        line_vertical_1->setFrameShape(QFrame::VLine);
        line_vertical_1->setFrameShadow(QFrame::Sunken);

        layout_handVisualization->addWidget(line_vertical_1);

        layout_handVisualization->setStretch(0, 4);
        layout_handVisualization->setStretch(1, 1);

        gridLayout->addLayout(layout_handVisualization, 0, 0, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 25));
        menuBar->setCursor(QCursor(Qt::PointingHandCursor));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setCursor(QCursor(Qt::PointingHandCursor));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(action_connect);
        menuMenu->addAction(action_disconnect);
        menuMenu->addAction(action_testrun);
        menuMenu->addAction(action_exit);
        menuMenu->addAction(action_info);
        mainToolBar->addAction(action_connect);
        mainToolBar->addAction(action_disconnect);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_testrun);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_info);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rekawica_sensoryczna", Q_NULLPTR));
        action_connect->setText(QApplication::translate("MainWindow", "Pod\305\202\304\205cz", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_connect->setToolTip(QApplication::translate("MainWindow", "Umo\305\274liwia \305\202\304\205czenie z urz\304\205dzeniem poprzez port wirtualny", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        action_connect->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        action_connect->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+C", Q_NULLPTR));
        action_disconnect->setText(QApplication::translate("MainWindow", "Roz\305\202\304\205cz", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_disconnect->setToolTip(QApplication::translate("MainWindow", "Roz\305\202\304\205cza z urz\304\205dzeniem", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        action_disconnect->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        action_disconnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+D", Q_NULLPTR));
        action_exit->setText(QApplication::translate("MainWindow", "Wyjd\305\272", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_exit->setToolTip(QApplication::translate("MainWindow", "Wychodzi z aplikacji", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        action_exit->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        action_exit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+E", Q_NULLPTR));
        action_info->setText(QApplication::translate("MainWindow", "&Info", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_info->setToolTip(QApplication::translate("MainWindow", "Pokazuje informacje", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        action_info->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        action_info->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+I", Q_NULLPTR));
        action_testrun->setText(QApplication::translate("MainWindow", "&Test Syntetyczny", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_testrun->setToolTip(QApplication::translate("MainWindow", "Uruchamia test syntetyczny z losowymi warto\305\233ciami", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        action_testrun->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        action_testrun->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+T", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graphics_handOrientation->setToolTip(QApplication::translate("MainWindow", "Jak rozumiemy osie patrz\304\205c na d\305\202o\305\204", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_orientationX->setText(QApplication::translate("MainWindow", "O\305\233 X: ", Q_NULLPTR));
        label_orientationZ->setText(QApplication::translate("MainWindow", "O\305\233 Z: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        value_orientationX->setToolTip(QApplication::translate("MainWindow", "Warto\305\233\304\207 osi x", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        value_orientationX->setText(QApplication::translate("MainWindow", "---", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        value_orientationZ->setToolTip(QApplication::translate("MainWindow", "Warto\305\233\304\207 osi z", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        value_orientationZ->setText(QApplication::translate("MainWindow", "---", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graph_orientation->setToolTip(QApplication::translate("MainWindow", "Wykres warto\305\233ci akcelerometru zale\305\274ny od czasu", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        info1->setToolTip(QApplication::translate("MainWindow", "Przyciski pozwalaj\304\205ce sterowa\304\207 drganiami poszczeg\303\263lnych palc\303\263w", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        info1->setText(QApplication::translate("MainWindow", "Sterowanie drganiami paliczk\303\263w", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graphics_finger_1->setToolTip(QApplication::translate("MainWindow", "W\305\202\304\205cz wibracje na kciuku", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        graphics_finger_1->setText(QApplication::translate("MainWindow", "Kciuk", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graphics_finger_2->setToolTip(QApplication::translate("MainWindow", "W\305\202\304\205cz wibracje na palcu wskazuj\304\205cym", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        graphics_finger_2->setText(QApplication::translate("MainWindow", "P. wskazuj\304\205cy", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graphics_finger_3->setToolTip(QApplication::translate("MainWindow", "W\305\202\304\205cz wibracje na palcu \305\233rodkowym", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        graphics_finger_3->setText(QApplication::translate("MainWindow", "P. \305\233rodkowy", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graphics_finger_4->setToolTip(QApplication::translate("MainWindow", "W\305\202\304\205cz wibracje na palcu serdecznym", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        graphics_finger_4->setText(QApplication::translate("MainWindow", "P. serdeczny", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graphics_finger_5->setToolTip(QApplication::translate("MainWindow", "W\305\202\304\205cz wibracje na ma\305\202ym palcu", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        graphics_finger_5->setText(QApplication::translate("MainWindow", "P. ma\305\202y", Q_NULLPTR));
        info2->setText(QApplication::translate("MainWindow", "Si\305\202a nacisku na poszczeg\303\263lne paliczki", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        progressBar_finger_1->setToolTip(QApplication::translate("MainWindow", "Warto\305\233\304\207 si\305\202y nacisku na kciuk", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        progressBar_finger_1->setFormat(QApplication::translate("MainWindow", "%p%", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        progressBar_finger_2->setToolTip(QApplication::translate("MainWindow", "Warto\305\233\304\207 si\305\202y nacisku na palec wskazuj\304\205cy", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        progressBar_finger_3->setToolTip(QApplication::translate("MainWindow", "Warto\305\233\304\207 si\305\202y nacisku na palec \305\233rodkowy", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        progressBar_finger_4->setToolTip(QApplication::translate("MainWindow", "Warto\305\233\304\207 si\305\202y nacisku na palec serdeczny", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        progressBar_finger_5->setToolTip(QApplication::translate("MainWindow", "Warto\305\233\304\207 si\305\202y nacisku na ma\305\202y palec", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        terminal->setToolTip(QApplication::translate("MainWindow", "Pokazuje zapiski systemowe", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        terminal->setPlaceholderText(QApplication::translate("MainWindow", "Logs only", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graphics_handVisualization->setToolTip(QApplication::translate("MainWindow", "Wizualizuje interkacje", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        graph_bending->setToolTip(QApplication::translate("MainWindow", "Pokazuje warto\305\233ci zgi\304\231cia palc\303\263w zale\305\274ne od czasu", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        graph_touch->setToolTip(QApplication::translate("MainWindow", "Pokazuje warto\305\233ci si\305\202y dotyku poszczeg\303\263lnych palc\303\263w zale\305\274ne od czasu", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        menuMenu->setTitle(QApplication::translate("MainWindow", "&Menu", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
