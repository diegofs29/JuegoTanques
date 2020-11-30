#pragma once
#include "Actor.h"
class Enemy :
    public Actor
{
public:
    Enemy(string file, float x, float y, int width, int height, int angle, Game* game);
    virtual void update();
    void rotate(int angle);

    bool rotating = false;
};

