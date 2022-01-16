#include "Player.h"


Player::Player()
{
    this->type = 1;
    this->Position.sets(0.0,0.0);
    this->Collider.Set_Position(Position);
    this->Collider.Set_Width(25);
    this->Collider.Set_Height(45);
}

void Player::Draw(int sta,int Face, float Scrollx)
{
    char Buffer[99];
    state = sta;
    switch(state)
    {
        case Idle:
            if(Frame_count < 10)
            {
                al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                Frame_count++;
            }
            else
            {
                if(Laststate != state)
                {
                    Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                    Laststate = state;
                }
                else
                {
                    Sprite_frame++;
                    if(Sprite_frame > 3) Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                }
            }
            break;
        case Run:
            if(Frame_count < 5)
            {
                al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                Frame_count++;
            }
            else
            {
                if(Laststate != state)
                {
                    Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                    Laststate = state;
                }
                else
                {
                    Sprite_frame++;
                    if(Sprite_frame > 17) Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                }
            }
            break;
        case Jump_Up:
            if(Frame_count < 5)
            {
                al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                Frame_count++;
            }
            else
            {
                if(Laststate != state)
                {
                    Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                    Laststate = state;
                }
                else
                {
                    Sprite_frame++;
                    if(Sprite_frame > 1) Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                }
            }
            break;
        case Jump_MidAir:
            if(Frame_count < 5)
            {
                al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                Frame_count++;
            }
            else
            {
                if(Laststate != state)
                {
                    Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                    Laststate = state;
                }
                else
                {
                    Sprite_frame++;
                    if(Sprite_frame > 2) Sprite_frame = 0;
                    Frame_count = 0;
                    Laststate = Fall;
                }
            }
            break;
        case Fall:
            if(Frame_count < 5)
            {
                al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                Frame_count++;
            }
            else
            {
                if(Laststate != state)
                {
                    Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                    Laststate = state;
                }
                else
                {
                    Sprite_frame++;
                    if(Sprite_frame > 1) Sprite_frame = 0;
                    sprintf(Buffer, "./Assets/Player/%d_%d.png",state,Sprite_frame);
                    Sprite = al_load_bitmap(Buffer);
                    al_draw_bitmap(Sprite,Position.get_x()-Scrollx,Position.get_y(),Face);
                    Frame_count = 0;
                }
            }
            break;
        default:
            break;
    }
}
