#ifndef WORK_H_INCLUDED
#define WORK_H_INCLUDED

#include "Tower.h"

class Work : public Tower
{
public:
    Work(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = WORK;

        circle->r = 500;
        attack_frequency = 30;
        attack_velocity = 10;
        attack_harm_point = 1;
        img = al_load_bitmap("./Tower/Work.png");
        attack_img = al_load_bitmap("./Tower/Work_Beam.png");
    }

    int getWidth() override { return TowerWidth[WORK]; }
    int getHeight() override { return TowerHeight[WORK]; }
};

#endif // ARCHER_H_INCLUDED
