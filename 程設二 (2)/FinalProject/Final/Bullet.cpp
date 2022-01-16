#include "Bullet.h"

Bullet::Bullet(int Team, int AttackPower)
{
    this->AttackPower = AttackPower;
    this->Team = Team;
}

void Bullet::SetVelocity(int V)
{
    this->Velocity = V;
}

void Bullet::SetTravelDistance(int Dis)
{
    this->TravelDistance = Dis;
}

void Bullet::Draw(float ScrollX, Vector2 Pos)
{
    this->Position.sets(Pos.get_x(), Pos.get_y());
    this->Collider.Set_Position(Position);
    this->Collider.Set_Width(32);
    this->Collider.Set_Height(32);
    al_draw_bitmap(Sprite,Position.get_x()-ScrollX, Position.get_y(),0);
}
