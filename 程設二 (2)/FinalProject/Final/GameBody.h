#ifndef GAMEBODY_H_INCLUDED
#define GAMEBODY_H_INCLUDED

//////Include all allegro5 header//////
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>

#include "Global.h"
#include "Level.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"

class GameBody
{
    public:
        //////Constructor//////
        GameBody();
        //////GameBackstage//////
        void game_init();
        void game_begin();
        void game_running(int Sta);
        void game_destroy();
        //////GameScenes//////
        void game_scene(int scene);
        void transition(int scene);
        void game_menu();
        void draw_menu(float scrollx, int Select, int scene);
        void game_exit();
        //////GameFunctions//////
        int event_processor();
        int update(float );
        void state_controller(int state);

    private:
        //////Bitmap//////
        ALLEGRO_BITMAP* menu_back = NULL;
        ALLEGRO_BITMAP* menu_front = NULL;
        //////Timer//////
        ALLEGRO_TIMER* frametimer = NULL;
        //////Display//////
        ALLEGRO_DISPLAY* display = NULL;
        //////Event & EventQueue//////
        ALLEGRO_EVENT_QUEUE* event_queue = NULL;
        ALLEGRO_EVENT event;
        //////Sample & SampleInstance//////
        ALLEGRO_SAMPLE *sample = NULL;
        ALLEGRO_SAMPLE_INSTANCE *BGM_stage = NULL;
        ALLEGRO_SAMPLE_INSTANCE *BGM_menu = NULL;
        ALLEGRO_SAMPLE_INSTANCE *Trans = NULL;
        ALLEGRO_SAMPLE_INSTANCE *Button = NULL;
        float Volume_BGM = 1;
        float Volume_SFX = 1;
        //////Font//////
        ALLEGRO_FONT *font = NULL;
        ALLEGRO_FONT *Medium_font = NULL;
        ALLEGRO_FONT *Large_font = NULL;
        ALLEGRO_FONT *Title_font = NULL;
        //////GameSubject//////
        Level* game_level = NULL;
        Player* game_player = NULL;
        vector<Bullet> BulletSet;
        vector<Monster> MonsterSet;

};

#endif // GAMEBODY_H_INCLUDED
