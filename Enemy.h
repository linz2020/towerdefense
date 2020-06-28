#ifndef ENEMY_H
#define ENEMY_H

#include <QPixmap>
#include <QPainter>
#include <QVector>

struct CoorStr
{
    int x;
    int y;
    CoorStr(int x1,int y1):x(x1),y(y1) {}
};
//QPoint搞出bug了...

class Enemy
{
public:
    //monster
    int mx;
    int my;
    int mid;
    const int mwidth=80;
    const int mheight=80;
    int HP;
    int speed;//每次移动的长度
    QString ImgPath;
    QVector<CoorStr*> Waypoint;  //小怪兽路径点数组

    Enemy(CoorStr **point,int arrlen,int x,int y,int id);
    void setHP(int);
    bool Move();//小怪兽移动
};

#endif // ENEMY_H
