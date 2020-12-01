#pragma once
#include "Actor.h"
#include "Animation.h"

class Enemy :
    public Actor
{
public:
    Enemy(string file, float x, float y, int width, int height, int angle, Game* game, float velocity = 5);
    virtual void update();
    void rotate(int angle);
    void updateVelocity();
    void draw(float scrollX = 0, float scrollY = 0) override;

    bool rotating = false;
    int rotateTime = 0;
    int rotateMoment = 50;
    int state;
    float velocity;

    Animation* aMovingForward;
    Animation* aMovingBackward;
    Animation* aRotatingLeft;
    Animation* aRotatingRight;
    Animation* aShooting;
    Animation* animation; // Referencia a la animación mostrada

private:
    void cambiarEstadoMovimiento();
    void cambiarEstadoRotacion(int angle);
};

