#include "Player.h"

Player::Player(float x, float y, float angle, Game* game)
	: Actor("res/playerIdle.png", x, y, 72, 80, game, angle) {
	realX = x;
	realY = y;
}

void Player::update() {
	realX += vx;
	realY += vy;
	x = realX;
	y = realY;
}

void Player::move(int axis) {
	int vel = 7;

	float seno = sin(angle * (M_PI / 180.0));
	float coseno = cos(angle * (M_PI / 180.0));
	vx = -axis * seno * vel;
	vy = axis * coseno * vel;
}

void Player::rotate(float angle) {
	if (this->angle == 0)
		this->angle = 360 + angle;
	else if (this->angle == 360)
		this->angle = 0 + angle;
	else
		this->angle += angle;
}