#include "Menu.h"
#include "GameWindow.h"

const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 30;
const int offsetX = 30 + field_width, offsetY = 150;
const int Initial_Health = 10;
const int Initial_Coin = 10;

bool
Menu::isInRange(int point, int startPos, int length)
{
    if(point >= startPos && point <= startPos + length)
        return true;

    return false;
}

bool
Menu::Enough_Coin(int type)
{

    if(type < 0 || type >= Num_TowerType)
        return false;

    return (Coin + need_coin[type] >= 0);
}

Menu::Menu()
{
    char filename[50];

    HealthPoint = Initial_Health;
    Coin = Initial_Coin;
    Score = 0;

    for(int i=0;i<Num_TowerType; i++)
    {
        ALLEGRO_BITMAP *tower;
        sprintf(filename, "./Tower/%s_Menu.png", TowerClass[i]);

        tower = al_load_bitmap(filename);
        menu_tower.push_back(tower);
    }

    love = al_load_bitmap("./Tower/love.png");

    menuFont = al_load_ttf_font("pirulen.ttf", 12, 0); // load font
    infoFont = al_load_ttf_font("pirulen.ttf", 8, 0);
}

Menu::~Menu()
{
    al_destroy_bitmap(love);
    al_destroy_font(menuFont);

    for(int i=0; i < Num_TowerType; i++)
        al_destroy_bitmap(menu_tower[i]);

    menu_tower.clear();
}

void
Menu::Reset()
{
    HealthPoint = Initial_Health;
    Coin = Initial_Coin;
    Score = 0;
    killedMonster = 0;
}

void
Menu::Draw()
{
    char buffer[50];

    sprintf(buffer, "%d", HealthPoint);
    al_draw_bitmap(love, offsetX, 20, 0);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), 2*al_get_bitmap_width(love) + offsetX, 20, 0, buffer);

    sprintf(buffer, "Coin: %d", Coin);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + gapY, 0, buffer);

    sprintf(buffer, "Score: %d", Score);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + 2*gapY, 0, buffer);

    for(int i=0; i < Num_TowerType; i++)
    {
        int pos_x = offsetX + (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + (ThumbHeight + gapY) * (i / 2);

        al_draw_bitmap(menu_tower[i], pos_x, pos_y, 0);
        if(!Enough_Coin(i))
            al_draw_filled_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgba(100, 100, 100, 100));
        else if(i == selectedTower)
        {
            Tower *tower = NULL;
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 0, 0), 0);
            al_draw_filled_rectangle(pos_x + 10 ,pos_y + ThumbHeight-10,pos_x -200,pos_y + ThumbHeight+40,al_map_rgba(0,0,0,30));
            switch(i)
            {
                case 0:
                    tower = new Arcane(0,0);
                    break;
                case 1:
                    tower = new Archer(0,0);
                    break;
                case 2:
                    tower = new Canon(0,0);
                    break;
                case 3:
                    tower = new Poison(0,0);
                    break;
                case 4:
                    tower = new Storm(0,0);
                    break;
                case 5:
                    tower = new Work(0,0);
                    break;
                default:
                    tower = new Tower(0,0);
            }
            al_draw_textf(infoFont,al_map_rgb(255,255,255),pos_x-190,pos_y + ThumbHeight,ALLEGRO_ALIGN_LEFT,"%s", TowerClass[i]);
            al_draw_textf(infoFont,al_map_rgb(255,255,255),pos_x-100,pos_y + ThumbHeight,ALLEGRO_ALIGN_LEFT,"Frequency : %d ", tower->get_frequency());
            al_draw_textf(infoFont,al_map_rgb(255,255,255),pos_x-190,pos_y + ThumbHeight+20,ALLEGRO_ALIGN_LEFT,"Damage : %d ", tower->get_harm_point());
            al_draw_textf(infoFont,al_map_rgb(255,255,255),pos_x-100,pos_y + ThumbHeight+20,ALLEGRO_ALIGN_LEFT,"Speed : %d ", tower->get_velocity());
        }
        else
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255), 0);
    }
}

int
Menu::MouseIn(int mouse_x, int mouse_y)
{
    bool enoughCoin;

    selectedTower = -1;

    for(int i=0; i < Num_TowerType; i++)
    {
        int pos_x = offsetX + (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + (ThumbHeight + gapY) * (i / 2);

        if(isInRange(mouse_x, pos_x, ThumbWidth) && isInRange(mouse_y, pos_y, ThumbHeight))
        {
            if(Enough_Coin(i))
            {
                selectedTower = i;
                break;
            }
        }
    }
    return selectedTower;
}

bool
Menu::Subtract_HP(int escapeNum)
{
    HealthPoint -= escapeNum;

    return (HealthPoint == 0);
}

void
Menu::Gain_Score(int scoreWorth)
{
    killedMonster++;
    Score += scoreWorth;
}


