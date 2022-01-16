#include "GameBody.h"


GameBody::GameBody()
{
    if(!al_init())
        state_controller(-1);

    display = al_create_display(Window_width, Window_hegith);
    event_queue = al_create_event_queue();

    frametimer = al_create_timer(1.0 / FPS);

    if(display == NULL || event_queue == NULL || frametimer == NULL)
        state_controller(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    printf("initialize success.\n");

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    printf("install success.\n");

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(frametimer));

    printf("register success.\n");
    //cout << "Constructing Success!"<<endl;
    game_init();
}

void GameBody::game_init()
{
    menu_back = al_load_bitmap("./Assets/Menu_back.jpg");
    menu_front = al_load_bitmap("./Assets/Menu_front.png");
    game_level = new Level();
    game_player = new Player();

    al_reserve_samples(4);
    sample = al_load_sample("./Assets/Menu_BGM.ogg");
    BGM_menu = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(BGM_menu,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(BGM_menu,al_get_default_mixer());
    sample = al_load_sample("./Assets/button.ogg");
    Button = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(Button,ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(Button,al_get_default_mixer());
    sample = al_load_sample("./Assets/trans.ogg");
    Trans = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(Trans,ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(Trans,al_get_default_mixer());


    al_start_timer(frametimer);

    font = al_load_ttf_font("./Assets/setofont.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("./Assets/setofont.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("./Assets/setofont.ttf",36,0); //load large font
    Title_font = al_load_ttf_font("./Assets/setofont.ttf",72,0); //load Title font
}

void GameBody::game_running(int Sta)
{
    bool next = false;
    int stage = Sta;
    transition(stage);
    BGM_stage = game_level->GetBGM();
    al_set_sample_instance_gain(BGM_stage,Volume_BGM);
    al_attach_sample_instance_to_mixer(BGM_stage,al_get_default_mixer());
    al_play_sample_instance(BGM_stage);
    game_player->Moveto(game_level->GetStartPoint());

    float Map_x = 0.0;
    Vector2 Position = game_player->GetPosition();
    Vector2 Vel;
    int state = 0;
    int face = 0;
    int dir = 0;
    int frame_count = 0;
    int Gravity = 8;
    bool Isrunning = false;
    bool Isgrounded = false;
    bool IsJumping = false;
    MonsterSet.clear();
    if (Sta == 0)
    {
        MonsterSet.push_back(Monster(600,480));
        MonsterSet.push_back(Monster(1200,480));
        MonsterSet.push_back(Monster(1400,480));
        MonsterSet.push_back(Monster(1600,480));
    }
    else if(Sta == 1)
    {
        MonsterSet.push_back(Monster(1560, 260));
    }
    while(!next)
    {
        Isgrounded = game_level->IsTouchingGround(game_player);
        if(game_player->GetPosition().get_y() > 600)
        {
            Position.sets(game_level->GetStartPoint().get_x(), game_level->GetStartPoint().get_y());
            Map_x = 0;
        }
        if(game_player->GetPosition().get_x() > 4700)
        {
            next = true;
            game_running(Sta+1);
        }
        al_wait_for_event(event_queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                state_controller(0);
                break;
            case ALLEGRO_EVENT_TIMER:
                Map_x = Map_x + 5*face;
                if(Map_x <= 0) Map_x = 0;
                if(Map_x >= 4000) Map_x = 4000;
                game_level->Draw(Map_x);

                if(!Isgrounded && !IsJumping)
                {
                    state = Fall;
                    Vel.sets(game_player->GetVelocity()*face, Gravity);
                }
                else if(IsJumping)
                {
                    if(frame_count <20)
                    {
                        frame_count++;
                        state = Jump_Up;
                        Vel.sets(game_player->GetVelocity()*face, (frame_count - 28)*0.7);
                    }
                    else if(frame_count >= 20 && frame_count <= 35)
                    {
                        frame_count++;
                        state = Jump_MidAir;
                        Vel.sets(game_player->GetVelocity()*face, (frame_count - 28)*0.7);
                    }
                    else
                    {
                        state = Fall;
                        Vel.sets(game_player->GetVelocity()*face, Gravity);
                        if(Isgrounded)
                        {
                            IsJumping = false;
                            Vel.sets(game_player->GetVelocity()*face, Gravity);
                        }
                    }
                }
                else if (Isgrounded && !Isrunning)
                {
                    state = Idle;
                    Vel.sets(game_player->GetVelocity()*face, 0);
                }
                else if (Isgrounded && Isrunning)
                {
                    state = Run;
                    Vel.sets(game_player->GetVelocity()*face, 0);
                }
                Position.sets(Position.get_x()+Vel.get_x(),Position.get_y()+Vel.get_y());
                game_player->Moveto(Position);
                game_player->Draw(state,dir,Map_x);
                update(Map_x);
                frame_count++;
                al_flip_display();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                {
                    Isrunning = true;
                    state = Run;
                    face = 1;
                    dir = 0;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                {
                    Isrunning = true;
                    state = Run;
                    face = -1;
                    dir = 1;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    next = true;
                    al_stop_sample_instance(BGM_stage);
                    game_menu();
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_Z)
                {
                    if(!IsJumping)
                    {
                        IsJumping = true;
                        state = Jump_Up;
                        frame_count = 0;
                    }
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_X)
                {
                    Bullet Bul(0, game_player->GetAttackPower());
                    Vector2 pos = game_player->GetPosition();
                    if(dir == 0) Bul.SetVelocity(Bul.GetVelocity()*1);
                    else Bul.SetVelocity(Bul.GetVelocity()*-1);
                    Bul.Draw(Map_x,pos);
                    BulletSet.push_back(Bul);
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                {
                    if(event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                    {
                        Isrunning = false;
                        face = 0;
                        state = Idle;
                    }
                }
                break;
        }
    }
}

void GameBody::transition(int stage)
{
    al_clear_to_color(White);
    if(al_get_sample_instance_playing(BGM_menu)) al_stop_sample_instance(BGM_menu);
    else if(al_get_sample_instance_playing(BGM_stage)) al_stop_sample_instance(BGM_stage);
    al_play_sample_instance(Trans);
    float time = 2.0;
    float speed = (255/60)/time;
    float percent = 0.0;
    while(percent <= 255.0)
    {
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(White);
            al_draw_filled_rectangle(0,0,Window_width,Window_hegith,al_map_rgba(0, 0, 0, percent));
            percent += speed;
            al_flip_display();
        }
    }
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER)
    {
        al_clear_to_color(Black);
        al_draw_text(Title_font, White, 400, 250, ALLEGRO_ALIGN_CENTER,"Loading...");
        al_draw_text(Title_font, Orange, 397, 250, ALLEGRO_ALIGN_CENTER,"Loading...");
        al_flip_display();
    }

    game_level->LoadLevel(stage);

    while(percent >= 0.0)
    {
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(White);
            al_draw_filled_rectangle(0,0,Window_width,Window_hegith,al_map_rgba(0, 0, 0, percent));
            percent -= speed*0.7;
            al_flip_display();
        }
    }
}

void GameBody::game_menu()
{
    bool Start = false;
    draw_menu(0.0, 1,0);
    al_play_sample_instance(BGM_menu);
    float ScrollX = 0.0;
    int sel = 1;
    int scene = 0;
    while(!Start)
    {
        al_wait_for_event(event_queue, &event);
        draw_menu(ScrollX,sel,scene);
        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                state_controller(0);
                break;
            case ALLEGRO_EVENT_TIMER:
                ScrollX += 0.5;
                if(ScrollX >= 799.5)
                    ScrollX = 0;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        sel -= 1;
                        if(!al_get_sample_instance_playing(Button))
                            al_play_sample_instance(Button);
                        if(sel <= 1) sel = 1;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        sel += 1;
                        if(!al_get_sample_instance_playing(Button))
                            al_play_sample_instance(Button);
                        if(sel >= 4 && scene == 0) sel = 4;
                        else if(sel>=3 && scene == 2) sel = 3;
                        else if(sel && scene == 3) sel = 1;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        if(scene == 2)
                        {
                            if(sel == 1)
                                if(Volume_BGM < 1.0)Volume_BGM +=0.1;
                            if(sel == 2)
                                if(Volume_SFX < 1.0)Volume_SFX +=0.1;
                            al_set_sample_instance_gain(BGM_menu,Volume_BGM);
                            al_set_sample_instance_gain(Button,Volume_SFX);
                            al_set_sample_instance_gain(Trans, Volume_SFX);
                        }
                        break;
                    case ALLEGRO_KEY_LEFT:
                        if(scene == 2)
                        {
                            if(sel == 1)
                                Volume_BGM -=0.1;
                            if(sel == 2)
                                Volume_SFX -=0.1;
                            if(Volume_BGM <= 0.0) Volume_BGM = 0.0;
                            if(Volume_SFX <= 0.0) Volume_SFX = 0.0;
                            al_set_sample_instance_gain(BGM_menu,Volume_BGM);
                            al_set_sample_instance_gain(Button,Volume_SFX);
                            al_set_sample_instance_gain(Trans, Volume_SFX);
                        }
                        break;
                    case ALLEGRO_KEY_Z:
                        if(scene == 0)
                            scene = sel;
                        else if(scene == 0 && sel!= 1)
                        {
                            Start = true;
                            draw_menu(0,0,1);
                        }
                        else if(scene == 2 && sel == 3)
                            scene = 0;
                        else if(scene == 3)
                            scene = 0;
                        break;
                    default:
                        continue;
                }
                break;
            default:
                continue;
        }
    }
    return;
}

void GameBody::draw_menu(float scrollx, int Select, int scene)
{
    al_clear_to_color(White);
    al_draw_bitmap(menu_back, -scrollx, 0, 0);
    al_draw_bitmap(menu_front, 0, 0, 0);
    al_draw_text(Title_font,White,47,50,ALLEGRO_ALIGN_LEFT,"Unity!");
    al_draw_text(Title_font,Orange,50,50,ALLEGRO_ALIGN_LEFT,"Unity!");
    switch(scene)
    {
        case 0:
            switch(Select)
            {
                case 1:
                    al_draw_text(Large_font,Redd,750,350,ALLEGRO_ALIGN_RIGHT,"->Start game");
                    al_draw_text(Large_font,Orange,750,410,ALLEGRO_ALIGN_RIGHT,"Options");
                    al_draw_text(Large_font,Orange,750,470,ALLEGRO_ALIGN_RIGHT,"Credit");
                    al_draw_text(Large_font,Orange,750,530,ALLEGRO_ALIGN_RIGHT,"Exit");
                    break;
                case 2:
                    al_draw_text(Large_font,Orange,750,350,ALLEGRO_ALIGN_RIGHT,"Start game");
                    al_draw_text(Large_font,Redd,750,410,ALLEGRO_ALIGN_RIGHT,"->Options");
                    al_draw_text(Large_font,Orange,750,470,ALLEGRO_ALIGN_RIGHT,"Credit");
                    al_draw_text(Large_font,Orange,750,530,ALLEGRO_ALIGN_RIGHT,"Exit");
                    break;
                case 3:
                    al_draw_text(Large_font,Orange,750,350,ALLEGRO_ALIGN_RIGHT,"Start game");
                    al_draw_text(Large_font,Orange,750,410,ALLEGRO_ALIGN_RIGHT,"Options");
                    al_draw_text(Large_font,Redd,750,470,ALLEGRO_ALIGN_RIGHT,"->Credit");
                    al_draw_text(Large_font,Orange,750,530,ALLEGRO_ALIGN_RIGHT,"Exit");
                    break;
                case 4:
                    al_draw_text(Large_font,Orange,750,350,ALLEGRO_ALIGN_RIGHT,"Start game");
                    al_draw_text(Large_font,Orange,750,410,ALLEGRO_ALIGN_RIGHT,"Options");
                    al_draw_text(Large_font,Orange,750,470,ALLEGRO_ALIGN_RIGHT,"Credit");
                    al_draw_text(Large_font,Redd,750,530,ALLEGRO_ALIGN_RIGHT,"->Exit");
                    break;
                default:
                    al_draw_text(Large_font,Orange,750,350,ALLEGRO_ALIGN_RIGHT,"Start game");
                    al_draw_text(Large_font,Orange,750,410,ALLEGRO_ALIGN_RIGHT,"Options");
                    al_draw_text(Large_font,Orange,750,470,ALLEGRO_ALIGN_RIGHT,"Credit");
                    al_draw_text(Large_font,Orange,750,530,ALLEGRO_ALIGN_RIGHT,"Exit");
        }
            break;
        case 1:
            game_running(0);
            //game_menu();
            break;
        case 2:
            switch(Select)
            {
                case 1:
                    al_draw_textf(Large_font,Redd,750,350,ALLEGRO_ALIGN_RIGHT,"->BGM %.1f", Volume_BGM*10);
                    al_draw_textf(Large_font,Orange,750,410,ALLEGRO_ALIGN_RIGHT,"SFX %.1f", Volume_SFX*10);
                    al_draw_textf(Large_font,Orange,750,530,ALLEGRO_ALIGN_RIGHT,"Return");
                    break;
                case 2:
                    al_draw_textf(Large_font,Orange,750,350,ALLEGRO_ALIGN_RIGHT,"BGM %.1f", Volume_BGM*10);
                    al_draw_textf(Large_font,Redd,750,410,ALLEGRO_ALIGN_RIGHT,"->SFX %.1f", Volume_SFX*10);
                    al_draw_textf(Large_font,Orange,750,530,ALLEGRO_ALIGN_RIGHT,"Return");
                    break;
                case 3:
                    al_draw_textf(Large_font,Orange,750,350,ALLEGRO_ALIGN_RIGHT,"BGM %.1f", Volume_BGM*10);
                    al_draw_textf(Large_font,Orange,750,410,ALLEGRO_ALIGN_RIGHT,"SFX %.1f", Volume_SFX*10);
                    al_draw_textf(Large_font,Redd,750,530,ALLEGRO_ALIGN_RIGHT,"->Return");
                    break;
                default:
                    al_draw_textf(Large_font,Orange,750,350,ALLEGRO_ALIGN_RIGHT,"BGM %.1f", Volume_BGM*10);
                    al_draw_textf(Large_font,Orange,750,410,ALLEGRO_ALIGN_RIGHT,"SFX %.1f", Volume_SFX*10);
                    al_draw_textf(Large_font,Orange,750,530,ALLEGRO_ALIGN_RIGHT,"Return");
        }
            break;
        case 3:
            al_draw_text(Large_font,Orange,400,300,ALLEGRO_ALIGN_CENTER,"Maker:");
            al_draw_text(Large_font,Orange,400,350,ALLEGRO_ALIGN_CENTER,"Tom1236868");
            al_draw_text(Large_font,Redd,400,450,ALLEGRO_ALIGN_CENTER,"->Return");
            break;
        case 4:
            state_controller(0);
        default:
            printf("Unknown Scene Call\n");
    }

    al_flip_display();
}

void GameBody::state_controller(int state)
{
    switch(state)
    {
        case -1:
            game_destroy();
            printf("Unable to initialize.\n");
            exit(-1);
            break;
        case 0:
            game_destroy();
            printf("Manually Exit.\n");
            exit(0);
            break;
        default:
            game_destroy();
            printf("Unexpected Error!\nForce Terminate.\n");
            exit(-2);
    }
    return;
}

void GameBody::game_destroy()
{
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);
    al_destroy_font(Title_font);

    al_destroy_timer(frametimer);

    al_destroy_bitmap(menu_back);
    al_destroy_bitmap(menu_front);

    al_destroy_sample(sample);
    al_destroy_sample_instance(BGM_menu);
    al_destroy_sample_instance(Button);
    al_destroy_sample_instance(Trans);
}


int GameBody::update(float Scrollx)
{
    vector<Bullet>::iterator it;
    vector<Monster>::iterator it2;
    for(it = BulletSet.begin(); it != BulletSet.end(); it++)
    {
        Vector2 Now = (*it).GetPosition();
        Now.sets(Now.get_x()+(*it).GetVelocity(), Now.get_y());
        (*it).Draw(Scrollx , Now);
    }

    for(it = BulletSet.begin(); it != BulletSet.end(); it++)
    {
        int Dist = (*it).GetTravelDistance();
        if(Dist < 400)
            (*it).SetTravelDistance(Dist + abs((*it).GetVelocity()));
        else
        {
            BulletSet.erase(it);
            break;
        }
    }

    for(it2 = MonsterSet.begin(); it2 != MonsterSet.end(); it2++)
    {
        vector<Bullet>::iterator it3;
        for(it3 = BulletSet.begin(); it3 != BulletSet.end(); it3++)
        {
            if((*it2).IsTouching((*it3).GetHitBox()))
            {
                (*it2).LoseHealth((*it3).GetAttackPower());
                BulletSet.erase(it3);
                break;
            }
        }
        if(!((*it2).Isalive()))
            {
                MonsterSet.erase(it2);
                break;
            }
        (*it2).Draw(Scrollx);
    }
}
