#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
//////Define some useful static//////
#define Redd al_map_rgb(255, 0, 0)
#define White al_map_rgb(255, 255, 255)
#define Black al_map_rgb(0, 0, 0)
#define Orange al_map_rgb(255, 153, 0)
/////Include game's header//////

using namespace std;

enum State{Idle = 0, Run, Jump_Up, Jump_MidAir,Fall, Shoot};
enum Type{Default = 0, player, block, bullet, monster};

//Frame Rate
const float FPS = 60.00;
//Window Solution
const unsigned int Window_width = 800;
const unsigned int Window_hegith = 600;

#endif // GLOBAL_H_INCLUDED
