#include "Enemy.h"

Enemy::Enemy(string file, float x, float y, int width, int height, int angle, Game* game)
	: Actor(file, x, y, width, height, game, angle) {
	realX = x;
	realY = y;
}

void Enemy::update() {
	realX += vx;
	realY += vy;

	x = realX;
	y = realY;
}

void Enemy::rotate(int angle) {
	this->angle += angle;
	if (this->angle >= 360)
		this->angle = 0;
}