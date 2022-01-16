#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "GameObject.h"

class Block : public GameObject
{
    public:
        Block();
        Block(float,float,float,float);
        void Draw();
};


#endif // BLOCK_H_INCLUDED
