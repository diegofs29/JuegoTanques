#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/normalIdle.png", x, y, 72, 80, angle, game) {
	rotateTime = rotateMoment;
	
	aMovingForward = new Animation("res/normalForward.png", width, height, 576, 80, 1, 8, true, game);
	aMovingBackward = new Animation("res/normalBackward.png", width, height, 576, 80, 1, 8, true, game);
	aRotatingLeft = new Animation("res/normalLeft.png", width, height, 576, 80, 1, 8, true, game);
	aRotatingRight = new Animation("res/normalRight.png", width, height, 576, 80, 1, 8, true, game);

	aShooting = new Animation("res/normalShot.png", width, height, 360, 80, 1, 5, false, game);
}


void NormalEnemy::update() {
	Enemy::update();
}