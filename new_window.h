#ifndef NEW_WINDOW_H
#define NEW_WINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QVector>
#include <QTimer>
#include "Enemy.h"
#include "mainwindow.h"
#include "tower.h"
#include "choice.h"

//鼠标点击区域
#define MouseClickRegion(X,Width,Y,Height)     \
( mp->x()>=X && mp->x()<=X+Width &&  \
mp->y()>=Y&& mp->y()<=Y+Height )

//插入怪物  路径点数组和小怪兽的编号
#define InsertEnemy(PathId,StartCoorId,EnemyId)     \
EnemyVec.push_back(new Enemy(pointarr[PathId],pointnum[PathId],stc[StartCoorId].x,stc[StartCoorId].y, EnemyId));

namespace Ui {
class new_window;
}


class new_window : public QMainWindow
{
public:
    explicit new_window(QWidget *parent = nullptr);
    new_window(int level);
    ~new_window();
    Ui::new_window *ui;

    const int level;
    int money=1000;     //初始金币
    int life=20;        //初始生命值
    const int bonus=50;
    //各种lable
    QLabel *moneylb=new QLabel(this);
    QLabel *lifelb=new QLabel(this);
    QLabel *victorylb=new QLabel(this);
    QLabel *loselb=new QLabel(this);

    QTimer* timer = new QTimer(this);
    QTimer* timer2=new QTimer(this);
    QTimer* timer3=new QTimer(this);

    CoorStr *icecoor=new CoorStr(0,0);
    SelectionBox* SelBox = new SelectionBox(":/images/choice.png"); //选择框类

    QVector<TowerBase*> TowerBaseVec;  //塔基数组
    QVector<tower*> TowerVec; //塔数组
    QVector<Enemy*> EnemyVec; //小怪兽数组

    int counter=0;    //用于产生小怪兽的计数器
    CoorStr stc[];  //小怪兽路径的起始点坐标

    bool buyingtower(int);//判断现有金币是否足够购买塔
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

    void DrawMap(QPainter&);
    void DrawEnemy(QPainter&);
    void DrawChoiceBoxes(QPainter&);
    void DrawTower(QPainter&);

    //重载
    void EnemyRoute(CoorStr**,CoorStr*,int*);//一条路径产生小怪兽
    void EnemyRoute(CoorStr**,CoorStr**,CoorStr*,int*); //两条路径

    void chooseEnemy(tower*);
    void attackEnemy(tower*);
};

#endif // NEW_WINDOW_H
