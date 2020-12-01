#include "MineEnemy.h"

MineEnemy::MineEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/minadorIdle.png", x, y, 72, 102, angle, game, 3) {

	aMovingForward = new Animation("res/minadorForward.png", width, height, 576, 102, 1, 8, true, game);
	aMovingBackward = new Animation("res/minadorBackward.png", width, height, 576, 102, 1, 8, true, game);
	aRotatingLeft = new Animation("res/minadorLeft.png", width, height, 576, 102, 1, 8, true, game);
	aRotatingRight = new Animation("res/minadorRight.png", width, height, 576, 102, 1, 8, true, game);

	aShooting = new Animation("res/minadorShot.png", width, height, 360, 102, 1, 5, false, game);

}

void MineEnemy::update() {
	Enemy::update();
}