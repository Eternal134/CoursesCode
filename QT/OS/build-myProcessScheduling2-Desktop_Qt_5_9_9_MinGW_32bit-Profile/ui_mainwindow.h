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

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_2;
    QSpinBox *spinBox;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_3;
    QSpinBox *spinBox_2;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_6;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1171, 704);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 381, 681));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_5 = new QSpacerItem(20, 48, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QFont font1;
        font1.setFamily(QStringLiteral("Consolas"));
        font1.setPointSize(10);
        lineEdit->setFont(font1);
        lineEdit->setTabletTracking(true);
        lineEdit->setFocusPolicy(Qt::StrongFocus);
        lineEdit->setStyleSheet(QLatin1String("\n"
"border-radius:5px;"));

        verticalLayout->addWidget(lineEdit);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setFont(font1);
        spinBox->setStyleSheet(QLatin1String("\n"
"border-radius:5px;"));

        verticalLayout->addWidget(spinBox);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        spinBox_2 = new QSpinBox(widget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setFont(font1);
        spinBox_2->setStyleSheet(QStringLiteral("border-radius:5px;"));

        verticalLayout->addWidget(spinBox_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        font2.setUnderline(false);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QLatin1String("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(194, 255, 216, 255), stop:1 rgba(70, 94, 251, 255));\n"
"border-radius:5px;"));

        verticalLayout->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(26, 46, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setFont(font);
        pushButton_2->setFocusPolicy(Qt::ClickFocus);
        pushButton_2->setStyleSheet(QLatin1String("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(194, 255, 216, 255), stop:1 rgba(70, 94, 251, 255));\n"
"border-radius:5px;"));

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setFont(font);
        pushButton_4->setFocusPolicy(Qt::ClickFocus);
        pushButton_4->setStyleSheet(QLatin1String("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(194, 255, 216, 255), stop:1 rgba(70, 94, 251, 255));\n"
"border-radius:5px;"));

        verticalLayout->addWidget(pushButton_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setFont(font);
        pushButton_3->setFocusPolicy(Qt::ClickFocus);
        pushButton_3->setStyleSheet(QLatin1String("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(194, 255, 216, 255), stop:1 rgba(70, 94, 251, 255));\n"
"border-radius:5px;"));

        verticalLayout->addWidget(pushButton_3);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(399, 9, 761, 691));
        widget_2->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font3;
        font3.setPointSize(15);
        label_4->setFont(font3);
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setStyleSheet(QStringLiteral(""));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        tableWidget = new QTableWidget(widget_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setFont(font);
        tableWidget->setFocusPolicy(Qt::ClickFocus);
        tableWidget->setStyleSheet(QStringLiteral(""));
        tableWidget->setColumnCount(0);

        verticalLayout_2->addWidget(tableWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234\347\263\273\347\273\237\350\277\233\347\250\213\350\260\203\345\272\246\346\250\241\346\213\237", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\350\277\233\347\250\213\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\344\274\230\345\205\210\347\272\247", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\351\234\200\350\246\201\347\232\204CPU\346\227\266\351\227\264", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\350\277\233\347\250\213", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214\350\277\233\347\250\213", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\346\227\245\345\277\227", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\345\260\261\347\273\252\351\230\237\345\210\227", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
