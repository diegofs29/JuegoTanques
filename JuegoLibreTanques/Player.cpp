#include "Player.h"

Player::Player(float x, float y, float angle, Game* game)
	: Actor("res/playerIdle.png", x, y, 72, 80, game, angle) {
	realX = x;
	realY = y;

	state = game->stateIdle;

	aMovingForward = new Animation("res/playerForward.png", width, height, 576, 80, 1, 8, true, game);
	aMovingBackward = new Animation("res/playerBackward.png", width, height, 576, 80, 1, 8, true, game);
	aRotatingLeft = new Animation("res/playerLeft.png", width, height, 576, 80, 1, 8, true, game);
	aRotatingRight = new Animation("res/playerRight.png", width, height, 576, 80, 1, 8, true, game);

	aShooting = new Animation("res/playerShot.png", width, height, 360, 80, 1, 5, false, game);

	animation = aMovingForward;
}

void Player::update() {
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateIdle;
		}
	}

	if (shootTime > 0) {
		shootTime--;
	}

	cout << state << endl;

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

	realX += vx;
	realY += vy;

	x = realX;
	y = realY;
}

void Player::move(int axis) {
	int vel = 5;

	if (state != game->stateShooting)
		cambiarEstadoMovimiento(axis);

	float seno = sin(angle * (M_PI / 180.0));
	float coseno = cos(angle * (M_PI / 180.0));
	vx = -axis * seno * vel;
	vy = axis * coseno * vel;
}

void Player::cambiarEstadoMovimiento(int axis) {
	if (axis > 0) {
		state = game->stateBackward;
	}
	else if (axis < 0) {
		state = game->stateForward;
	}
	else {
		state = game->stateIdle;
	}
}

void Player::rotate(float angle) {
	if (state != game->stateShooting)
		cambiarEstadoRotacion(angle);

	if (this->angle == 0)
		this->angle = 360 + angle;
	else if (this->angle == 360)
		this->angle = 0 + angle;
	else
		this->angle += angle;
}

void Player::cambiarEstadoRotacion(int angle) {
	if (angle > 0) {
		state = game->stateRight;
	}
	else if (angle < 0) {
		state = game->stateLeft;
	}
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		aShooting->currentFrame = 0;
		state = game->stateShooting;
		shootTime = shootCadence;
		return new Projectile(x, y, angle, game);
	}
	else {
		return NULL;
	}
}

void Player::draw() {
	if (state != game->stateIdle)
		animation->draw(x, y, angle);
	else
		Actor::draw();
}
