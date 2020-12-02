#pragma once
#include "Enemy.h"
class MineEnemy :
    public Enemy
{
public:
    MineEnemy(float x, float y, int angle, Game* game);
    void update() override;
    Projectile* shoot() override;
    Mine* mine() override;

    int rotationAngle;
    int rotation;
    int timeMine = 0;
    int cadenceMine = 250;
};

