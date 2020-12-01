#include "Enemy.h"

Enemy::Enemy(string file, float x, float y, int width, int height, int angle, Game* game, float velocity)
	: Actor(file, x, y, width, height, game, angle) {
	realX = x;
	realY = y;

	shootTime = shootCadence;

	this->velocity = velocity;

	state = game->stateIdle;
}

void Enemy::update() {
	bool endAnimation = false;
	if(state != game->stateIdle)
		endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateIdle;
		}
	}

	if (rotating) {
		rotate(2);
		if (this->angle % 90 == 0) {
			rotating = false;
			rotateTime = rotateMoment;
			updateVelocity();
		}
	}
	if (rotateTime > 0) {
		rotateTime--;
	}
	else {
		rotating = true;
		vx = vy = 0;
	}

	if (state == game->stateForward)
		animation = aMovingForward;
	else if (state == game->stateBackward)
		animation = aMovingBackward;
	else if (state == game->stateLeft)
		animation = aRotatingLeft;
	else if (state == game->stateRight)
		animation = aRotatingRight;
	else if (state == game->stateShooting)
		animation = aShooting;

	if (shootTime > 0) {
		shootTime--;
	}

	x = realX;
	y = realY;
}

void Enemy::cambiarEstadoMovimiento() {
	if (!rotating) {
		if (vx != 0 || vy != 0) {
			state = game->stateForward;
		}
		else {
			state = game->stateIdle;
		}
	}
}

void Enemy::rotate(int angle) {
	this->angle += angle;
	if (this->angle >= 360)
		this->angle = 0;
	cambiarEstadoRotacion(angle);
}

void Enemy::cambiarEstadoRotacion(int angle) {
	if (angle > 0) {
		state = game->stateRight;
	}
	else if (angle < 0) {
		state = game->stateLeft;
	}
}

void Enemy::updateVelocity() {
	if (angle == 0) {
		vy = -velocity;
		vx = 0;
	}
	else if (angle == 90 || angle == 360) {
		vx = velocity;
		vy = 0;
	}
	else if (angle == 180) {
		vy = velocity;
		vx = 0;
	}
	else if (angle == 270) {
		vx = -velocity;
		vy = 0;
	}
	else {
		vx = vy = 0;
	}
	cambiarEstadoMovimiento();
}

Projectile* Enemy::shoot() {
	if (shootTime == 0) {
		aShooting->currentFrame = 0;
		state = game->stateShooting;
		shootTime = shootCadence;
		int posX = (width/2 + 5) * sin(angle * (M_PI / 180));
		int posY = -(height/2 + 5) * cos(angle * (M_PI / 180));
		return new Projectile(x + posX, y + posY, angle, game);
	}
	else {
		return NULL;
	}
}

Mine* Enemy::mine() {
	return NULL;
}

void Enemy::draw(float scrollX, float scrollY) {
	if (state != game->stateIdle)
		animation->draw(x - scrollX, y - scrollY, angle);
	else
		Actor::draw(scrollX, scrollY);
}