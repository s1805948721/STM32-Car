/********************************************************************************
** Form generated from reading UI file 'udpwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPWIDGET_H
#define UI_UDPWIDGET_H

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

class Ui_UDPWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *localIp_2;
    QSpinBox *localPort_2;
    QPushButton *bind;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *serverIp;
    QSpinBox *serverPort;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *message_2;
    QPushButton *send_2;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *toHex_2;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *clear_2;

    void setupUi(QWidget *UDPWidget)
    {
        if (UDPWidget->objectName().isEmpty())
            UDPWidget->setObjectName("UDPWidget");
        UDPWidget->resize(683, 364);
        verticalLayout = new QVBoxLayout(UDPWidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        localIp_2 = new QComboBox(UDPWidget);
        localIp_2->setObjectName("localIp_2");
        localIp_2->setMinimumSize(QSize(120, 0));

        horizontalLayout_7->addWidget(localIp_2);

        localPort_2 = new QSpinBox(UDPWidget);
        localPort_2->setObjectName("localPort_2");
        localPort_2->setMinimum(1);
        localPort_2->setMaximum(65535);

        horizontalLayout_7->addWidget(localPort_2);

        bind = new QPushButton(UDPWidget);
        bind->setObjectName("bind");

        horizontalLayout_7->addWidget(bind);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        serverIp = new QLineEdit(UDPWidget);
        serverIp->setObjectName("serverIp");
        serverIp->setMinimumSize(QSize(120, 0));

        horizontalLayout_7->addWidget(serverIp);

        serverPort = new QSpinBox(UDPWidget);
        serverPort->setObjectName("serverPort");
        serverPort->setMinimum(1);
        serverPort->setMaximum(65535);

        horizontalLayout_7->addWidget(serverPort);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        message_2 = new QLineEdit(UDPWidget);
        message_2->setObjectName("message_2");

        horizontalLayout_6->addWidget(message_2);

        send_2 = new QPushButton(UDPWidget);
        send_2->setObjectName("send_2");

        horizontalLayout_6->addWidget(send_2);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        toHex_2 = new QCheckBox(UDPWidget);
        toHex_2->setObjectName("toHex_2");

        horizontalLayout_8->addWidget(toHex_2);


        verticalLayout->addLayout(horizontalLayout_8);

        textEdit = new QTextEdit(UDPWidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        clear_2 = new QPushButton(UDPWidget);
        clear_2->setObjectName("clear_2");

        horizontalLayout_5->addWidget(clear_2);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(UDPWidget);

        QMetaObject::connectSlotsByName(UDPWidget);
    } // setupUi

    void retranslateUi(QWidget *UDPWidget)
    {
        UDPWidget->setWindowTitle(QCoreApplication::translate("UDPWidget", "Form", nullptr));
        bind->setText(QCoreApplication::translate("UDPWidget", "bind", nullptr));
        serverIp->setInputMask(QCoreApplication::translate("UDPWidget", "000.000.000.000", nullptr));
        send_2->setText(QCoreApplication::translate("UDPWidget", "send", nullptr));
        toHex_2->setText(QCoreApplication::translate("UDPWidget", "hex", nullptr));
        clear_2->setText(QCoreApplication::translate("UDPWidget", "clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UDPWidget: public Ui_UDPWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPWIDGET_H
