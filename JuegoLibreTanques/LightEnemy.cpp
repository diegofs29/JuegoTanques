#include "LightEnemy.h"

LightEnemy::LightEnemy(float x, float y, int angle, Game* game) :
	Enemy("res/ligeroIdle.png", x, y, 64, 79, angle, game, 7) {

	aMovingForward = new Animation("res/ligeroForward.png", width, height, 512, 79, 1, 8, true, game);
	aMovingBackward = new Animation("res/ligeroBackward.png", width, height, 512, 79, 1, 8, true, game);
	aRotatingLeft = new Animation("res/ligeroLeft.png", width, height, 512, 79, 1, 8, true, game);
	aRotatingRight = new Animation("res/ligeroRight.png", width, height, 512, 79, 1, 8, true, game);

	aShooting = new Animation("res/ligeroShot.png", width, height, 320, 79, 1, 5, false, game);

	state = game->stateIdle;

}

void LightEnemy::update() {
	bool endAnimation = false;
	if (state != game->stateIdle)
		endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateIdle;
			if(!rotating)
				updateVelocity();
		}
	}

	if (rotating && state != game->stateShooting) {
		currentRotation += 2;
		rotate(2);
		if (currentRotation >= rotationAngle) {
			rotating = false;
			currentRotation = 0;
			rotateTime = rotateMoment;
			updateVelocity();
		}
	}

	if (rotateTime > 0) {
		rotateTime--;
	}
	else if (!rotating) {
		rotating = true;
		rotationAngle = rand() % 361 + (-180);
		cout << rotationAngle << endl;
		if (rotationAngle < 0)
			rotation = -2;
		else if (rotationAngle > 0)
			rotation = 2;
		else {
			rotating = false;
			rotateTime = rotateMoment;
		}
		if (rotating)
			realvx = vx = 0;
			realvy = vy = 0;
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

	changeAnimation();

	x = realX;
	y = realY;
}

void LightEnemy::updateVelocity() {
	float seno = sin(angle * (M_PI / 180.0));
	float coseno = cos(angle * (M_PI / 180.0));
	realvx = vx = seno * velocity;
	realvy = vy = -coseno * velocity;

	cambiarEstadoMovimiento();
}