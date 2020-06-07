#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/images/startbg.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    new_win = new new_window(1);
    new_win->setWindowTitle("第一关");
    new_win->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    new_win = new new_window(2);
    new_win->setWindowTitle("第二关");
    new_win->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    new_win = new new_window(3);
    new_win->setWindowTitle("第三关");
    new_win->show();
}
