#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game, int angle = 0);
	~Actor();
	virtual void draw(float scrollX = 0, float scrollY = 0);
	bool isOverlap(Actor* actor);
	bool containsPoint(int pointX, int pointY); // contiene punto
	bool isInRender(float scrollX = 0, float scrollY = 0);

	bool clicked; // Est� pulsado
	SDL_Texture* texture;
	int x;
	int y;
	float realX;
	float realY;
	float vx;
	float vy;
	int angle;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game; // referencia al juego
};