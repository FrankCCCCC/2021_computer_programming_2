#include "Block.h"

Block::Block()
{
    this->type = 2;
    this->Position.sets(0.0,0.0);
    this->Collider.Set_Position(Position);
    this->Collider.Set_Width(0.0);
    this->Collider.Set_Height(0.0);
}

Block::Block(float pos_x, float pos_y, float width, float height)
{
    this->type = 2;
    this->Position.sets(pos_x,pos_y);
    this->Collider.Set_Position(Position);
    this->Collider.Set_Width(width);
    this->Collider.Set_Height(height);
}

void Block::Draw()
{
    return;
}
