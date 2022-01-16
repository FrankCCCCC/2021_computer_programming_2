#include "Monster.h"

Monster::Monster(float X, float Y)
{
    this->Position.sets(X,Y);
    this->Collider.Set_Position(Position);
    this->Collider.Set_Width(25);
    this->Collider.Set_Height(45);
}

void Monster::Draw(int Scrollx)
{
    al_draw_bitmap(Sprite, Position.get_x() - Scrollx, Position.get_y(), 0);
}
