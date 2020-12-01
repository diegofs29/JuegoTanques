#include "LightEnemy.h"

LightEnemy::LightEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/ligeroIdle.png", x, y, 64, 79, angle, game) {

}

void LightEnemy::update() {
	Enemy::update();
}
