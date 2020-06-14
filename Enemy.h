#ifndef ENEMY_H
#define ENEMY_H

//#include <QObject>
#include <QPoint>
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

class Enemy// : public QObject
{
    //Q_OBJECT
public:
    Enemy(CoorStr **point,int arrlen,int x,int y,int id);
    bool Move();

    int getX() const;
    int getY() const;
    int getID() const;
    int getHP() const;
    void setHP(int);
    QString getImgPath() const;
private:
    QVector<CoorStr*> Waypoint;  //小怪兽路径点数组
    //monster
    int mx, my;
    int mid;
    int HP;
    int speed =10;//每次移动的长度
    QString ImgPath;
//signals:

};

#endif // ENEMY_H
