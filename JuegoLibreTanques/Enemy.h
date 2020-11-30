#pragma once
#include "Actor.h"
class Enemy :
    public Actor
{
public:
    Enemy(string file, float x, float y, int angle, Game* game);
    virtual void update();
};

