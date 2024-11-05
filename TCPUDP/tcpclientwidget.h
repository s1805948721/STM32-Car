#ifndef TCPCLIENTWIDGET_H
#define TCPCLIENTWIDGET_H

#include <QWidget>

namespace Ui {
class TCPClientWidget;
}

class QTcpSocket;
class TCPClientWidget : public QWidget {
    Q_OBJECT

public:
    explicit TCPClientWidget(QWidget *parent = nullptr);
    ~TCPClientWidget();

private slots:
    void on_connect_clicked();

    void on_send_clicked();

    void on_clear_clicked();

private:
    Ui::TCPClientWidget *ui;
    QTcpSocket *m_Socket;
};

#endif // TCPCLIENTWIDGET_H
