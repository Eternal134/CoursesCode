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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <btn_apply.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QLabel *label;
    QLineEdit *lineEditName;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;
    QSpinBox *spinBoxLen;
    QSpacerItem *verticalSpacer_2;
    btn_apply *btnApply;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonRelease;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QTableWidget *tableWidget;
    QLabel *labBackground;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1306, 781);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/icon_23.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QLatin1String("border-image:url(:/new/logo2.0.jpg);\n"
"border-image:url()"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(140, 110, 961, 461));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(widget_3);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_5 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgba(255, 255, 255, 200);"));

        verticalLayout->addWidget(label);

        lineEditName = new QLineEdit(widget);
        lineEditName->setObjectName(QStringLiteral("lineEditName"));
        lineEditName->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        lineEditName->setFont(font1);
        lineEditName->setStyleSheet(QStringLiteral("color: rgba(0, 0, 0, 200);"));

        verticalLayout->addWidget(lineEditName);

        verticalSpacer_4 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("color: rgba(255, 255, 255, 200);"));

        verticalLayout->addWidget(label_2);

        spinBoxLen = new QSpinBox(widget);
        spinBoxLen->setObjectName(QStringLiteral("spinBoxLen"));
        spinBoxLen->setMinimumSize(QSize(0, 30));
        spinBoxLen->setFont(font1);
        spinBoxLen->setMaximum(10000000);

        verticalLayout->addWidget(spinBoxLen);

        verticalSpacer_2 = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        btnApply = new btn_apply(widget);
        btnApply->setObjectName(QStringLiteral("btnApply"));
        btnApply->setMinimumSize(QSize(0, 30));
        btnApply->setFont(font1);
        btnApply->setAutoFillBackground(false);
        btnApply->setStyleSheet(QLatin1String("border-radius:5px;\n"
"background-color: rgb(255, 255, 255, 200);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/PlusSquare.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnApply->setIcon(icon1);

        verticalLayout->addWidget(btnApply);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButtonRelease = new QPushButton(widget);
        pushButtonRelease->setObjectName(QStringLiteral("pushButtonRelease"));
        pushButtonRelease->setMinimumSize(QSize(0, 30));
        pushButtonRelease->setFont(font1);
        pushButtonRelease->setStyleSheet(QLatin1String("border-radius:5px;\n"
"background-color: rgba(255, 255, 255, 200);"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/MinusSquare.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRelease->setIcon(icon2);

        verticalLayout->addWidget(pushButtonRelease);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 30));
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QLatin1String("border-radius:5px;\n"
"background-color: rgba(255, 255, 255, 200);"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/CloseSquare.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon3);

        verticalLayout->addWidget(pushButton);

        verticalSpacer_6 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);


        horizontalLayout->addWidget(widget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 0));
        widget_2->setMaximumSize(QSize(1666666, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        label_3->setFont(font2);
        label_3->setStyleSheet(QStringLiteral("color: rgba(255, 255, 255, 200);"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        tableWidget = new QTableWidget(widget_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(0, 0));
        tableWidget->setMaximumSize(QSize(1666666, 16777215));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(9);
        tableWidget->setFont(font3);
        tableWidget->setAutoFillBackground(true);
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);\n"
"alternate-background-color: rgba(156, 251, 255, 200);\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border-radius:5px;"));
        tableWidget->setFrameShape(QFrame::WinPanel);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setGridStyle(Qt::DotLine);

        verticalLayout_2->addWidget(tableWidget);


        horizontalLayout->addWidget(widget_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 3);
        labBackground = new QLabel(centralwidget);
        labBackground->setObjectName(QStringLiteral("labBackground"));
        labBackground->setGeometry(QRect(0, 0, 1500, 1000));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labBackground->sizePolicy().hasHeightForWidth());
        labBackground->setSizePolicy(sizePolicy1);
        labBackground->setPixmap(QPixmap(QString::fromUtf8(":/image/autumn-5704791_1920.jpg")));
        labBackground->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        labBackground->raise();
        widget_3->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\350\277\233\347\250\213\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\347\251\272\351\227\264\345\244\247\345\260\217", Q_NULLPTR));
        btnApply->setText(QApplication::translate("MainWindow", "\347\224\263\350\257\267\347\251\272\351\227\264", Q_NULLPTR));
        pushButtonRelease->setText(QApplication::translate("MainWindow", "\351\207\212\346\224\276\347\251\272\351\227\264", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\347\251\272\351\227\262\345\214\272\351\223\276", Q_NULLPTR));
        labBackground->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
