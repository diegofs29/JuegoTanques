#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	space = new Space();

	scrollX = 0;
	scrollY = 0;

	barros.clear();
	solidos.clear();
	destruibles.clear();

	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);

	projectiles.clear();

	loadMap("res/1.txt");
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
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
			if(controlMove == 0 && controlRotate == 0)
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
			space->addDynamicActor(newProjectile);
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

void GameLayer::loadMap(string name) {
	int lineas = 0;
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 128; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				float x = 128 / 2 + j * 128; // x central
				float y = 128 + i * 128; // y suelo
				loadMapObject(character, x, y);
			}
			lineas++;
		}
	}
	mapHeight = lineas * 128;
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'P': {
		player = new Player(x, y, 90, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case 'B': {
		Tile* tile = new Tile("res/barro.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		barros.push_back(tile);
		space->addSlowingActor(tile);
		break;
	}
	case 'S': {
		Tile* tile = new Tile("res/bloquesolido.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		solidos.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'D': {
		Tile* tile = new Tile("res/bloqueagrietado.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		destruibles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}


void GameLayer::update() {
	space->update();
	player->update();
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	calculateScroll();

	background->draw();
	for (auto const& barro : barros) {
		barro->draw(scrollX, scrollY);
	}
	for (auto const& solido : solidos) {
		solido->draw(scrollX, scrollY);
	}
	for (auto const& destruible : destruibles) {
		destruible->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}
	player->draw(scrollX, scrollY);

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::calculateScroll() {
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}
	
	if (player->y > HEIGHT * 0.3) {
		if (player->y - scrollY < HEIGHT * 0.3) {
			scrollY = player->y - HEIGHT * 0.3;
		}
	}
	if (player->y < mapHeight - HEIGHT * 0.3) {
		if (player->y - scrollY > HEIGHT * 0.7) {
			scrollY = player->y - HEIGHT * 0.7;
		}
	}
}