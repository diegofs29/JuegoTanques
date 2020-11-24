#include "Player.h"

Player::Player(float x, float y, float angle, Game* game)
	: Actor("res/playerIdle.png", x, y, angle, 72, 80, game) {

}

void Player::update() {
	x = x + vx;
	y = y + vy;
}

void Player::move(float axis) {
	vx = axis * 3;
	vy = axis * 3;
}

void Player::rotate(float angle) {
	this->angle += angle;
}