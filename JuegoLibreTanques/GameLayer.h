#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Projectile.h"
#include "Tile.h"
#include "Space.h"

#include <list>
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();

	float scrollX;
	float scrollY;
	int mapWidth;
	int mapHeight;

	list<Tile*> barros;
	list<Tile*> solidos;
	list<Tile*> destruibles;
	list<Projectile*> projectiles;

	Background* background;
	Player* player;
	Space* space;
	bool controlShoot = false;
	int controlMove = 0;
	int controlRotate = 0;
};

