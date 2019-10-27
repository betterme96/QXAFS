#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <recvdata.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();
private slots:
    void on_start_btn_clicked();

    void on_stop_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
