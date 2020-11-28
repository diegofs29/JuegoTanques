#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	player = new Player(100, 100, 90, game);
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);

	projectiles.clear();
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		switch (code) {
		case SDLK_d: // derecha
			if(controlMove == 0)
				controlRotate = 1;
			break;
		case SDLK_a: // izquierda
			if (controlMove == 0)
				controlRotate = -1;
			break;
		case SDLK_w: // arriba
			if(controlRotate == 0)
				controlMove = -1;
			break;
		case SDLK_s: // abajo
			if (controlRotate == 0)
				controlMove = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		switch (code) {
		case SDLK_d: // derecha
			if (controlRotate == 1) {
				controlRotate = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlRotate == -1) {
				controlRotate = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMove == -1) {
				controlMove = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMove == 1) {
				controlMove = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	//procesar controles
	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}

	// Mover
	if (controlMove > 0) {
		player->move(1);
	}
	else if (controlMove < 0) {
		player->move(-1);
	}
	else {
		player->move(0);
	}

	// Rotar
	if (controlRotate > 0) {
		player->rotate(2);
	}
	else if (controlRotate < 0) {
		player->rotate(-2);
	}
	else {
		player->rotate(0);
	}

}

void GameLayer::update() {
	player->update();
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();
	for (auto const& projectile : projectiles) {
		projectile->draw();
	}
	player->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}