#include "tcpclientwidget.h"
#include "common.h"
#include "ui_tcpclientwidget.h"
#include <QFutureWatcher>
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>

TCPClientWidget::TCPClientWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TCPClientWidget) {
    ui->setupUi(this);
    ui->localIp->addItems(getIPAddresses());
    m_Socket = new QTcpSocket;
    connect(m_Socket, &QTcpSocket::disconnected, [=]() {
        ui->connect->setText("connect");
        appendLog(ui->textEdit, "disconnect");
    });
    connect(m_Socket, &QTcpSocket::readyRead, [=]() {
        QByteArray data = (ui->toHex->isChecked()) ? m_Socket->readAll().toHex()
                                                   : m_Socket->readAll();
        appendLog(ui->textEdit, QString(data));
    });
}

TCPClientWidget::~TCPClientWidget() {
    delete ui;
}

void TCPClientWidget::on_connect_clicked() {
    if ("connect" == ui->connect->text()) {
        if (ui->bind->isChecked()) {
            if (!m_Socket->bind(QHostAddress(ui->localIp->currentText()),
                                ui->localPort->value())) {
                appendLog(ui->textEdit,
                          "bind error:" + m_Socket->errorString());
                return;
            }
        }
        ui->connect->setEnabled(false);
        m_Socket->connectToHost(QHostAddress(ui->serverIp->text()),
                                ui->serverPort->value());
        if (m_Socket->waitForConnected()) {
            ui->connect->setText("disconnect");

            appendLog(ui->textEdit, "connect");
        } else
            appendLog(ui->textEdit, "connect error:" + m_Socket->errorString());
        ui->connect->setEnabled(true);
    } else {
        m_Socket->close();
        m_Socket->disconnectFromHost();
        ui->connect->setText("connect");
        appendLog(ui->textEdit, "disconnect");
    }
}

void TCPClientWidget::on_send_clicked() {
    QByteArray data = (ui->toHex->isChecked())
        ? QByteArray::fromHex(ui->message->text().toUtf8())
        : ui->message->text().toUtf8();
    if (m_Socket->isOpen()) m_Socket->write(data, data.size());
}

void TCPClientWidget::on_clear_clicked() {
    ui->textEdit->clear();
}
