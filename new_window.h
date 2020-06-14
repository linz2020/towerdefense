#ifndef NEW_WINDOW_H
#define NEW_WINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include "Enemy.h"
#include "mainwindow.h"

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

    //各种lable
    QLabel *moneylb=new QLabel(this);
    QLabel *lifelb=new QLabel(this);
    QLabel *victorylb=new QLabel(this);
    QLabel *loselb=new QLabel(this);

    void paintEvent(QPaintEvent *);         //绘图事件
    //void mousePressEvent(QMouseEvent *);    //鼠标点击事件

    void DrawMap(QPainter&);
    void DrawEnemy(QPainter&);

    CoorStr *icecoor=new CoorStr(0,0);

    QVector<Enemy*> EnemyVec;    //小怪兽数组
    int counter=0;    //用于产生小怪兽的计数器

    CoorStr stc[];
    //重载
    void EnemyRoute(CoorStr**,CoorStr*,int*);//一条路径产生小怪兽
    void EnemyRoute(CoorStr**,CoorStr**,CoorStr*,int*); //两条路径

};

#endif // NEW_WINDOW_H
