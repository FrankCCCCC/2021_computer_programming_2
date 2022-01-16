#ifndef HITBOX_H_NCLUDED
#define HITBOX_H_INCLUDED

#include "Vector2.h"
#include <math.h>

class Hitbox
{
    public:
        //////Constructor//////
        Hitbox();
        Hitbox(Vector2, float, float);
        Hitbox(float , float, float, float);
        //////Functions//////
        bool Istouching(Hitbox);
        float Get_OffsetX(){return offset_x;}
        float Get_OffsetY(){return offset_y;}
        void Set_Position(Vector2);
        void Set_Width(float);
        void Set_Height(float);

    protected:
        float offset_x;
        float offset_y;
        Vector2 Center;
};

#endif // HITBOX_H_NCLUDED

