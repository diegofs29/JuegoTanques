#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/normalIdle.png", x, y, 72, 80, angle, game) {
	rotateTime = rotateMoment;
	updateVelocity();
}


void NormalEnemy::update() {
	Enemy::update();
}