#pragma once
#include "Enemy.h"
class LightEnemy :
    public Enemy
{
public:
    LightEnemy(float x, float y, int angle, Game* game);
    void update() override;
    void updateVelocity() override;

    int rotationAngle = 180;
    int currentRotation = 0;

    int rotation;
};

