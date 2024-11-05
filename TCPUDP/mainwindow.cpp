#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("智能小车监控软件");
  resize(900,680);
}

MainWindow::~MainWindow() { delete ui; }
