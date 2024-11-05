/********************************************************************************
** Form generated from reading UI file 'tcpserverwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVERWIDGET_H
#define UI_TCPSERVERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCPServerWidget
{
public:
    QCheckBox *toHex;
    QComboBox *localIp;
    QSpinBox *localPort;
    QPushButton *listen;
    QPushButton *close;
    QLineEdit *message;
    QPushButton *send;
    QTextEdit *textEdit;
    QTableWidget *clientTable;
    QPushButton *clear;
    QFrame *line;
    QFrame *line_2;
    QLabel *label;
    QFrame *line_3;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *line_4;
    QLabel *label_4;
    QLabel *label_PACKET_CNT;
    QLabel *label_5;
    QLabel *label_DEV_ID;
    QLabel *label_6;
    QLabel *label_BATT_VOLT;
    QPushButton *btn_OPEN_LED0;
    QLabel *label_7;

    void setupUi(QWidget *TCPServerWidget)
    {
        if (TCPServerWidget->objectName().isEmpty())
            TCPServerWidget->setObjectName("TCPServerWidget");
        TCPServerWidget->resize(900, 600);
        toHex = new QCheckBox(TCPServerWidget);
        toHex->setObjectName("toHex");
        toHex->setGeometry(QRect(360, 110, 51, 30));
        localIp = new QComboBox(TCPServerWidget);
        localIp->setObjectName("localIp");
        localIp->setGeometry(QRect(10, 10, 161, 30));
        localIp->setMinimumSize(QSize(120, 0));
        localPort = new QSpinBox(TCPServerWidget);
        localPort->setObjectName("localPort");
        localPort->setGeometry(QRect(180, 10, 72, 30));
        localPort->setMinimum(1);
        localPort->setMaximum(65535);
        localPort->setValue(5555);
        listen = new QPushButton(TCPServerWidget);
        listen->setObjectName("listen");
        listen->setGeometry(QRect(270, 10, 93, 30));
        close = new QPushButton(TCPServerWidget);
        close->setObjectName("close");
        close->setGeometry(QRect(390, 10, 93, 30));
        message = new QLineEdit(TCPServerWidget);
        message->setObjectName("message");
        message->setGeometry(QRect(10, 60, 351, 30));
        send = new QPushButton(TCPServerWidget);
        send->setObjectName("send");
        send->setGeometry(QRect(390, 60, 93, 30));
        textEdit = new QTextEdit(TCPServerWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(280, 150, 331, 431));
        textEdit->setReadOnly(true);
        textEdit->setTabStopDistance(80.000000000000000);
        clientTable = new QTableWidget(TCPServerWidget);
        if (clientTable->columnCount() < 2)
            clientTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        clientTable->setObjectName("clientTable");
        clientTable->setGeometry(QRect(10, 150, 250, 431));
        clientTable->setMaximumSize(QSize(250, 16777215));
        clientTable->setGridStyle(Qt::SolidLine);
        clear = new QPushButton(TCPServerWidget);
        clear->setObjectName("clear");
        clear->setGeometry(QRect(520, 110, 93, 30));
        line = new QFrame(TCPServerWidget);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 40, 631, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(TCPServerWidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, 100, 631, 16));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        label = new QLabel(TCPServerWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 120, 131, 16));
        line_3 = new QFrame(TCPServerWidget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(260, 110, 20, 491));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        label_2 = new QLabel(TCPServerWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(280, 110, 91, 30));
        label_3 = new QLabel(TCPServerWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(450, 110, 91, 30));
        line_4 = new QFrame(TCPServerWidget);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(620, 0, 20, 601));
        line_4->setFrameShape(QFrame::Shape::VLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        label_4 = new QLabel(TCPServerWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(650, 60, 101, 30));
        label_PACKET_CNT = new QLabel(TCPServerWidget);
        label_PACKET_CNT->setObjectName("label_PACKET_CNT");
        label_PACKET_CNT->setGeometry(QRect(760, 60, 72, 30));
        label_5 = new QLabel(TCPServerWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(650, 30, 101, 30));
        label_DEV_ID = new QLabel(TCPServerWidget);
        label_DEV_ID->setObjectName("label_DEV_ID");
        label_DEV_ID->setGeometry(QRect(760, 30, 72, 30));
        label_6 = new QLabel(TCPServerWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(650, 90, 101, 30));
        label_BATT_VOLT = new QLabel(TCPServerWidget);
        label_BATT_VOLT->setObjectName("label_BATT_VOLT");
        label_BATT_VOLT->setGeometry(QRect(760, 90, 72, 30));
        btn_OPEN_LED0 = new QPushButton(TCPServerWidget);
        btn_OPEN_LED0->setObjectName("btn_OPEN_LED0");
        btn_OPEN_LED0->setGeometry(QRect(760, 170, 93, 30));
        label_7 = new QLabel(TCPServerWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(650, 170, 101, 30));

        retranslateUi(TCPServerWidget);

        QMetaObject::connectSlotsByName(TCPServerWidget);
    } // setupUi

    void retranslateUi(QWidget *TCPServerWidget)
    {
        TCPServerWidget->setWindowTitle(QCoreApplication::translate("TCPServerWidget", "Form", nullptr));
        toHex->setText(QCoreApplication::translate("TCPServerWidget", "hex", nullptr));
        listen->setText(QCoreApplication::translate("TCPServerWidget", "listen", nullptr));
        close->setText(QCoreApplication::translate("TCPServerWidget", "close", nullptr));
        send->setText(QCoreApplication::translate("TCPServerWidget", "send", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TCPServerWidget", "ip", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TCPServerWidget", "port", nullptr));
        clear->setText(QCoreApplication::translate("TCPServerWidget", "clear", nullptr));
        label->setText(QCoreApplication::translate("TCPServerWidget", "\345\256\242\346\210\267\347\253\257\344\277\241\346\201\257\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("TCPServerWidget", "\345\215\201\345\205\255\350\277\233\345\210\266\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("TCPServerWidget", "\346\270\205\351\231\244\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("TCPServerWidget", "\346\225\260\346\215\256\345\214\205\347\274\226\345\217\267\357\274\232", nullptr));
        label_PACKET_CNT->setText(QCoreApplication::translate("TCPServerWidget", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("TCPServerWidget", "\350\256\276\345\244\207ID\345\217\267\357\274\232", nullptr));
        label_DEV_ID->setText(QCoreApplication::translate("TCPServerWidget", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("TCPServerWidget", "\347\224\265\346\261\240\347\224\265\345\216\213\345\200\274\357\274\232", nullptr));
        label_BATT_VOLT->setText(QCoreApplication::translate("TCPServerWidget", "TextLabel", nullptr));
        btn_OPEN_LED0->setText(QCoreApplication::translate("TCPServerWidget", "\346\211\223\345\274\200", nullptr));
        label_7->setText(QCoreApplication::translate("TCPServerWidget", "LED\346\216\247\345\210\266\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCPServerWidget: public Ui_TCPServerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVERWIDGET_H
