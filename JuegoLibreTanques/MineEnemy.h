#pragma once
#include "Enemy.h"
class MineEnemy :
    public Enemy
{
public:
    MineEnemy(float x, float y, int angle, Game* game);
    void update() override;
};

