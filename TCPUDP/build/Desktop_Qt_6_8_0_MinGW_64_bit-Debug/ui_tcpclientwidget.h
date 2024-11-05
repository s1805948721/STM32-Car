/********************************************************************************
** Form generated from reading UI file 'tcpclientwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENTWIDGET_H
#define UI_TCPCLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCPClientWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *localIp;
    QSpinBox *localPort;
    QCheckBox *bind;
    QSpacerItem *horizontalSpacer;
    QLineEdit *serverIp;
    QSpinBox *serverPort;
    QPushButton *connect;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *message;
    QPushButton *send;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *toHex;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *clear;

    void setupUi(QWidget *TCPClientWidget)
    {
        if (TCPClientWidget->objectName().isEmpty())
            TCPClientWidget->setObjectName("TCPClientWidget");
        TCPClientWidget->resize(612, 374);
        verticalLayout = new QVBoxLayout(TCPClientWidget);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName("horizontalLayout");
        localIp = new QComboBox(TCPClientWidget);
        localIp->setObjectName("localIp");
        localIp->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(localIp);

        localPort = new QSpinBox(TCPClientWidget);
        localPort->setObjectName("localPort");
        localPort->setMinimum(1);
        localPort->setMaximum(65535);

        horizontalLayout->addWidget(localPort);

        bind = new QCheckBox(TCPClientWidget);
        bind->setObjectName("bind");

        horizontalLayout->addWidget(bind);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        serverIp = new QLineEdit(TCPClientWidget);
        serverIp->setObjectName("serverIp");

        horizontalLayout->addWidget(serverIp);

        serverPort = new QSpinBox(TCPClientWidget);
        serverPort->setObjectName("serverPort");
        serverPort->setMinimum(1);
        serverPort->setMaximum(65535);

        horizontalLayout->addWidget(serverPort);

        connect = new QPushButton(TCPClientWidget);
        connect->setObjectName("connect");

        horizontalLayout->addWidget(connect);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        message = new QLineEdit(TCPClientWidget);
        message->setObjectName("message");

        horizontalLayout_2->addWidget(message);

        send = new QPushButton(TCPClientWidget);
        send->setObjectName("send");

        horizontalLayout_2->addWidget(send);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        toHex = new QCheckBox(TCPClientWidget);
        toHex->setObjectName("toHex");

        horizontalLayout_3->addWidget(toHex);


        verticalLayout->addLayout(horizontalLayout_3);

        textEdit = new QTextEdit(TCPClientWidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        clear = new QPushButton(TCPClientWidget);
        clear->setObjectName("clear");

        horizontalLayout_4->addWidget(clear);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(TCPClientWidget);

        QMetaObject::connectSlotsByName(TCPClientWidget);
    } // setupUi

    void retranslateUi(QWidget *TCPClientWidget)
    {
        TCPClientWidget->setWindowTitle(QCoreApplication::translate("TCPClientWidget", "Form", nullptr));
        bind->setText(QCoreApplication::translate("TCPClientWidget", "bind", nullptr));
        serverIp->setInputMask(QCoreApplication::translate("TCPClientWidget", "000.000.000.000", nullptr));
        connect->setText(QCoreApplication::translate("TCPClientWidget", "connect", nullptr));
        send->setText(QCoreApplication::translate("TCPClientWidget", "send", nullptr));
        toHex->setText(QCoreApplication::translate("TCPClientWidget", "hex", nullptr));
        clear->setText(QCoreApplication::translate("TCPClientWidget", "clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCPClientWidget: public Ui_TCPClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENTWIDGET_H
