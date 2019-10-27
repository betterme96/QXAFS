#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string.h>
#include <QDesktopWidget>
#include <QDate>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,800);
    this->setWindowTitle("QXAFS");
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width()-this->width())/2,
               (desktop->height()-this->height())/2);
    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    ui->ctrWidget->setObjectName("ctrwidget");
    ui->ctrWidget->setStyleSheet("QWidget#ctrwidget{border:2px outset #C0C0C0}");

    ui->dspWidget->setObjectName("dspwidget");
    ui->dspWidget->setStyleSheet("QWidget#dspwidget{border:2px outset #C0C0C0}");

    ui->tabWidget->setObjectName("tabwidget");
    ui->tabWidget->setStyleSheet("QWidget#tabwidget{border:2px outset #C0C0C0}");

    ui->infoWidget->setObjectName("datawidget");
    ui->infoWidget->setStyleSheet("QWidget#datawidget{border:2px outset #C0C0C0}");
}



void MainWindow::on_start_btn_clicked()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString str = curTime.toString("MM.dd hh:mm:ss:zzz");
    ui->start_time->setText(str);
    ui->start_time->setFocusPolicy(Qt::NoFocus);
    ui->start_btn->setEnabled(false);
    ui->stop_btn->setEnabled(true);

    RecvData recvData;
    std::string server_ip = ui->SERVER_IP->text().toStdString();
    std::string filename = curTime.toString("yyyyMMddhhmmss").toStdString();
    recvData.getData(server_ip,filename);
}

void MainWindow::on_stop_btn_clicked()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString str = curTime.toString("MM.dd hh:mm:ss:zzz");
    ui->stop_time->setText(str);
    ui->stop_time->setFocusPolicy(Qt::NoFocus);
    ui->stop_btn->setEnabled(false);
    ui->start_btn->setEnabled(true);
}
