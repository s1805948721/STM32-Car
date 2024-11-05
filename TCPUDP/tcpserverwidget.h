#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H
#include <QWidget>
///////////////////////////////////////////////////////////
#define POS_HEADER0                   0
#define POS_HEADER1                   1
#define POS_DEV_ID                    2
#define POS_PKG_CNT                   3
#define POS_BATT_VOLT_H               4
#define POS_BATT_VOLT_L               5
///////////////////////////////////////////////////////////
namespace Ui {
class TCPServerWidget;
}
class QTcpServer;
class QTcpSocket;
class TCPServerWidget : public QWidget {
    Q_OBJECT
public:
    explicit TCPServerWidget(QWidget *parent = nullptr);
    ~TCPServerWidget();

private:
    QTcpSocket *socket(int row);
private slots:
    void on_listen_clicked();
    void on_close_clicked();
    void on_send_clicked();
    void on_clear_clicked();

    void on_btn_OPEN_LED0_clicked();

private:
    Ui::TCPServerWidget *ui;
    QTcpServer *m_Server;
    QList<QTcpSocket *> m_Clients;
    quint16 crc16_ibm(QByteArray crcdata, quint16 length);
    void PrintState(QByteArray package);
};
#endif // TCPSERVERWIDGET_H
