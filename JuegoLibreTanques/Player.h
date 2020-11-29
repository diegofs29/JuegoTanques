#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Animation.h"

class Player : public Actor
{
public:
	Player(float x, float y, float angle, Game* game);
	void update();
	void move(int axis);
	void rotate(float angle);
	Projectile* shoot();
	void draw() override;

	float realX;
	float realY;
	int shootCadence = 30;
	int shootTime = 0;
	int state;

	Animation* aMovingForward;
	Animation* aMovingBackward;
	Animation* aRotatingLeft;
	Animation* aRotatingRight;
	Animation* aShooting;
	Animation* animation; // Referencia a la animación mostrada

private:
	void cambiarEstadoMovimiento(int axis);
	void cambiarEstadoRotacion(int angle);
};

