#ifndef CHOICE_H
#define CHOICE_H

#include <QString>

class Subbutton
{
public:
    int subx;
    int suby;
    int subwidth=55;
    int subheight=55;
    QString SubImgPath;
};

class SelectionBox
{
public:
    int sx=0;
    int sy=0;
    const int swidth;
    const int sheight;
    QString SelBoxImgPath;
    bool display=false;
    Subbutton SubBut[4];

    SelectionBox(QString Path,int width=270,int height=270):
         swidth(width),sheight(height),SelBoxImgPath(Path) {}
    Subbutton* GetSubbutton();
    void SetDisplay(const bool play);
    void CheckTower(int x,int y); //选择防御塔
};

#endif // CHOICE_H
