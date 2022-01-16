#include "Vector2.h"

Vector2::Vector2()
{
    sets(0.0,0.0);
}

Vector2::Vector2(float X, float Y)
{
    sets(X,Y);
}

void Vector2::sets(float X, float Y)
{
    this->x = X;
    this->y = Y;
}

float Vector2::get_x()
{
    return x;
}

float Vector2::get_y()
{
    return y;
}

Vector2 Vector2::operator+(const Vector2 &Target)
{
    Vector2 temp;

    temp.x = this->x + Target.x;
    temp.y = this->y + Target.y;

    return temp;
}
