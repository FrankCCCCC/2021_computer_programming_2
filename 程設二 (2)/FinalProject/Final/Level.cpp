#include "Level.h"

Level::Level()
{
    this->level_num = 1;
    this->Map = NULL;
    this->sample = NULL;
    this->BGM = NULL;
}

bool Level::LoadLevel(int stage)
{
    char Buffer[99];
    int pos_x, pos_y, width;
    FILE *file;

    sprintf(Buffer, "./Assets/Map_%d.png", stage);
    Map = al_load_bitmap(Buffer);
    if(Map == NULL)
    {
        printf("Fail to load BackGround!\n");
        return false;
    }
    else printf("Background loaded.\n");

    sprintf(Buffer, "./Assets/Map_%d.ogg", stage);
    sample = al_load_sample(Buffer);
    BGM = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(BGM,ALLEGRO_PLAYMODE_LOOP);
    if(sample == NULL || BGM == NULL)
    {
        printf("Fail to load BGM!\n");
        return false;
    }
    else printf("BGM loaded.\n");

    sprintf(Buffer, "./Assets/Map_%d.txt", stage);
    file = fopen(Buffer,"r");
    if(!file)
    {
        printf("Fail to load Map!\n");
        return false;
    }
    else printf("Map loaded.\n");

    this->level_num = stage;
    this->BlockSets.clear();

    fscanf(file, "%d%d", &level_width, &level_height);
    fscanf(file, "%f%f", &StartX, &StartY);
    level_width = level_width - Window_width;
    printf("Level width %d, height %d. Start at(%.f,%.f)\n", level_width, level_height, StartX, StartY);

    while(fscanf(file, "%d%d%d", &pos_x, &pos_y, &width) != EOF)
    {
        BlockSets.push_back(Block(pos_x,pos_y,width,1));
        printf("Add a Block(%d,%d), %d width.\n", pos_x, pos_y, width);
    }

    fclose(file);

    return true;
}

void Level::Draw(float Scrollx)
{
    al_draw_bitmap(Map,-Scrollx,0,0);
}

bool Level::IsTouchingGround(GameObject* Target)
{
   vector<Block>::iterator it;

   for(it = BlockSets.begin(); it!= BlockSets.end(); it++)
   {
        if((*it).IsTouching(Target->GetHitBox()))
        {
            printf("Touching Down at (%.f,%.f) to Blocks %d\n",Target->GetPosition().get_x(), Target->GetPosition().get_y(), it);
            Target->Moveto(Target->GetPosition().get_x(), (*it).GetPosition().get_y()-(*it).GetHitBox().Get_OffsetY());
            return true;
        }

   }
   return false;
}

ALLEGRO_SAMPLE_INSTANCE* Level::GetBGM()
{
    return BGM;
}

Vector2 Level::GetStartPoint()
{
    Vector2 Start;
    Start.sets(StartX, StartY);
    return Start;
}
