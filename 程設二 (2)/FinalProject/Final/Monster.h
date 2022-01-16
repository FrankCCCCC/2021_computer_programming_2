#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "GameObject.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Monster: public GameObject
{
    public:
        Monster(float, float);
        void Draw(int);
        float GetVelocity(){return Velocity;}
        int GetAttackPower(){return AttackPower;}
        bool Isalive(){return (Health>0);}
        void LoseHealth(int damage){Health = Health - damage;}
    private:
        float Velocity = 5;
        int AttackPower = 10;
        int Health = 30;

        ALLEGRO_BITMAP* Sprite = al_load_bitmap("./Assets/monster_0.png");
};

#endif // MONSTER_H_INCLUDED
