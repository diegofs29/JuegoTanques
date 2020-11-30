#include "Enemy.h"

Enemy::Enemy(string file, float x, float y, int angle, Game* game)
	: Actor(file, x, y, 36, 40, game, angle) {
	realX = x;
	realY = y;
}