#include "Player.h"

Player::Player(float x, float y, float angle, Game* game)
	: Actor("res/playerIdle.png", x, y, 72, 80, game, angle) {

}

void Player::update() {
	x = x + vx;
	y = y + vy;
}

void Player::move(int axis) {
	float seno = sin(angle * (M_PI / 180)) * 15;
	float coseno = cos(angle * (M_PI / 180)) * 15;
	vx = -axis * seno;
	vy = axis * coseno;
}

void Player::rotate(float angle) {
	if (this->angle == 0)
		this->angle = 360 + angle;
	else if (this->angle == 360)
		this->angle = 0 + angle;
	else
		this->angle += angle;
}