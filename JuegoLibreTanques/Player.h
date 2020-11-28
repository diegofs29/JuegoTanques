#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
	Player(float x, float y, float angle, Game* game);
	void update();
	void move(int axis);
	void rotate(float angle);

	float realX;
	float realY;
};

