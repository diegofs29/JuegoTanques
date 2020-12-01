#include "LightEnemy.h"

LightEnemy::LightEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/ligeroIdle.png", x, y, 64, 79, angle, game, 7) {

	aMovingForward = new Animation("res/ligeroForward.png", width, height, 512, 79, 1, 8, true, game);
	aMovingBackward = new Animation("res/ligeroBackward.png", width, height, 512, 79, 1, 8, true, game);
	aRotatingLeft = new Animation("res/ligeroLeft.png", width, height, 512, 79, 1, 8, true, game);
	aRotatingRight = new Animation("res/ligeroRight.png", width, height, 512, 79, 1, 8, true, game);

	aShooting = new Animation("res/ligeroShot.png", width, height, 320, 79, 1, 5, false, game);

}

void LightEnemy::update() {
	Enemy::update();
}
