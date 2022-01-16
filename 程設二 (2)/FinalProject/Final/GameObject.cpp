#include "GameObject.h"

GameObject::GameObject()
{
    this->type = 0;
    this->Position.sets(0.0,0.0);
    this->Collider.Set_Position(Position);
    this->Collider.Set_Width(0.0);
    this->Collider.Set_Height(0.0);
}

GameObject::GameObject(int t, Vector2 pos, float width, float height)
{
    this->type = t;
    this->Position = pos;
    this->Collider.Set_Position(Position);
    this->Collider.Set_Width(width);
    this->Collider.Set_Height(height);
}

void GameObject::Moveto(float X, float Y)
{
    this->Position.sets(X,Y);
    this->Collider.Set_Position(Position);
}

void GameObject::Moveto(Vector2 Pos)
{
    this->Position = Pos;
    this->Collider.Set_Position(Pos);
}

Vector2 GameObject::GetPosition()
{
    return Position;
}

Hitbox GameObject::GetHitBox()
{
    return Collider;
}

bool GameObject::IsTouching(Hitbox Target)
{
    return(Collider.Istouching(Target));
}
