#include "new_window.h"
#include "ui_new_window.h"
#include "mainwindow.h"
#include <QPainter>
#include <QTimer>
/*new_window::new_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_window)
{
    ui->setupUi(this);
}*/

//插入怪物  路径点数组和小怪兽的编号
#define InsertEnemy(PathId,StartCoorId,EnemyId)     \
EnemyVec.push_back(new Enemy(pointarr[PathId],PathLength[PathId],stc[StartCoorId].x,stc[StartCoorId].y, EnemyId));

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
    victorylb->setFont(QFont("Calibri",30));
    victorylb->setText(QString("YOU WIN!"));
    victorylb->hide();

    loselb->setGeometry(370,180,300,100);
    loselb->setFont(QFont("Calibri",30));
    loselb->setText(QString("YOU LOSE!"));
    loselb->hide();

    QTimer* timer = new QTimer(this);
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

            //每条路径的结点个数
            int PathLength[] = {sizeof(Waypointarr)/sizeof(CoorStr*)};
            EnemyRoute(Waypointarr,stc,PathLength);
            break;
        }
        case 2:
        {
            CoorStr* Waypointarr[] = {new CoorStr(120,280), new CoorStr(760,280), new CoorStr(760,480),
                                      new CoorStr(200,480), new CoorStr(icecoor->x, icecoor->y)};
            CoorStr stc[] = {CoorStr(120,0)};
            int PathLength[] = {sizeof(Waypointarr)/sizeof(CoorStr*)};
            EnemyRoute(Waypointarr,stc,PathLength);
            break;
        }

        case 3:
        {
            CoorStr* Waypointarr1[] = {new CoorStr(480,360), new CoorStr(320,360),
                                       new CoorStr(320,0),new CoorStr(icecoor->x, icecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(480,360), new CoorStr(640,360),
                                       new CoorStr(640,0), new CoorStr(icecoor->x, icecoor->y)};
            CoorStr stc[] = {CoorStr(440,640)};
            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr2)/sizeof(CoorStr*)};
            EnemyRoute(Waypointarr1,Waypointarr2,stc,PathLength);
            break;
        }
        default:
            break;
        }
    });

    QTimer* timer2=new QTimer(this);
    timer2->start(150);

    connect(timer2,&QTimer::timeout,[=]()
    {
        //小怪兽移动
        for (auto i = EnemyVec.begin();i != EnemyVec.end();i++)
            if((*i)->Move()) //走到终点
            {
                delete *i;
                EnemyVec.erase(i);//移除
                life--;
                lifelb->setText(QString("生命：%1").arg(life));

                if (life <= 0)
                    loselb->show();
                    this->close();
                break;
            }
        update();   //不要漏掉
    });

}

//利用数组画出每关的不同地图
void new_window::DrawMap(QPainter & painter)
{
    //地图数组
    //640=16*40
    int Map1[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3, 1,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map2[16][26] =
    {
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map3[16][26] =
    {
        0, 0, 0, 0, 0, 2, 0, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    //每关的塔基数量递减
    int tempMap[16][26];    //用于拷贝不同关卡地图数组的临时数组

    switch (level)
    {
    case 1:
        memcpy(tempMap, Map1, sizeof(tempMap));//memorycopy
        break;
    case 2:
        memcpy(tempMap, Map2, sizeof(tempMap));
        break;
    case 3:
        memcpy(tempMap, Map3, sizeof(tempMap));
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


void new_window::EnemyRoute(CoorStr** Waypointarr,CoorStr* stc,int* PathLength)
{
    CoorStr** pointarr[] = {Waypointarr};

    if(counter>=1&&counter<=10)
    {
        InsertEnemy(0,0,1);
    }
    else if(counter>10&&counter<=20)
    {
        InsertEnemy(0,0,2);
    }
    else if (counter>20&& counter<=30)
    {
        InsertEnemy(0,0,2);
        InsertEnemy(0,0,3);
    }
    else if (counter>30&&counter<=40)
    {
        InsertEnemy(0,0,3);
        InsertEnemy(0,0,4);
    }
    if(counter>40&&counter<=50)
    {
        InsertEnemy(0,0,4);
        InsertEnemy(0,0,5);
    }

    if (counter>50&&EnemyVec.empty())
        victorylb->show();

    counter++;
    update();
}


void new_window::EnemyRoute(CoorStr** Waypointarr1, CoorStr** Waypointarr2, CoorStr* stc, int* PathLength)
{
    //两条路径
    CoorStr** pointarr[] = {Waypointarr1, Waypointarr2};

    if(counter>=1&&counter<=10)
    {
        InsertEnemy(0,0,1);
    }
    else if(counter>10&&counter<=20)
    {
        InsertEnemy(0,0,1);
        InsertEnemy(1,0,2);
    }
    else if (counter>20&&counter<=30)
    {
        InsertEnemy(0,0,3);
        InsertEnemy(1,0,3);
    }
    else if (counter>30&&counter<=40)
    {
        InsertEnemy(0,0,3);
        InsertEnemy(0,0,4);
        InsertEnemy(1,0,4);
    }
    if(counter>40&&counter<=50)
    {
        InsertEnemy(1,0,4);
        InsertEnemy(0,0,5);
        InsertEnemy(1,0,5);
    }

    if (counter>50&&EnemyVec.empty())
        victorylb->show();

    counter++;
    update();
}

//画出怪物
void new_window::DrawEnemy(QPainter& painter)
{
    for (auto i:EnemyVec)
        painter.drawPixmap(i->getX(),i->getY(),QPixmap(i->getImgPath()));
}

void new_window::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,1040,640,QPixmap(":/images/gamebg.png"));
    DrawMap(painter);
    DrawEnemy(painter);

}
new_window::~new_window()
{
    for (auto i=EnemyVec.begin();i!=EnemyVec.end();i++)
    {
        delete *i;
        *i = NULL;
    }
    delete ui;
}

