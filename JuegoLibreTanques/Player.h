#pragma once

#include "Actor.h"
#include "Projectile.h"

class Player : public Actor
{
public:
	Player(float x, float y, float angle, Game* game);
	void update();
	void move(int axis);
	void rotate(float angle);
	Projectile* shoot();

	float realX;
	float realY;
	int shootCadence = 30;
	int shootTime = 0;
};

