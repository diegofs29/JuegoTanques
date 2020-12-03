#pragma once
#include "Actor.h"
class Bonus :
    public Actor
{
public:
    Bonus(int x, int y, Game* game);

    int points = 100;
};

