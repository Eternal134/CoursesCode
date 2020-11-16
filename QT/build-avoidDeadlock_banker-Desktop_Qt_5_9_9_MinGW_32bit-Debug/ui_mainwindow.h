/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTableWidget *tableWidget_Max;
    QLabel *label_4;
    QTableWidget *tableWidget_Allocation;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableWidget *tableWidget_Available;
    QLabel *label_3;
    QTableWidget *tableWidget_Need;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QSpinBox *spinBox_num;
    QLabel *label_6;
    QSpinBox *spinBox_A;
    QLabel *label_7;
    QSpinBox *spinBox_B;
    QLabel *label_8;
    QSpinBox *spinBox_C;
    QPushButton *pushButton_request;
    QPushButton *pushButton_log;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1129, 746);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(770, 120, 330, 481));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        tableWidget_Max = new QTableWidget(widget);
        tableWidget_Max->setObjectName(QStringLiteral("tableWidget_Max"));
        tableWidget_Max->setMinimumSize(QSize(300, 200));
        tableWidget_Max->setMaximumSize(QSize(300, 200));
        tableWidget_Max->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout->addWidget(tableWidget_Max);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        tableWidget_Allocation = new QTableWidget(widget);
        tableWidget_Allocation->setObjectName(QStringLiteral("tableWidget_Allocation"));
        tableWidget_Allocation->setMinimumSize(QSize(300, 200));
        tableWidget_Allocation->setMaximumSize(QSize(300, 200));
        tableWidget_Allocation->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_Allocation->setSelectionBehavior(QAbstractItemView::SelectItems);

        verticalLayout->addWidget(tableWidget_Allocation);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(420, 180, 330, 381));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        tableWidget_Available = new QTableWidget(widget_2);
        if (tableWidget_Available->rowCount() < 1)
            tableWidget_Available->setRowCount(1);
        tableWidget_Available->setObjectName(QStringLiteral("tableWidget_Available"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget_Available->sizePolicy().hasHeightForWidth());
        tableWidget_Available->setSizePolicy(sizePolicy);
        tableWidget_Available->setMinimumSize(QSize(300, 70));
        tableWidget_Available->setMaximumSize(QSize(300, 70));
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft YaHei UI"));
        tableWidget_Available->setFont(font1);
        tableWidget_Available->setContextMenuPolicy(Qt::DefaultContextMenu);
        tableWidget_Available->setLayoutDirection(Qt::LeftToRight);
        tableWidget_Available->setAutoFillBackground(false);
        tableWidget_Available->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        tableWidget_Available->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget_Available->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget_Available->setAlternatingRowColors(true);
        tableWidget_Available->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_Available->setRowCount(1);
        tableWidget_Available->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_Available->horizontalHeader()->setDefaultSectionSize(40);
        tableWidget_Available->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget_Available->horizontalHeader()->setStretchLastSection(false);
        tableWidget_Available->verticalHeader()->setVisible(false);
        tableWidget_Available->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout_2->addWidget(tableWidget_Available);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        tableWidget_Need = new QTableWidget(widget_2);
        tableWidget_Need->setObjectName(QStringLiteral("tableWidget_Need"));
        tableWidget_Need->setMinimumSize(QSize(300, 200));
        tableWidget_Need->setMaximumSize(QSize(300, 200));
        tableWidget_Need->setStyleSheet(QStringLiteral(""));
        tableWidget_Need->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWidget_Need->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_Need->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableWidget_Need->horizontalHeader()->setMinimumSectionSize(29);
        tableWidget_Need->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout_2->addWidget(tableWidget_Need);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(60, 160, 211, 421));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_5);

        spinBox_num = new QSpinBox(widget_3);
        spinBox_num->setObjectName(QStringLiteral("spinBox_num"));
        spinBox_num->setMinimumSize(QSize(10, 25));

        verticalLayout_3->addWidget(spinBox_num);

        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_6);

        spinBox_A = new QSpinBox(widget_3);
        spinBox_A->setObjectName(QStringLiteral("spinBox_A"));
        spinBox_A->setMinimumSize(QSize(0, 25));

        verticalLayout_3->addWidget(spinBox_A);

        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_7);

        spinBox_B = new QSpinBox(widget_3);
        spinBox_B->setObjectName(QStringLiteral("spinBox_B"));
        spinBox_B->setMinimumSize(QSize(0, 25));

        verticalLayout_3->addWidget(spinBox_B);

        label_8 = new QLabel(widget_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_8);

        spinBox_C = new QSpinBox(widget_3);
        spinBox_C->setObjectName(QStringLiteral("spinBox_C"));
        spinBox_C->setMinimumSize(QSize(0, 25));

        verticalLayout_3->addWidget(spinBox_C);

        pushButton_request = new QPushButton(widget_3);
        pushButton_request->setObjectName(QStringLiteral("pushButton_request"));
        pushButton_request->setFont(font);

        verticalLayout_3->addWidget(pushButton_request);

        pushButton_log = new QPushButton(widget_3);
        pushButton_log->setObjectName(QStringLiteral("pushButton_log"));
        pushButton_log->setFont(font);
        pushButton_log->setContextMenuPolicy(Qt::DefaultContextMenu);

        verticalLayout_3->addWidget(pushButton_log);

        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font);

        verticalLayout_3->addWidget(pushButton);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\220\204\350\277\233\347\250\213\347\232\204\346\234\200\345\244\247\351\234\200\346\261\202\351\207\217", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\345\267\262\345\210\206\351\205\215\347\273\231\345\220\204\350\277\233\347\250\213\347\232\204\350\265\204\346\272\220\351\207\217", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\347\216\260\346\234\211\350\265\204\346\272\220", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\220\204\350\277\233\347\250\213\350\277\230\351\234\200\350\246\201\347\232\204\346\234\200\345\244\247\350\265\204\346\272\220\351\207\217", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\350\277\233\347\250\213\345\217\267", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "A\350\265\204\346\272\220\351\207\217", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "B\350\265\204\346\272\220\351\207\217", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "C\350\265\204\346\272\220\351\207\217", Q_NULLPTR));
        pushButton_request->setText(QApplication::translate("MainWindow", "\347\224\263\350\257\267\350\265\204\346\272\220", Q_NULLPTR));
        pushButton_log->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\346\227\245\345\277\227", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\347\250\213\345\272\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
