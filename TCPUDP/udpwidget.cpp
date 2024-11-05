#include "udpwidget.h"
#include <QUdpSocket>
#include "common.h"
#include "ui_udpwidget.h"

UDPWidget::UDPWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UDPWidget) {
  ui->setupUi(this);
  ui->localIp_2->addItems(getIPAddresses());
  m_Socket = new QUdpSocket;
  connect(m_Socket, &QUdpSocket::readyRead, [=]() {
    while (m_Socket->hasPendingDatagrams()) {
      QByteArray data;
      QHostAddress host;
      quint16 port;
      data.resize(m_Socket->pendingDatagramSize());
      m_Socket->readDatagram(data.data(), data.size(), &host, &port);
      data = (ui->toHex_2->isChecked()) ? data.toHex() : data;
      appendLog(ui->textEdit, QString("%1:%2:%3")
                                  .arg(host.toString())
                                  .arg(port)
                                  .arg(QString(data)));
    }
  });
}

UDPWidget::~UDPWidget() { delete ui; }

void UDPWidget::on_bind_clicked() {
  if (ui->bind->text() == "bind") {
    if (m_Socket->bind(QHostAddress(ui->localIp_2->currentText()),
                       ui->localPort_2->value()))
      ui->bind->setText("unbind");
    else
      appendLog(ui->textEdit, "bind error:" + m_Socket->errorString());
  } else {
    m_Socket->abort();
    ui->bind->setText("bind");
  }
}

void UDPWidget::on_send_2_clicked() {
  QByteArray data = (ui->toHex_2->isChecked())
                        ? QByteArray::fromHex(ui->message_2->text().toUtf8())
                        : ui->message_2->text().toUtf8();
  m_Socket->writeDatagram(data, QHostAddress(ui->serverIp->text()),
                          ui->serverPort->value());
}

void UDPWidget::on_clear_2_clicked() { ui->textEdit->clear(); }
