#pragma once
#include "Actor.h"
class Municion :
    public Actor
{
public:
    Municion(int x, int y, Game* game);

    int ammo = 5;
    int mines = 1;
};

