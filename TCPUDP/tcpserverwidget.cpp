#include "tcpserverwidget.h"
#include "common.h"
#include "ui_tcpserverwidget.h"
#include <QHeaderView>
#include <QTcpServer>
#include <QTcpSocket>
TCPServerWidget::TCPServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TCPServerWidget) {
    ui->setupUi(this);
    ui->localIp->addItem("Any");
    ui->localIp->addItems(getIPAddresses());
    ui->clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    m_Server = new QTcpServer;
    //////////////////////////////////////////////////////////////////////////////////////////
    connect(m_Server, &QTcpServer::newConnection, [=]() {
        QTcpSocket *tcpSocket = m_Server->nextPendingConnection();
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
        appendLog(ui->textEdit, QString("%1:%2:connect").arg(ip).arg(port));
        bool r = false;
        for (int i = 0; i < ui->clientTable->rowCount(); ++i) {
            QTableWidgetItem *ipitem = ui->clientTable->item(i, 0);
            QTableWidgetItem *portitem = ui->clientTable->item(i, 1);
            if (nullptr != ipitem && nullptr != portitem &&
                ipitem->text() == ip && portitem->text().toUShort() == port) {
                r = true;
                break;
            }
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        connect(tcpSocket, &QTcpSocket::disconnected, [=]() {
            appendLog(ui->textEdit,
                      QString("%1:%2 disconnected")
                          .arg(tcpSocket->peerAddress().toString())
                          .arg(tcpSocket->peerPort()));
            for (int i = 0; i < ui->clientTable->rowCount(); ++i) {
                QTableWidgetItem *ipitem = ui->clientTable->item(i, 0);
                QTableWidgetItem *portitem = ui->clientTable->item(i, 1);
                if (nullptr != ipitem && nullptr != portitem &&
                    ipitem->text() == ip &&
                    portitem->text().toUShort() == port) {
                    ui->clientTable->removeRow(i);
                    break;
                }
            }
            for (QTcpSocket *socket : m_Clients) {
                if (ip == socket->peerAddress().toString() &&
                    port == socket->peerPort()) {
                    m_Clients.removeOne(socket);
                    socket = nullptr;
                    break;
                }
            }
        });
        ///////////////////////////////////////////////////////////
        //////////////////////接收数据//////////////////////////////
        ///////////////////////////////////////////////////////////
        connect(tcpSocket, &QTcpSocket::readyRead, [=]()
        {
            QByteArray data = tcpSocket->readAll();
            PrintState(data);
            if(ui->toHex->isChecked())
            {
                data = data.toHex();
            }
            appendLog(ui->textEdit,
                      QString("%1:%2:%3").arg(ip).arg(port).arg(QString(data)));
        });
        /*connect(tcpSocket, &QTcpSocket::readyRead, [=]()
        {
            QByteArray data = (ui->toHex->isChecked())
                ? tcpSocket->readAll().toHex()
                : tcpSocket->readAll();
            appendLog(ui->textEdit,
                      QString("%1:%2:%3").arg(ip).arg(port).arg(QString(data)));
             PrintState(data);
        });*/
        //////////////////////////////////////////////////////////
        m_Clients.append(tcpSocket);
        int row = ui->clientTable->rowCount();
        ui->clientTable->insertRow(row);
        ui->clientTable->setItem(row, 0, new QTableWidgetItem(ip));
        ui->clientTable->setItem(row, 1,
                                 new QTableWidgetItem(QString::number(port)));

    });
}

TCPServerWidget::~TCPServerWidget() {
    delete ui;
}

QTcpSocket *TCPServerWidget::socket(int row) {
    QTableWidgetItem *ipitem = ui->clientTable->item(row, 0);
    QTableWidgetItem *portitem = ui->clientTable->item(row, 1);
    if (nullptr != ipitem && nullptr != portitem) {
        QString ip = ipitem->text();
        quint16 port = portitem->text().toUShort();
        for (QTcpSocket *tcpSocket : m_Clients) {
            if (ip == tcpSocket->peerAddress().toString() &&
                port == tcpSocket->peerPort())
                return tcpSocket;
        }
    }
    return nullptr;
}

void TCPServerWidget::on_listen_clicked() {

    if (ui->listen->text() == "listen") {
        if (m_Server->listen((ui->localIp->currentText() == "Any")
                                 ? QHostAddress::Any
                                 : QHostAddress(ui->localIp->currentText()),
                             ui->localPort->value())) {
            ui->listen->setText("listening");
            appendLog(ui->textEdit, "start listening");
        } else {
            appendLog(ui->textEdit,
                      "start listen error:" + m_Server->errorString());
        }
    } else {
        m_Server->close();
        ui->listen->setText("listen");
        for (QTcpSocket *tcpSocket : m_Clients) {
            tcpSocket->close();
            tcpSocket->disconnectFromHost();
        }
        m_Clients.clear();
        appendLog(ui->textEdit, "stop listening");
    }
}

void TCPServerWidget::on_close_clicked() {
    int row = ui->clientTable->currentRow();
    QTcpSocket *tcpSocket = socket(row);
    if (nullptr != tcpSocket) {
        tcpSocket->close();
        tcpSocket->disconnectFromHost();
    }
}

void TCPServerWidget::on_send_clicked() {
    QByteArray data = (ui->toHex->isChecked())
        ? QByteArray::fromHex(ui->message->text().toUtf8())
        : ui->message->text().toUtf8();
    int row = ui->clientTable->currentRow();
    QTcpSocket *tcpSocket = socket(row);
    if (nullptr != tcpSocket)tcpSocket->write(data, data.size());
}

void TCPServerWidget::on_clear_clicked() {
    ui->textEdit->clear();
}

void TCPServerWidget::PrintState(QByteArray package)
{
    char *buf;
    int len;
    unsigned int data;
    float float_data;
    QString rbytes;
    qint16 Rcrc;
    buf = package.data();
    len = package.size();
    if(((unsigned char)buf[0]!=0xAA)||((unsigned char)buf[1]!=0xCC))
    {
        return;
    }
    Rcrc=crc16_ibm(package, len-2);//计算数据包的CRC校验值
    if(((package.at(len-2)&0xff)!=((Rcrc>>8)&0xff)) || ((package.at(len-1)&0xff)!=(Rcrc&0xff)))//CRC校验错误
    {
        return;
    }
    //设备ID
    data = ((unsigned char)buf[POS_DEV_ID])&0xff;
    rbytes=rbytes.asprintf("%d",data);
    ui->label_DEV_ID->setText(rbytes);
    //包计数器
    data = ((unsigned char)buf[POS_PKG_CNT])&0xff;
    rbytes=rbytes.asprintf("%d",data);
    ui->label_PACKET_CNT->setText(rbytes);
    //电池电压
    data = ((unsigned char)buf[POS_BATT_VOLT_H]*256)+(unsigned char)buf[POS_BATT_VOLT_L];
    float_data = (float)(3.3*2*data/4096);
    rbytes=rbytes.asprintf("%5.3f",float_data);
    ui->label_BATT_VOLT->setText(rbytes);
}

quint16 TCPServerWidget::crc16_ibm(QByteArray crcdata, quint16 length)
{
    quint8 i,data;
    quint16 j=0;
    quint16 crc = 0;        // Initial value
    while(length--)
    {
        data=crcdata.at(j++);
        crc ^= data;        // crc ^= *data; data++;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001;        // 0xA001 = reverse 0x8005
            else
                crc = (crc >> 1);
        }
    }
    return crc;
}

