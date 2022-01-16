#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameObject.h"


class Player : public GameObject
{
    public:
        Player();
        float GetVelocity(){return Velocity;}
        int GetAttackPower(){return AttackPower;}
        void Draw(int, int, float);
    private:
        int Laststate = 0;
        int state = 0;
        int Direction = 0;
        float Velocity = 5;
        int AttackPower = 10;
        int Health = 100;

        int Frame_count = 0;
        int Sprite_frame = 0;
        ALLEGRO_BITMAP* Sprite = al_load_bitmap("./Assets/Player/0_0.png");
};


#endif // PLAYER_H_INCLUDED
