#pragma once
#include "Actor.h"
#include "Animation.h"
#include "Projectile.h"
#include "Mine.h"
#include "Audio.h"

class Enemy :
    public Actor
{
public:
    Enemy(string file, float x, float y, int width, int height, int angle, Game* game, float velocity = 5);
    virtual void update();
    void rotate(int angle);
    virtual void updateVelocity();
    void changeAnimation();
    void draw(float scrollX = 0, float scrollY = 0) override;
    virtual Projectile* shoot();
    virtual Mine* mine();
    void cambiarEstadoMovimiento();
    void cambiarEstadoRotacion(int angle);
    bool checkSpeed();

    bool rotating = false;
    int rotateTime = 0;
    int rotateMoment = 75;
    int state;
    float velocity;
    int shootCadence = 50;
    int shootTime = 0;
    float realvx;
    float realvy;

    Audio* audioShoot;
    Animation* aMovingForward;
    Animation* aMovingBackward;
    Animation* aRotatingLeft;
    Animation* aRotatingRight;
    Animation* aShooting;
    Animation* animation; // Referencia a la animación mostrada

};

