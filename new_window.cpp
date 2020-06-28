#include "new_window.h"
//#include "ui_new_window.h"
#include "mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <math.h>
#include "tower.h"
#include "choice.h"
#include <QMediaPlayer>

new_window::new_window(int level):level(level)
{
    //窗口大小固定
    this->setFixedSize(1040, 640);

    moneylb->setGeometry(20,530,200,40);
    moneylb->setFont(QFont("Calibri",20));
    moneylb->setText(QString("金钱：%1").arg(money));

    lifelb->setGeometry(20,590,200,40);
    lifelb->setFont(QFont("Calibri",20));
    lifelb->setText(QString("生命值：%1").arg(life));

    victorylb->setGeometry(370,180,300,100);
    victorylb->setFont(QFont("Calibri",40));
    victorylb->setStyleSheet("color:white");
    victorylb->setText(QString("YOU WIN!"));
    victorylb->hide();

    loselb->setGeometry(370,180,300,100);
    loselb->setFont(QFont("Calibri",40));
    loselb->setStyleSheet("color:white");
    loselb->setText(QString("YOU LOSE!"));
    loselb->hide();

    timer->start(2000);
    connect(timer,&QTimer::timeout,[=]()
    {
        switch (level) {
        case 1:
        {
            //设置路径点:拐点和icecoor
            CoorStr* Waypointarr[] = {new CoorStr(160,400), new CoorStr(160,160), new CoorStr(480,160),
                                      new CoorStr(480,400), new CoorStr(800,400), new CoorStr(800,160),
                                      new CoorStr(icecoor->x, icecoor->y)};

            CoorStr stc[] = {CoorStr(0,400)};
            int pointnum[] = {7};
            EnemyRoute(Waypointarr,stc,pointnum);
            break;
        }
        case 2:
        {
            CoorStr* Waypointarr1[] = {new CoorStr(400,320), new CoorStr(240,320),
                                       new CoorStr(240,0),new CoorStr(icecoor->x, icecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(560,320), new CoorStr(720,320),
                                       new CoorStr(720,0), new CoorStr(icecoor->x, icecoor->y)};
            CoorStr stc[] = {CoorStr(400,640),CoorStr(560,640)};
            int pointnum[] = {4,4};
            EnemyRoute(Waypointarr1,Waypointarr2,stc,pointnum);
            break;
        }
        default:
            break;
        }
    });

    timer2->start(100);
    connect(timer2,&QTimer::timeout,[=]()
    {
        //寻找目标怪物
        for (auto towi:TowerVec)
            chooseEnemy(towi);

        //子弹移动
        for (auto towi:TowerVec)
            towi->BulletMove();

        update();
    });

    timer3->start(100);
    connect(timer3,&QTimer::timeout,[=]()
    {
        //小怪兽移动
        for (auto i=EnemyVec.begin();i!=EnemyVec.end();i++)
            if((*i)->Move())
            {//终点
                delete *i;
                EnemyVec.erase(i);

                if((*i)->mid==3)
                    life-=2;
                else
                    life--;

                QSound *sound=new QSound(":/sounds/beattacked.wav");
                sound->setLoops(1);
                sound->play();
                lifelb->setText(QString("生命：%1").arg(life));

                if (life <= 0)
                {
                    loselb->show();
                    QSound *sound=new QSound(":/sounds/losing2.wav");
                    sound->setLoops(1);
                    sound->play();
                    timer->stop();
                    timer2->stop();
                    timer3->stop();
                }

                break;
            }

        //子弹攻击怪物
        for (auto towi:TowerVec)
            attackEnemy(towi);

        update();
    });

}


bool new_window::buyingtower(int money)
{
    if(this->money-money<0)//钱不够
        return true;
    else
    {
        this->money-=money;
        moneylb->setText(QString("金钱：%1").arg(this->money));
        return false;
    }
}

//利用数组画出每关的不同地图
void new_window::DrawMap(QPainter & painter)
{
    //地图数组
    //640=16*40
    //easy
    int Map1[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3, 1,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    //hard
    int Map2[16][26] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };


    int tempMap[16][26];
    switch (level)
    {
    case 1:
        memcpy(tempMap, Map1, sizeof(tempMap));//memorycopy
        break;
    case 2:
        memcpy(tempMap, Map2, sizeof(tempMap));
        break;
    default:
        break;
    }

    //x->j;y->i
    for (int i=0;i<16;i++)
    {
        for (int j=0;j<26;j++)
        {
            switch (tempMap[i][j])
            {
            case 1:    //路面
                painter.drawPixmap(j*40,i*40,40,40,QPixmap(":/images/ground.png"));
                break;
            case 2:    //塔基
                painter.drawPixmap(j*40,i*40,80,80,QPixmap(":/images/towerbase.png"));
                 TowerBaseVec.push_back(new TowerBase(j*40, i*40,80,80));
                break;
            case 3:
                painter.drawPixmap(j*40,i*40,40,40,QPixmap(":/images/ground.png"));
                //获取icecream的坐标
                icecoor->x=j*40;
                icecoor->y=i*40;
                break;
            }
        }
    }
    //画出icecream
    painter.drawPixmap(icecoor->x,icecoor->y,80,80,QPixmap(":/images/icecream.png"));
}

void new_window::EnemyRoute(CoorStr** Waypointarray,CoorStr* stc,int* pointnum)
{
    CoorStr** pointarr[] = {Waypointarray};
    if(counter>=1&&counter<=10)
    {
        InsertEnemy(0,0,1);
    }
    else if(counter>10&&counter<=20)
    {
        InsertEnemy(0,0,2);
    }
    else if(counter>20&& counter<=30)
    {
        InsertEnemy(0,0,3);
    }
    else if(counter>30&&counter<=40)
    {
        InsertEnemy(0,0,4);
    }
    else if(counter>40&&counter<=50)
    {
        InsertEnemy(0,0,5);
    }
    else if(counter>50&&EnemyVec.empty())
    {
        victorylb->show();
        QSound *sound=new QSound(":/sounds/winning.wav");
        sound->play();
        sound->setLoops(1);
        timer->stop();
        timer2->stop();
        timer3->stop();
    }
    counter++;
    update();
}


void new_window::EnemyRoute(CoorStr** Waypointarray1,CoorStr** Waypointarray2,CoorStr* stc,int* pointnum)
{
    //两条路径
    CoorStr** pointarr[] = {Waypointarray1, Waypointarray2};
    if(counter>=1&&counter<=10)
    {
        InsertEnemy(0,0,1);
    }
    else if(counter>10&&counter<=20)
    {
        InsertEnemy(0,0,1);
        InsertEnemy(1,1,2);
    }
    else if(counter>20&&counter<=30)
    {
        InsertEnemy(0,0,3);
        InsertEnemy(1,1,3);
    }
    else if(counter>30&&counter<=40)
    {
        InsertEnemy(0,0,4);
        InsertEnemy(1,1,4);
    }
    else if(counter>40&&counter<=50)
    {
        InsertEnemy(0,0,5);
        InsertEnemy(1,1,4);
    }
    else if(counter>50&&EnemyVec.empty())
    {
        victorylb->show();
        QSound *sound=new QSound(":/sounds/winning.wav");
        sound->play();
        sound->setLoops(1);
        timer->stop();
        timer2->stop();
        timer3->stop();
    }
    counter++;
    update();
}

void new_window::chooseEnemy(tower* ti)
{
    if (ti->GetTarget()==NULL)
    {
        for(int i=0;i<=EnemyVec.size()-1;i++)
        {
            if (PointsDistance(ti->centerx,ti->centery,EnemyVec.at(i)->mx+EnemyVec.at(i)->mwidth/2,
                EnemyVec.at(i)->my+EnemyVec.at(i)->mheight/2)<=ti->Range)
            {
                ti->SetTarget(EnemyVec.at(i));
                break;
            }
        }
    }
    else
    {
        if (PointsDistance(ti->centerx,ti->centery,ti->GetTarget()->mx+ti->GetTarget()->mwidth/2,
            ti->GetTarget()->my+ti->GetTarget()->mheight/2)<= ti->Range)
        {
            //计算旋转角度
            ti->SetRotateAngle(atan2(ti->GetTarget()->my+ti->GetTarget()->mheight/2-ti->centerx,
                    ti->GetTarget()->mx+ti->GetTarget()->mwidth/2-ti->centery)*180/3.1415926);//转换成角度
             ti->ShootBullet();
        }

        else if (PointsDistance(ti->centerx,ti->centery,ti->GetTarget()->mx+ti->GetTarget()->mwidth/2,
                ti->GetTarget()->my+ti->GetTarget()->mheight/2)>ti->Range)
            ti->SetTarget(NULL);     //超出范围
      }

}

void new_window::attackEnemy(tower *ti)
{
    auto tempvec=ti->GetBulletVec();   //临时子弹
    for (auto buli=tempvec.begin();buli!=tempvec.end();buli++)
        for (auto moni=EnemyVec.begin();moni!=EnemyVec.end();moni++)//怪物
            if ((*buli)->coor.x+ti->bullwidth>=(*moni)->mx && (*buli)->coor.x<=(*moni)->mx+(*moni)->mwidth &&
               (*buli)->coor.y+ti->bullheight>=(*moni)->my && (*buli)->coor.y<=(*moni)->my+(*moni)->mheight)
            {   //击中怪物
                tempvec.erase(buli);
                (*moni)->setHP((*moni)->HP-ti->attack);

                if ((*moni)->HP <= 0)
                {
                    for (auto i:TowerVec)
                        if (i->GetTarget()==*moni)
                            i->SetTarget(NULL);

                    EnemyVec.erase(moni);
                    money+=bonus;
                    moneylb->setText(QString("金钱：%1").arg(money));
                }
                goto L1;
            }

    L1:;
    update();   //不要漏掉
}

void new_window::DrawEnemy(QPainter& painter)
{
    for (auto i:EnemyVec)
        painter.drawPixmap(i->mx,i->my,QPixmap(i->ImgPath));
}

void new_window::DrawChoiceBoxes(QPainter& painter)
{
    if (!SelBox->display)
        return;

    painter.drawPixmap(SelBox->sx,SelBox->sy,SelBox->swidth,SelBox->sheight,
        QPixmap(SelBox->SelBoxImgPath));

    Subbutton *subbut=SelBox->GetSubbutton();
    for (int i=0;i<4;i++)
        painter.drawPixmap(subbut[i].subx,subbut[i].suby,subbut[i].subwidth,subbut[i].subheight,
            QPixmap(subbut[i].SubImgPath));
    //选中时
    painter.setPen(QPen(Qt::yellow,5,Qt::SolidLine));
    painter.drawRect(QRect(SelBox->sx+95,SelBox->sy+95,80,80));
}

void new_window::DrawTower(QPainter& painter)
{
    for (auto i:TowerVec)
    {
        for (auto buli:i->GetBulletVec())
            painter.drawPixmap(buli->coor.x,buli->coor.y,i->bullwidth,i->bullheight,
                               QPixmap(i->BullPath));

        painter.translate(i->centerx,i->centery);//旋转中心
        painter.rotate(i->RotateAngle);
        painter.translate(-(i->centerx),-(i->centery));
        painter.drawPixmap(i->tx,i->ty,i->twidth,i->theight,QPixmap(i->TowImgPath));
        painter.resetTransform();

        //显示攻击范围
        painter.setPen(QPen(Qt::red));
        painter.drawEllipse(QPoint(i->centerx,i->centery),i->Range,i->Range);
    }
}

void new_window::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,1040,640,QPixmap(":/images/gamebg.png"));
    DrawMap(painter);
    DrawEnemy(painter);
    DrawChoiceBoxes(painter);
    DrawTower(painter);
}

