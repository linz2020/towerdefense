#include "Enemy.h"
#include <QPoint>
#include <QVector>
#include <QDebug>
Enemy::Enemy(CoorStr **point,int arrlen,int x,int y,int id):mx(x),my(y),mid(id)
{
    for(int i=0;i<arrlen;i++)
        Waypoint.push_back(point[i]);

    switch (mid)
    {
    case 1:
        HP=100;
        ImgPath=":/images/enemy1.png";
        break;
    case 2:
        HP=150;
        ImgPath=":/images/enemy2.png";
        break;
    case 3:
        HP=200;
        ImgPath=":/images/enemy3.png";
        break;
    case 4:
        HP=250;
        ImgPath=":/images/enemy4.png";
        break;
    case 5:
        HP=300;
        ImgPath=":/images/enemy5.png";
        break;
    default:
        break;
    }
}

bool Enemy::Move()
{
    if(Waypoint.empty())
        return true;

    //第一个路径点的纵坐标比小怪兽的小，小怪兽向上走
    if (Waypoint.at(0)->y<my) //上
    {
        my-=speed;
        return false;
    }
    if (Waypoint.at(0)->y>my) //下
    {
        my+=speed;
        return false;
    }
    if (Waypoint.at(0)->x<mx) //左
    {
        mx-=speed;
        return false;
    }
    if (Waypoint.at(0)->x>mx) //右
    {
        mx+=speed;
        return false;
    }

    //当小怪兽的坐标和路径点坐标重合时,删除此路径点，这样下一个路径点就会是第一个路径点
    if (Waypoint.at(0)->y==my&&Waypoint.at(0)->x==mx)
    {
        delete Waypoint.begin();                //释放内存
        Waypoint.erase(Waypoint.begin());       //从数组中删除
    }
    return false;
}


int Enemy::getX() const
{
    return mx;
}

int Enemy::getY() const
{
    return my;
}

int Enemy::getID() const
{
    return mid;
}

int Enemy::getHP() const
{
    return HP;
}

void Enemy::setHP(int hp)
{
    HP=hp;
}

QString Enemy::getImgPath() const
{
    return ImgPath;
}

