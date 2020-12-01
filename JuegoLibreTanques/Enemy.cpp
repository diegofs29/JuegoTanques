#include "Enemy.h"

Enemy::Enemy(string file, float x, float y, int width, int height, int angle, Game* game)
	: Actor(file, x, y, width, height, game, angle) {
	realX = x;
	realY = y;
}

void Enemy::update() {
	if (rotating) {
		rotate(2);
		updateVelocity();
		if (vx != 0 || vy != 0) {
			rotating = false;
			rotateTime = rotateMoment;
		}
	}
	if (rotateTime > 0) {
		rotateTime--;
	}
	else {
		rotating = true;
	}

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

void Enemy::updateVelocity() {
	if (angle == 0) {
		vy = -3;
		vx = 0;
	}
	else if (angle == 90 || angle == 360) {
		vx = 3;
		vy = 0;
	}
	else if (angle == 180) {
		vy = 3;
		vx = 0;
	}
	else if (angle == 270) {
		vx = -3;
		vy = 0;
	}
	else {
		vx = vy = 0;
	}
}