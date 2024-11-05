#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include <QWidget>

namespace Ui {
class UDPWidget;
}

class QUdpSocket;
class UDPWidget : public QWidget {
  Q_OBJECT

 public:
  explicit UDPWidget(QWidget *parent = nullptr);
  ~UDPWidget();

 private slots:
  void on_bind_clicked();

  void on_send_2_clicked();

  void on_clear_2_clicked();

 private:
  Ui::UDPWidget *ui;
  QUdpSocket *m_Socket;
};

#endif  // UDPWIDGET_H
