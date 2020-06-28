#include "Enemy.h"
#include <QPoint>
#include <QVector>
#include <QDebug>
Enemy::Enemy(CoorStr **point,int arrlen,int x,int y,int id):
    mx(x),my(y),mid(id)
{
    for(int i=0;i<arrlen;i++)
        Waypoint.push_back(point[i]);

    switch (mid)
    {
    case 1:
        HP=300;
        speed=10;
        ImgPath=":/images/enemy1.png";
        break;
    case 2:
        HP=400;
        speed=20;
        ImgPath=":/images/enemy2.png";
        break;
    case 3:
        HP=500;
        speed=10;
        ImgPath=":/images/enemy3.png";
        break;
    case 4:
        HP=500;
        speed=20;
        ImgPath=":/images/enemy4.png";
        break;
    case 5:
        HP=600;
        speed=20;
        ImgPath=":/images/enemy5.png";
        break;
    default:
        break;
    }
}

void Enemy::setHP(int hp)
{
    HP=hp;
}

bool Enemy::Move()
{
    if(Waypoint.empty())
        return true;
    else
    {
        //第一个路径点的纵坐标比小怪兽的小，小怪兽向上走
        if (Waypoint.at(0)->y<my)
            my-=speed;

        if (Waypoint.at(0)->y>my) //下
            my+=speed;

        if (Waypoint.at(0)->x<mx) //左
            mx-=speed;

        if (Waypoint.at(0)->x>mx) //右
            mx+=speed;

        //当小怪兽的坐标和路径点坐标重合时,删除此路径点，这样下一个路径点就会是第一个路径点
        if (Waypoint.at(0)->x==mx&&Waypoint.at(0)->y==my)
        {
            delete Waypoint.begin();
            Waypoint.erase(Waypoint.begin());
        }

        return false;
    }
}
