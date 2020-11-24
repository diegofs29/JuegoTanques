#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
	Player(float x, float y, float angle, Game* game);
	void update();
	void move(float axis);
	void rotate(float angle);
};

