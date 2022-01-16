#include "Hitbox.h"

Hitbox::Hitbox()
{
    this->offset_x = 0.0;
    this->offset_y = 0.0;
    this->Center.sets(0.0,0.0);
}

Hitbox::Hitbox(Vector2 pos, float width, float height)
{
    this->offset_x = width/2;
    this->offset_y = height/2;
    this->Center.sets(pos.get_x()+offset_x, pos.get_y()+offset_y);
}

Hitbox::Hitbox(float pos_x, float pos_y,float width, float height)
{
    this->offset_x = width/2;
    this->offset_y = height/2;
    this->Center.sets(pos_x+offset_x, pos_y+offset_y);
}

bool Hitbox::Istouching(Hitbox Target)
{
    if(fabs(this->Center.get_x() - Target.Center.get_x())<(this->offset_x+Target.Get_OffsetX()) && fabs(this->Center.get_y() - Target.Center.get_y())<(this->offset_y+Target.Get_OffsetY()))
        return true;
    else
        return false;
}

void Hitbox::Set_Position(Vector2 Pos)
{
    Center.sets(Pos.get_x()+offset_x, Pos.get_y()+offset_y);
}

void Hitbox::Set_Width(float width)
{
    offset_x = width/2;
}

void Hitbox::Set_Height(float height)
{
    offset_y = height/2;
}
