#include "GameWindow.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)
#define RED al_map_rgb(255,0,0)
#define YELLOW al_map_rgb(255,255,0)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))


float Attack::volume = 1.0;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

bool compare(Tower *t1, Tower *t2)
{
    return (t1->getY() <= t2->getY());
}

void
GameWindow::game_init()
{
    char buffer[50];

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./StartBackground.jpg");
    Stage1 = al_load_bitmap("./SelectScene/level1.jpg");
    Stage2 = al_load_bitmap("./SelectScene/level2.jpg");
    Stage3 = al_load_bitmap("./SelectScene/level3.jpg");
    Stage4 = al_load_bitmap("./SelectScene/level4.jpg");

    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sample = al_load_sample("growl.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("BackgroundMusic.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    level = new LEVEL(1);
    menu = new Menu();
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

bool
GameWindow::isOnRoad()
{
    int startx, starty;
    int widthOfTower;

    widthOfTower = TowerWidth[selectedTower];

    for(int i=0; i < NumOfGrid; i++)
    {
        startx = (i % 15) * 40;
        starty = (i / 15) * 40;

        if(level->isRoad(i)) {
            if((mouse_x + (widthOfTower/2) < startx) || (mouse_x - (widthOfTower/2) > startx + grid_width))
                continue;
            else if((mouse_y + (widthOfTower/2) < starty) || (mouse_y > starty + grid_height))
                continue;
            else
                return true;
        }
    }
    return false;
}

Tower*
GameWindow::create_tower(int type)
{
    Tower *t = NULL;

    if(isOnRoad())
        return t;

    switch(type)
    {
    case ARCANE:
        t = new Arcane(mouse_x, mouse_y);
        break;
    case ARCHER:
        t = new Archer(mouse_x, mouse_y);
        break;
    case CANON:
        t = new Canon(mouse_x, mouse_y);
        break;
    case POISON:
        t = new Poison(mouse_x, mouse_y);
        break;
    case STORM:
        t = new Storm(mouse_x, mouse_y);
        break;
    case WORK:
        t = new Work(mouse_x, mouse_y);
    default:
        break;
    }

    menu->Change_Coin(menu->getTowerCoin(type));

    return t;
}

Monster*
GameWindow::create_monster()
{
    Monster *m = NULL;

    if(level->MonsterNum[WOLF])
    {
        level->MonsterNum[WOLF]--;
        m = new Wolf(level->ReturnPath());
    }
    else if(level->MonsterNum[WOLFKNIGHT])
    {
        level->MonsterNum[WOLFKNIGHT]--;
        m = new WolfKnight(level->ReturnPath());
    }
    else if(level->MonsterNum[DEMONNIJIA])
    {
        level->MonsterNum[DEMONNIJIA]--;
        m = new DemonNijia(level->ReturnPath());
    }
    else if(level->MonsterNum[CAVEMAN])
    {
        level->MonsterNum[CAVEMAN]--;
        m = new CaveMan(level->ReturnPath());
    }
    else
    {
        al_stop_timer(monster_pro);
    }

    return m;
}

void
GameWindow::game_play()
{
    int msg;
    int M;

    srand(time(NULL));

    msg = -1;
    /*
    *  We start the game by calling game_begin to start timer and play music
    * [TODO]:
    *     You may add some function to create starting scene before calling game_begin
    *     e.g: game_start_scene()
    */
    printf("Please enter the mode code : ");
    scanf("%d", &M);
    printf("\n");
    Mode = M;
    while(Mode>1 || Mode<0)
    {
        printf("Invalid mode code! Please try again.\n");
        scanf("%d", &M);
        Mode = M;
    }
    game_start_scene();


    /*
    *  while game is running, the result of game_run will be returned to msg.
    *  If msg is GAME_EXIT, then tower game will terminate.
    */
    while(msg != GAME_EXIT)
        msg = game_run();

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    /*
    * Create two timers to control different parts of tower game:
    *    a. timer: control the animation of each object, stopped when game doesn't run.
    *    b. monster_pro: control the production of monster, stooped when there is no need to produce monster.
    */
    timer = al_create_timer(1.0 / FPS);
    monster_pro = al_create_timer(1.0 * 80 / FPS);

    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font
    Title_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",72,0); //load Title font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));

    // Initializing resources that tower game needs.
    game_init();
}

void GameWindow::draw_start()
{
    int X = event.mouse.x;
    int Y = event.mouse.y;
    al_clear_to_color(BLACK);
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_text(Title_font, BLACK, 400, 50, ALLEGRO_ALIGN_CENTER, "Tower Defense Game");
    if(Y>=280 && Y<=310 && X<=450 && X>=350) al_draw_text(Large_font, RED, 400, 275, ALLEGRO_ALIGN_CENTER, "START");
    else al_draw_text(Large_font, BLACK, 400, 275, ALLEGRO_ALIGN_CENTER, "START");
    if(Mode == 1) al_draw_rectangle(350,280,450,310,YELLOW,0);
    if(Y>=380 && Y<=410 && X<=470 && X>=330) al_draw_text(Large_font, RED, 400, 375, ALLEGRO_ALIGN_CENTER, "OPTION");
    else al_draw_text(Large_font, BLACK, 400, 375, ALLEGRO_ALIGN_CENTER, "OPTION");
    if(Mode == 1) al_draw_rectangle(330,380,470,410,YELLOW,0);
    if(Y>=480 && Y<=510 && X<=450 && X>=350) al_draw_text(Large_font, RED, 400, 475, ALLEGRO_ALIGN_CENTER, "EXIT");
    else al_draw_text(Large_font, BLACK, 400, 475, ALLEGRO_ALIGN_CENTER, "EXIT");
    if(Mode == 1) al_draw_rectangle(350,480,450,510,YELLOW,0);
    if (Mode == 1) al_draw_textf(font, RED, X+10, Y+10, ALLEGRO_ALIGN_LEFT,"(%d, %d)", X, Y);
    al_flip_display();
}

void GameWindow::game_start_scene()
{
    bool Begin = false;

    if(Mode == 1)printf("Loding Start Scene.\n");
    background = al_load_bitmap("./StartScene.jpg");
    draw_start();
    while(Begin != true)
    {
        int X = event.mouse.x;
        int Y = event.mouse.y;
        al_wait_for_event(event_queue,&event);
        draw_start();
        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                show_err_msg(GAME_EXIT);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(X<=450 && X>=350)
                {
                    if(Y>=250 && Y<=300)
                    {
                        Begin = true;
                        game_select();
                    }
                    if(Y>=350 && Y<=400)
                    {
                        Begin = true;
                        game_setting();
                    }
                    if(Y>=450 && Y<=500) show_err_msg(GAME_EXIT);
                }
                break;
            default:
                continue;
        }
    }
}

void GameWindow::draw_select()
{
    int X = 100;
    int Y = 50;

    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_bitmap(Stage1, X, Y, 0);
    al_draw_bitmap(Stage2, X+400, Y, 0);
    al_draw_bitmap(Stage3, X, Y+300, 0);
    al_draw_bitmap(Stage4, X+400, Y+300, 0);
    if(event.mouse.x > X && event.mouse.x < X+200 && event.mouse.y > Y && event.mouse.y < Y+200)
        al_draw_rectangle(X-10,Y-10,X+210,Y+210,YELLOW,20);
    if(event.mouse.x > X+400 && event.mouse.x < X+600 && event.mouse.y > Y && event.mouse.y < Y+200)
        al_draw_rectangle(X+390,Y-10,X+610,Y+210,YELLOW,20);
    if(event.mouse.x > X && event.mouse.x < X+200 && event.mouse.y > Y+300 && event.mouse.y < Y+500)
        al_draw_rectangle(X-10,Y+290,X+210,Y+510,YELLOW,20);
    if(event.mouse.x > X+400 && event.mouse.x < X+600 && event.mouse.y > Y+300 && event.mouse.y < Y+500)
        al_draw_rectangle(X+390,Y+290,X+610,Y+510,YELLOW,20);
    if(event.mouse.x > 350 && event.mouse.x < 450 && event.mouse.y > 560)
        al_draw_text(Medium_font,RED,400,560,ALLEGRO_ALIGN_CENTER,"Back");
    else
        al_draw_text(Medium_font,BLACK,400,560,ALLEGRO_ALIGN_CENTER,"Back");
    if (Mode == 1) al_draw_textf(font, RED, event.mouse.x+10, event.mouse.y+10, ALLEGRO_ALIGN_LEFT,"(%d, %d)", event.mouse.x, event.mouse.y);
    al_flip_display();
}

void GameWindow::game_select()
{
    bool sel = false;

    if(Mode == 1)printf("Loding Select Scene.\n");
    background = al_load_bitmap("./StartBackground.jpg");

    while(!sel)
    {
        al_wait_for_event(event_queue, &event);
        draw_select();
        int X = event.mouse.x;
        int Y = event.mouse.y;
        switch (event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                show_err_msg(GAME_EXIT);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(X > 350 && X < 450 && Y > 560)
                {
                    sel = true;
                    game_start_scene();
                }
                if(X > 100 && X < 300 && Y > 50 && Y < 250)
                {
                    sel = true;
                    level->setLevel(1);
                    game_begin();
                }
                if(X > 500 && X < 700 && Y > 50 && Y < 250)
                {
                    sel = true;
                    level->setLevel(2);
                    game_begin();
                }
                if(X > 100 && X < 300 && Y > 350 && Y < 550)
                {
                    sel = true;
                    level->setLevel(3);
                    game_begin();
                }
                if(X > 500 && X < 700 && Y > 350 && Y < 550)
                {
                    sel = true;
                    level->setLevel(4);
                    game_begin();
                }
                break;
            default:
                continue;
        }
    }
}

void GameWindow::draw_setting(Slider& A, Slider& B)
{
    al_clear_to_color(al_map_rgb(100,100,100));
    A.Draw();
    B.Draw();
    if(event.mouse.x > 350 && event.mouse.x < 450 && event.mouse.y > 560)
        al_draw_text(Medium_font,RED,400,560,ALLEGRO_ALIGN_CENTER,"Back");
    else
        al_draw_text(Medium_font,BLACK,400,560,ALLEGRO_ALIGN_CENTER,"Back");
    if (Mode == 1) al_draw_textf(font, RED, event.mouse.x+10, event.mouse.y+10, ALLEGRO_ALIGN_LEFT,"(%d, %d)", event.mouse.x, event.mouse.y);
    al_flip_display();
}

void GameWindow::game_setting()
{
    bool done = false;
    if(Mode == 1)printf("Loding Setting Scene.\n");
    Slider BGM = Slider(300,200);
    BGM.set_label_content("BGM");
    Slider SFX = Slider(300,400);
    SFX.set_label_content("SFX");
    while(!done)
    {
        al_wait_for_event(event_queue, &event);
        draw_setting(BGM,SFX);
        int X = event.mouse.x;
        int Y = event.mouse.y;
        switch (event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                show_err_msg(GAME_EXIT);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(BGM.isClicked(X,Y))
                {
                    BGM.toggleDrag();
                    while(event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        int Xt = event.mouse.x;
                        int Yt = event.mouse.y;
                        BGM.Drag(Xt,Yt);
                        al_wait_for_event(event_queue, &event);
                        draw_setting(BGM,SFX);
                    }
                    al_set_sample_instance_gain(backgroundSound,BGM.getDegree());
                    if(BGM.isDragged()) BGM.toggleDrag();
                }
                else if(SFX.isClicked(X,Y))
                {
                    SFX.toggleDrag();
                    while(event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        int Xt = event.mouse.x;
                        int Yt = event.mouse.y;
                        SFX.Drag(Xt,Yt);
                        al_wait_for_event(event_queue, &event);
                        draw_setting(BGM,SFX);
                    }
                    set_attack_volume(SFX.getDegree());
                    if(SFX.isDragged()) BGM.toggleDrag();
                }
                if(X > 350 && X < 450 && Y > 560)
                {
                    done = true;
                    game_start_scene();
                }
                break;
            default:
                continue;
                break;
        }
    }
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    draw_running_map();

    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
    al_start_timer(monster_pro);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{
    unsigned int i, j;
    std::list<Tower*>::iterator it;

    /*TODO:*/
    /*Allow towers to detect if monster enters its range*/
    /*Hint: Tower::DetectAttack*/
    for(it = towerSet.begin(); it!= towerSet.end(); it++)
    {
        for(j=0; j < monsterSet.size(); j++)
        {
            Monster *m = monsterSet[j];
            (*it)->DetectAttack(m);
        }
    }


    // update every monster
    // check if it is destroyed or reaches end point
    for(i=0; i < monsterSet.size(); i++)
    {
        bool isDestroyed = false, isReachEnd = false;

        /*TODO:*/
        /*1. For each tower, traverse its attack set*/
        /*2. If the monster collide with any attack, reduce the HP of the monster*/
        /*3. Remember to set isDestroyed to "true" if monster is killed*/
        /*Hint: Tower::TriggerAttack*/


        for(it = towerSet.begin(); it!= towerSet.end(); it++)
        {
            Monster *m = monsterSet[i];
            isDestroyed = (*it)->TriggerAttack(m);
        }

        isReachEnd = monsterSet[i]->Move();

        if(isDestroyed)
        {
            Monster *m = monsterSet[i];

            menu->Change_Coin(m->getWorth());
            menu->Gain_Score(m->getScore());
            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;

        }
        else if(isReachEnd)
        {
            Monster *m = monsterSet[i];

            if(menu->Subtract_HP())
                return GAME_EXIT;

            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;
        }
    }

    /*TODO:*/
    /*1. Update the attack set of each tower*/
    /*Hint: Tower::UpdateAttack*/
    for(it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->UpdateAttack();

    return GAME_CONTINUE;
}

void GameWindow::game_pause()
{
    al_stop_timer(timer);
    al_stop_timer(monster_pro);
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);
    while(pause)
    {
        draw_running_map();
        al_wait_for_event(event_queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                show_err_msg(GAME_EXIT);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    pause = !pause;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.x > 265 && event.mouse.x < 335 && event.mouse.y > 345 && event.mouse.y < 375)
                {
                    pause = !pause;
                    game_reset();
                    game_select();
                }
                if(event.mouse.x > 435 && event.mouse.x < 560 && event.mouse.y > 345 && event.mouse.y < 375)
                {
                    pause = !pause;
                }
                break;
            default:
                continue;
                break;
        }
    }
    al_start_timer(timer);
    al_start_timer(monster_pro);
    al_play_sample_instance(backgroundSound);
}

void
GameWindow::game_reset()
{
    // clear all towers
    for(auto&& child : towerSet) {
        delete child;
    }
    towerSet.clear();
    monsterSet.clear();

    selectedTower = -1;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    mute = false;
    redraw = false;
    menu->Reset();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(monster_pro);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(monster_pro);

    for(int i=0;i<5; i++)
        al_destroy_bitmap(tower[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);

    delete level;
    delete menu;
}

int
GameWindow::process_event()
{
    int i;
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;

            if(Coin_Inc_Count == 0)
                menu->Change_Coin(Coin_Time_Gain);

            Coin_Inc_Count = (Coin_Inc_Count + 1) % CoinSpeed;

            // All monsters are created and destroyed -> Game Exit
            if(monsterSet.size() == 0 && !al_get_timer_started(monster_pro))
            {
                al_stop_timer(timer);
                return GAME_EXIT;
            }

        }
        else {
            Monster *m = create_monster();

            if(m != NULL)
                monsterSet.push_back(m);
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {

            case ALLEGRO_KEY_ESCAPE:
                /*
                * You can add some variable to control if game is paused.
                * e.g: pause
                * In addition to add variable, you also have to modify draw_running_map() and game_update()
                * Or, monsters and towers can still work without being paused
                */
                pause = !pause;
                game_pause();
                break;
            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_R:
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            // Create tower
            if(selectedTower != -1 && mouse_hover(0, 0, field_width, field_height)) {
                Tower *t = create_tower(selectedTower);

                if(t == NULL)
                    printf("Wrong place\n");
                else {
                    towerSet.push_back(t);
                    towerSet.sort(compare);
                }
            }
            /*
            *  Check if any tower is clicked.
            *  If so, cancel the shown circle range of the tower.
            *  In addition, we also re-check if any circle range should show up.
            */
            else if(selectedTower == -1){
                std::list<Tower*>::iterator it = towerSet.begin();
                if(lastClicked != -1)
                {
                    std::advance(it, lastClicked);
                    (*it)->ToggleClicked();
                }
                for(i=0, it = towerSet.begin(); it != towerSet.end(); it++, i++)
                {
                    Circle *circle = (*it)->getCircle();
                    int t_width = (*it)->getWidth();

                    if(mouse_hover(circle->x - t_width/2, circle->y, t_width, t_width/2))
                    {
                        (*it)->ToggleClicked();
                        lastClicked = i;
                        break;
                    } else {
                        lastClicked = -1;
                    }
                }

            }
            // check if user wants to create some kind of tower
            // if so, show tower image attached to cursor
            selectedTower = menu->MouseIn(mouse_x, mouse_y);

        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;

        menu->MouseIn(mouse_x, mouse_y);

    }

    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_running_map()
{
    unsigned int i, j;
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    for(i = 0; i < field_height/40; i++)
    {
        for(j = 0; j < field_width/40; j++)
        {
            char buffer[50];
            sprintf(buffer, "%d", i*15 + j);
            if(level->isRoad(i*15 + j)) {
                al_draw_filled_rectangle(j*40, i*40, j*40+40, i*40+40, al_map_rgb(255, 244, 173));
            }
            // For debug usage, if you want to create a new map, you may turn off this comment.
            // al_draw_text(font, al_map_rgb(0, 0, 0), j*40 + 20, i*40 + 14, ALLEGRO_ALIGN_CENTER, buffer);
        }
    }
    for(i=0; i<monsterSet.size(); i++)
    {
        monsterSet[i]->Draw();
    }


    for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->Draw();

    if(selectedTower != -1)
        Tower::SelectedTower(mouse_x, mouse_y, selectedTower);

    al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));

    menu->Draw();

    if(pause)
    {
        al_draw_filled_rectangle(200,200,600,400,al_map_rgba(0,0,0,50));
        al_draw_text(Large_font,WHITE,400,220,ALLEGRO_ALIGN_CENTER,"PAUSE");
        if (event.mouse.x > 265 && event.mouse.x < 335 && event.mouse.y > 345 && event.mouse.y < 375)
            al_draw_text(Large_font,RED,300,340,ALLEGRO_ALIGN_CENTER,"Exit");
        else al_draw_text(Large_font,BLACK,300,340,ALLEGRO_ALIGN_CENTER,"Exit");
        if(Mode == 1) al_draw_rectangle(265,345,335,375,YELLOW,0);
        if (event.mouse.x > 435 && event.mouse.x < 560 && event.mouse.y > 345 && event.mouse.y < 375)
            al_draw_text(Large_font,RED,500,340,ALLEGRO_ALIGN_CENTER,"Resume");
        else al_draw_text(Large_font,BLACK,500,340,ALLEGRO_ALIGN_CENTER,"Resume");
        if(Mode == 1) al_draw_rectangle(435,345,560,375,YELLOW,0);
    }
    if (Mode == 1) al_draw_textf(font, RED, event.mouse.x+10, event.mouse.y+10, ALLEGRO_ALIGN_LEFT,"(%d, %d)", event.mouse.x, event.mouse.y);

    al_flip_display();
}
