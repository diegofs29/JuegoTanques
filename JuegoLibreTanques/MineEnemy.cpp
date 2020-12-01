#include "MineEnemy.h"

MineEnemy::MineEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/minadorIdle.png", x, y, 72, 102, angle, game) {

}

void MineEnemy::update() {
	Enemy::update();
}