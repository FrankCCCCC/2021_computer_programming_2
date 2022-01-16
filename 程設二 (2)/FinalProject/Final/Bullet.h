#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "GameObject.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Bullet: public GameObject
{
    public:
        Bullet(int, int);
        int GetTeam(){return Team;}
        int GetVelocity(){return Velocity;}
        void SetVelocity(int);
        int GetAttackPower(){return AttackPower;}
        void SetTravelDistance(int);
        int GetTravelDistance(){return TravelDistance;}
        void Draw(float , Vector2);

    private:
        int Team;
        int Velocity = 10;
        int TravelDistance = 0;
        int AttackPower;
        ALLEGRO_BITMAP* Sprite = al_load_bitmap("./Assets/bullet.png");
};



#endif // BULLET_H_INCLUDED
