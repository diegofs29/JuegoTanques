#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Projectile.h"

#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	
	list<Projectile*> projectiles;

	Background* background;
	Player* player;
	bool controlShoot = false;
	int controlMove = 0;
	int controlRotate = 0;
};

