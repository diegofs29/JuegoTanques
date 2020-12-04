#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Animation.h"
#include "Mine.h"
#include "Audio.h"

class Player : public Actor
{
public:
	Player(float x, float y, float angle, Game* game);
	void update();
	void move(int axis);
	void rotate(float angle);
	Projectile* shoot();
	Mine* mine();
	void draw(float scrollX = 0, float scrollY = 0) override;

	int ammo = 10;
	int mines = 2;
	int shootCadence = 30;
	int shootTime = 0;
	int mineDelay = 150;
	int mineTime = 0;
	int state;

	Audio* audioShoot;
	Animation* aMovingForward;
	Animation* aMovingBackward;
	Animation* aRotatingLeft;
	Animation* aRotatingRight;
	Animation* aShooting;
	Animation* animation; // Referencia a la animación mostrada

private:
	void cambiarEstadoMovimiento(int axis);
	void cambiarEstadoRotacion(int angle);
};