void new_window::mousePressEvent(QMouseEvent *mp)
{
    if (mp->button()!= Qt::LeftButton)
        return;

    Subbutton *subbut=SelBox->GetSubbutton();
    for (int i=0;i<4;i++)
        if (MouseClickRegion(subbut[i].subx,subbut[i].subwidth,subbut[i].suby,subbut[i].subheight)
                && SelBox->display)
        {
            SelBox->SetDisplay(false);

            switch (i)
            {
            case 0:
                if (buyingtower(100))
                    return;
                TowerVec.push_back(new CommonTower1(SelBox->sx+110,SelBox->sy+112,SelBox->sx+135,SelBox->sy+135,80,50));
                break;
            case 1:
                if (buyingtower(150))
                    return;
                TowerVec.push_back(new CommonTower2(SelBox->sx+110,SelBox->sy+112,SelBox->sx+135,SelBox->sy+135,80,50));
                break;
            case 2:
                if (buyingtower(200))
                    return;
                TowerVec.push_back(new FireTower(SelBox->sx+110,SelBox->sy+112,SelBox->sx+135,SelBox->sy+135,80,50));
                break;
            case 3:
                if (buyingtower(250))
                    return;
                TowerVec.push_back(new LightTower(SelBox->sx+110,SelBox->sy+104,SelBox->sx+135,SelBox->sy+135,80,70));
                break;
            default:
                break;
            }

            update();
            return;
        }

    for (auto towerbase : TowerBaseVec)
        if (MouseClickRegion(towerbase->bx,towerbase->bwidth,towerbase->by,towerbase->bheight))
        {
            SelBox->CheckTower(towerbase->bx, towerbase->by);
            update();
            return;
        }

    SelBox->SetDisplay(false);
    update();

}

new_window::~new_window()
{
    for(auto i=TowerBaseVec.begin();i!=TowerBaseVec.end();i++)
    {
        delete *i;
        *i=NULL;
    }

    for(auto i=TowerVec.begin();i!=TowerVec.end();i++)
    {
        delete *i;
        *i=NULL;
    }

    for(auto i=EnemyVec.begin();i!=EnemyVec.end();i++)
    {
        delete *i;
        *i = NULL;
    }

    delete SelBox;
    SelBox = NULL;

    delete icecoor;
    //delete ui;
}

