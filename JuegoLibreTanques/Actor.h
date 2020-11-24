#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(string filename, float x, float y, float angle, int width, int height, Game* game);
	virtual void draw();
	SDL_Texture* texture;
	int x;
	int y;
	float vx;
	float vy;
	float angle;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game; // referencia al juego
};