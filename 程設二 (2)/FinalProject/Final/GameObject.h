#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
//////header//////
#include "Global.h"
#include "Vector2.h"
#include "Hitbox.h"

class GameObject
{
    public:
        GameObject();
        GameObject(int, Vector2, float, float);
        void Moveto(float,float);
        void Moveto(Vector2);
        Vector2 GetPosition();
        Hitbox GetHitBox();
        bool IsTouching(Hitbox);

    protected:
        int type;
        Vector2 Position;
        Hitbox Collider;
};

#endif // GAMEOBJECT_H_INCLUDED
