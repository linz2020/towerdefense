#ifndef TOWER_H
#define TOWER_H

#include <QString>
#include <QPoint>
#include "Enemy.h"
#include <math.h>

//两点间距离
#define PointsDistance(X1,Y1,X2,Y2)           \
abs(sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2)))

class TowerBase
{
public:
    int bx;
    int by;
    int bwidth;
    int bheight;
    TowerBase(int x,int y,int width = 80,int height = 80):
        bx(x), by(y), bwidth(width), bheight(height) {}
};

class bullet
{
public:
    CoorStr coor;
    const int bulspeed = 30;
    int tan;//方向
    int v;//vertical
    bool direct;
    bullet(CoorStr bulcoor,int btan=0,int bv=0,bool flag=false):
        coor(bulcoor),tan(btan),v(bv),direct(flag){}
};

class tower
{
public:
    int tx;
    int ty;
    int twidth;
    int theight;
    QString TowImgPath;
    qreal RotateAngle=0;     //旋转角度
    //塔的中心点
    int centerx;
    int centery;
    int Range;
    int attack;        //攻击力

    Enemy* target = NULL;//记录目标怪物

    int bullwidth=40;
    int bullheight=40;
    QString BullPath;
    int damage;
    int bcounter = 0;        //控制子弹的发射
    QVector<bullet*> BulletVec;

    void SetRotateAngle(qreal);

    Enemy* GetTarget() const;//返回当前目标
    void SetTarget(Enemy*);

    QVector<bullet*> GetBulletVec();//返回子弹数组
    void ShootBullet();
    void BulletMove();

};

class CommonTower1:public tower
{
public:
    CommonTower1(int x,int y,int CenterX,int CenetrY,int width,int height);
};

class CommonTower2:public tower
{
public:
    CommonTower2(int x,int y,int CenetrX,int CenterY,int width,int height);
};

class FireTower:public tower
{
public:
    FireTower(int x,int y,int CenterX,int CenterY,int width,int height);
};

class LightTower:public tower
{
public:
    LightTower(int x,int y,int CenterX, int CenterY,int width,int height);
};

#endif // TOWER_H
