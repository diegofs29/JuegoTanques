#include "Projectile.h"

Projectile::Projectile(float x, float y, int angle, Game* game) :
	Actor("res/disparo.png", x, y, 8, 8, game, angle) {
	velocidad = 20;
	realX = x;
	realY = y;
}

void Projectile::update() {
	calcularVelocidad();
	realX += vx;
	realY += vy;
	x = realX;
	y = realY;
}

void Projectile::calcularVelocidad() {
	float seno = sin(angle * (M_PI / 180.0));
	float coseno = cos(angle * (M_PI / 180.0));
	realVx = vx = seno * velocidad;
	realVy = vy = -coseno * velocidad;
}