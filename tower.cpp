#include "tower.h"

void tower::SetRotateAngle(qreal angle)
{
    RotateAngle=angle;
}

Enemy* tower::GetTarget() const
{
    return target;
}

void tower::SetTarget(Enemy* emy)
{
    target=emy;
}

QVector<bullet*> tower::GetBulletVec()//返回子弹数组
{
    return BulletVec;
}

void tower::ShootBullet()
{
    bcounter++;
    if(bcounter<5||target==NULL)
        return;

    CoorStr coor(centerx,centery);
    bullet *bull=new bullet(coor,0,0,false);
    bull->coor.x=centerx;
    bull->coor.y=centery;

    if(target->mx-bull->coor.x==0)
    {
        delete bull;
        bull = NULL;
        goto L1;
    }

    bull->tan=(target->my-bull->coor.y)/(target->mx-bull->coor.x);
    bull->v=target->my-target->mx*bull->tan;

    bull->coor.x=centerx;
    bull->coor.y=centery;

    BulletVec.push_back(bull);

    if(target->mx<=centerx) //确定子弹的移动方向
        bull->direct=true;

    L1:
        bcounter = 0;    //计数器重置

}


void tower::BulletMove()
{
    for(auto i:BulletVec)
    {
        if(i->direct==true)
            i->coor.x-=i->bulspeed; //左边
        else
            i->coor.x+=i->bulspeed; //右边

        i->coor.y=i->tan*i->coor.x+i->v;  //纵坐标

        if(PointsDistance(i->coor.x,i->coor.y,this->centerx,this->centery)
                > this->Range)
            BulletVec.removeOne(i);

    }

}

CommonTower1::CommonTower1(int x,int y,int CenterX,int CenterY,int width,int height)
{
    tx=x;
    ty=y;
    twidth=width;
    theight=height;
    TowImgPath=QString(":/images/common1.png");
    Range=150;
    attack=50;
    centerx=CenterX;
    centery=CenterY;
    BullPath=QString(":/images/bullet1.png");
}

CommonTower2::CommonTower2(int x,int y,int CenterX,int CenterY,int width,int height)
{
    tx=x;
    ty=y;
    twidth=width;
    theight=height;
    TowImgPath=QString(":/images/common2.png");
    Range=150;
    attack=100;
    centerx=CenterX;
    centery=CenterY;
    BullPath=QString(":/images/bullet2.png");
}

FireTower::FireTower(int x,int y,int CenterX,int CenterY,int width,int height)
{
    tx=x;
    ty=y;
    twidth=width;
    theight=height;
    TowImgPath=QString(":/images/firecannon.png");
    Range=200;
    attack=150;
    centerx=CenterX;
    centery=CenterY;
    BullPath=QString(":/images/bullet3.png");
}

LightTower::LightTower(int x,int y,int CenterX,int CenterY,int width,int height)
{
    tx=x;
    ty=y;
    twidth=width;
    theight=height;
    TowImgPath=QString(":/images/lightcannon.png");
    Range=200;
    attack=200;
    centerx=CenterX;
    centery=CenterY;
    BullPath=QString(":/images/bullet4.png");
}
