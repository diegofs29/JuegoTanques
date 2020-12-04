#include "MineEnemy.h"

MineEnemy::MineEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/minadorIdle.png", x, y, 72, 102, angle, game, 3) {

	aMovingForward = new Animation("res/minadorForward.png", width, height, 576, 102, 1, 8, true, game);
	aMovingBackward = new Animation("res/minadorBackward.png", width, height, 576, 102, 1, 8, true, game);
	aRotatingLeft = new Animation("res/minadorLeft.png", width, height, 576, 102, 1, 8, true, game);
	aRotatingRight = new Animation("res/minadorRight.png", width, height, 576, 102, 1, 8, true, game);

	aShooting = new Animation("res/minadorShot.png", width, height, 360, 102, 1, 5, false, game);

	state = game->stateIdle;

	rotateTime = rotateMoment;

	timeMine = cadenceMine;

	audioShoot = new Audio("res/disparo.wav", false);
}

void MineEnemy::update() {
	bool endAnimation = false;
	if (state != game->stateIdle)
		endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateIdle;
			if (!rotating)
				updateVelocity();
		}
	}

	if (rotating && state != game->stateShooting) {
		rotate(rotation);
		if (abs(this->angle) % 90 == 0) {
			rotating = false;
			rotateTime = rotateMoment;
			updateVelocity();
		}
	}

	if (rotateTime > 0) {
		rotateTime--;
	}
	else if (!rotating) {
		rotating = true;
		rotationAngle = rand() % 3 - 1;
		if (rotationAngle < 0)
			rotation = -2;
		else if (rotationAngle > 0)
			rotation = 2;
		else {
			rotating = false;
			rotateTime = rotateMoment;
		}
		if (rotating) {
			realvx = vx = 0;
			realvy = vy = 0;
		}
	}

	bool crash = checkSpeed();

	if (crash) {
		rotating = true;
		rotationAngle = 90;
		realvx = vx = 0;
		realvy = vy = 0;
	}

	if (shootTime > 0) {
		shootTime--;
	}
	if (timeMine > 0) {
		timeMine--;
	}

	if (!rotating && state != game->stateShooting)
		updateVelocity();
	changeAnimation();

	x = realX;
	y = realY;
}

Projectile* MineEnemy::shoot() {
	if (shootTime == 0) {
		audioShoot->play();
		aShooting->currentFrame = 0;
		state = game->stateShooting;
		shootTime = shootCadence;
		realvx = vx = 0;
		realvy = vy = 0;
		int posX = (width / 2 + 10) * sin(angle * (M_PI / 180));
		int posY = -(height / 2 + 10) * cos(angle * (M_PI / 180));
		return new Projectile(x + posX, y + posY, angle, game);
	}
	else {
		return NULL;
	}
}

Mine* MineEnemy::mine() {
	if (timeMine == 0) {
		timeMine = cadenceMine;
		int posX = -60 * sin(angle * (M_PI / 180));
		int posY = 60 * cos(angle * (M_PI / 180));
		return new Mine(x + posX, y + posY, game);
	}
	else {
		return NULL;
	}
}