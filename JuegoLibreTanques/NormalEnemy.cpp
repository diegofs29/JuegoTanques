#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/normalIdle.png", x, y, 72, 80, angle, game) {
	rotateTime = rotateMoment;
	updateVelocity();
}


void NormalEnemy::update() {
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

	Enemy::update();
}

void NormalEnemy::updateVelocity() {
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