void TCPServerWidget::on_btn_OPEN_LED0_clicked()
{
    QByteArray sendStr;
    quint16 tcrc;
    sendStr.append(24,char(0x0));
    sendStr[0]=0xAA;
    sendStr[1]=0xCC;
    sendStr[2]=0x01;//DEV_ID
    sendStr[3]=0x01;//CMD_ID
    if(ui->btn_OPEN_LED0->text()=="打开")
    {
        sendStr[4]=0x01;
        ui->btn_OPEN_LED0->setText("关闭");
        ui->btn_OPEN_LED0->setStyleSheet(QString("background-color:") + "green");
    }else if(ui->btn_OPEN_LED0->text()=="关闭")
    {
        sendStr[4]=0x00;
        ui->btn_OPEN_LED0->setText("打开");
        ui->btn_OPEN_LED0->setStyleSheet(QString("background-color:") + "white");
    }else
    {
        return;
    }
    tcrc=crc16_ibm(sendStr, 22);
    sendStr[22]=uchar(tcrc>>8);
    sendStr[23]=uchar(tcrc);

    int row = ui->clientTable->currentRow();
    QTcpSocket *tcpSocket = socket(row);
    if (nullptr != tcpSocket)tcpSocket->write(sendStr);
    //serial.write(sendStr);
}
