#pragma once
#include "Enemy.h"
class NormalEnemy :
    public Enemy
{
public:
    NormalEnemy(float x, float y, int angle, Game* game);
    void update() override;
    
    int rotateTime = 0;
    int rotateMoment = 50;

private:
    void updateVelocity();
};

