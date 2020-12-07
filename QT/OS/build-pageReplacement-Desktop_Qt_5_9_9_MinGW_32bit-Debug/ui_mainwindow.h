/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QTableWidget *tableRequest;
    QTableWidget *tablePage;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *btnNext;
    QPushButton *pushButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1200, 800);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(60, 100, 600, 600));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 200);"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 200);"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        tableRequest = new QTableWidget(widget);
        if (tableRequest->columnCount() < 1)
            tableRequest->setColumnCount(1);
        tableRequest->setObjectName(QStringLiteral("tableRequest"));
        tableRequest->setFont(font);
        tableRequest->setStyleSheet(QLatin1String("background-color: rgba(255, 255, 255, 200);\n"
"selection-background-color: rgb(255, 170, 0);"));
        tableRequest->setAlternatingRowColors(true);
        tableRequest->setColumnCount(1);
        tableRequest->horizontalHeader()->setVisible(false);
        tableRequest->horizontalHeader()->setCascadingSectionResizes(false);

        gridLayout->addWidget(tableRequest, 1, 0, 1, 1);

        tablePage = new QTableWidget(widget);
        if (tablePage->columnCount() < 4)
            tablePage->setColumnCount(4);
        tablePage->setObjectName(QStringLiteral("tablePage"));
        tablePage->setFont(font);
        tablePage->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 200);"));
        tablePage->setColumnCount(4);
        tablePage->horizontalHeader()->setVisible(false);

        gridLayout->addWidget(tablePage, 1, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(750, 290, 171, 121));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnNext = new QPushButton(widget_2);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setMinimumSize(QSize(30, 30));
        btnNext->setFont(font);
        btnNext->setStyleSheet(QLatin1String("border-radius: 5px;\n"
"background-color: rgb(214, 214, 214);"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/icons/Cartoon-Arrow-Down.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNext->setIcon(icon);
        btnNext->setIconSize(QSize(19, 19));

        verticalLayout->addWidget(btnNext);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 30));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QLatin1String("border-radius: 5px;\n"
"background-color: rgb(214, 214, 214);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/icons/Cartoon-Closed.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(19, 19));

        verticalLayout->addWidget(pushButton);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\351\241\265\351\235\242\347\275\256\346\215\242\346\250\241\346\213\237\347\250\213\345\272\217", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\350\257\267\346\261\202\351\241\265\351\235\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\351\241\265\350\241\250", Q_NULLPTR));
        btnNext->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\346\255\245", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
