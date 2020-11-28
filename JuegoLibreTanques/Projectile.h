#pragma once
#include "Actor.h"

class Projectile :
    public Actor
{
public:
    Projectile(float x, float y, int angle, Game* game);
    void update();

    float velocidad;
    float realX;
    float realY;

private:
    void calcularVelocidad();
};

