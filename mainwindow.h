#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "new_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace Ui {class new_window;}
QT_END_NAMESPACE
using namespace std;
class new_window;//报错的解决方法

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    new_window *new_win;
protected:
    void paintEvent(QPaintEvent *);


private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
