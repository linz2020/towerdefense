#ifndef NEW_WINDOW_H
#define NEW_WINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>

//coordinate struct
struct CoorStr
{
    int x;
    int y;
    CoorStr(int x1,int y1):x(x1),y(y1) {}
};

namespace Ui {
class new_window;
}

class new_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_window(QWidget *parent = nullptr);
    new_window(int level);
    ~new_window();

private:
    Ui::new_window *ui;

    const int level;
    int money=1000;     //初始金钱
    int life=10;        //初始生命值

    QLabel *moneylb=new QLabel(this);   //显示金钱
    QLabel *lifelb=new QLabel(this);    //显示生命值

    void paintEvent(QPaintEvent *);         //绘图事件
    //void mousePressEvent(QMouseEvent *);    //鼠标点击事件

    void DrawMap(QPainter&);
    //void DrawMonster(QPainter&);

    CoorStr *icecoor=new CoorStr(0,0);

};

#endif // NEW_WINDOW_H
