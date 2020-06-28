#include "choice.h"

Subbutton* SelectionBox::GetSubbutton()
{
    return SubBut;
}

void SelectionBox::SetDisplay(const bool play)
{
    display=play;
}

void SelectionBox::CheckTower(int x, int y)
{
    display=true;

    //选择框的位置，左上角，95+95+80=270
    sx=x-95;
    sy=y-95;

    SubBut[0].subx=sx+105;
    SubBut[0].suby=sy+15;
    SubBut[0].SubImgPath=QString(":/images/common1.png");

    SubBut[1].subx=sx+15;
    SubBut[1].suby=sy+105;
    SubBut[1].SubImgPath=QString(":/images/common2.png");

    SubBut[2].subx=sx+200;
    SubBut[2].suby=sy+105;
    SubBut[2].SubImgPath=QString(":/images/firecannon.png");

    SubBut[3].subx=sx+105;
    SubBut[3].suby=sy+190;
    SubBut[3].SubImgPath=QString(":/images/lightcannon.png");
}

