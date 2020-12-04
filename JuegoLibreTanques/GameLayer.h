#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Projectile.h"
#include "Tile.h"
#include "Space.h"
#include "Mine.h"
#include "Enemy.h"
#include "Text.h"
#include "Municion.h"
#include "Bonus.h"
#include "Audio.h" 

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
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();

	int scrollX;
	int scrollY;
	int mapWidth;
	int mapHeight;

	list<Tile*> barros;
	list<Tile*> solidos;
	list<Tile*> destruibles;
	list<Projectile*> projectiles;
	list<Mine*> minas;
	list<Enemy*> enemigos;
	list<Municion*> ammos;
	list<Bonus*> bonuses;

	Audio* audioBackground;
	Background* background;
	Player* player;
	Space* space;
	Actor* message;
	SDL_GameController* gamePad;

	bool moving = false;
	bool rotating = false;
	bool pause;
	bool controlContinue = false;
	bool controlMine = false;
	bool controlShoot = false;
	int controlMove = 0;
	int controlRotate = 0;
	int points;
	Text* textPoints;
	Text* textAmmo;
	Text* textMines;
};

