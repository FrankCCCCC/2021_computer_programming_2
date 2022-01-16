#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "Block.h"
#include "Player.h"
#include "Global.h"

using namespace std;

class Level
{
    public:
        Level();
        bool LoadLevel(int);
        void Draw(float);
        int GetLevel_num(){return level_num;}
        bool IsTouchingGround(GameObject*);
        ALLEGRO_SAMPLE_INSTANCE* GetBGM();
        Vector2 GetStartPoint();


    private:
        int level_width;
        int level_height;
        float StartX, StartY;
        ALLEGRO_BITMAP* Map;
        ALLEGRO_SAMPLE* sample;
        ALLEGRO_SAMPLE_INSTANCE* BGM;
        vector<Block> BlockSets;
        int level_num;
};


#endif // LEVEL_H_INCLUDED
