#include "GameLayer.h"
#include "NormalEnemy.h"
#include "LightEnemy.h"
#include "MineEnemy.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/instruccionesTeclado.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

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

	enemigos.clear();
	projectiles.clear();
	minas.clear();

	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = "Puntos: " + to_string(points);
	
	loadMap("res/2.txt");
	
	textAmmo = new Text("hola", WIDTH * 0.08, HEIGHT * 0.04, game);
	textAmmo->content = "Municion: " + to_string(player->ammo);
	
	textMines = new Text("hola", WIDTH * 0.5, HEIGHT * 0.04, game);
	textMines->content = "Minas: " + to_string(player->mines);
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
			if(!pause)
				if(controlMove == 0 && controlRotate == 0)
					controlShoot = true;
			controlContinue = true;
			break;
		case SDLK_m:	// minea
			if (controlMove == 0 && controlRotate == 0)
				controlMine = true;
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
		case SDLK_m:	// minea
			controlMine = false;
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
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}

	// Disparar
	if (controlShoot && !pause) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
		textAmmo->content = "Municion: " + to_string(player->ammo);
	}

	if (controlMine && !pause) {
		Mine* newMine = player->mine();
		if (newMine != NULL) {
			minas.push_back(newMine);
		}
		textMines->content = "Minas: " + to_string(player->mines);
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
	case 'N': {
		Enemy* enemy = new NormalEnemy(x, y, 90, game);
		enemigos.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'L': {
		Enemy* enemy = new LightEnemy(x, y, 90, game);
		enemigos.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'M': {
		Enemy* enemy = new MineEnemy(x, y, 90, game);
		enemigos.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'A': {
		Municion* ammo = new Municion(x, y, game);
		ammos.push_back(ammo);
		break;
	}
	case 'X': {
		Bonus* bonus = new Bonus(x, y, game);
		bonuses.push_back(bonus);
		break;
	}
	}
}

void GameLayer::update() {
	if (pause) {
		return;
	}

	//Nivel superado
	if (enemigos.size() == 0) {
		//game->currentLevel++;
		//if (game->currentLevel > game->finalLevel) {
			//game->currentLevel = 0;
		//}
		message = new Actor("res/gameSuccess.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		init();

	}

	space->update();
	player->update();
	for (auto const& enemigo : enemigos) {
		enemigo->update();
		Projectile* p = enemigo->shoot();
		if (p != NULL) {
			projectiles.push_back(p);
		}
		Mine* m = enemigo->mine();
		if (m != NULL) {
			minas.push_back(m);
		}
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& projectile : projectiles) {
		if (player->isOverlap(projectile)) {
			message = new Actor("res/gameOver.png", WIDTH * 0.5, HEIGHT * 0.5,
				WIDTH, HEIGHT, game);
			pause = true;
			init();
			break;
		}
	}

	for (auto const& mina : minas) {
		if (player->isOverlap(mina)) {
			message = new Actor("res/gameOver.png", WIDTH * 0.5, HEIGHT * 0.5,
				WIDTH, HEIGHT, game);
			pause = true;
			init();
			break;
		}
	}

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<Tile*> deleteDestruibles;
	list<Mine*> deleteMinas;
	list<Municion*> deleteAmmos;
	list<Bonus*> deleteBonuses;

	for (auto const& bonus : bonuses) {
		if (player->isOverlap(bonus)) {
			points += bonus->points;
			bool bInList = std::find(deleteBonuses.begin(),
				deleteBonuses.end(),
				bonus) != deleteBonuses.end();

			if (!bInList) {
				deleteBonuses.push_back(bonus);
			}
			textPoints->content = "Puntos: " + to_string(points);
		}
	}

	for (auto const& ammo : ammos) {
		if (player->isOverlap(ammo)) {
			player->ammo += ammo->ammo;
			player->mines += ammo->mines;
			bool aInList = std::find(deleteAmmos.begin(),
				deleteAmmos.end(),
				ammo) != deleteAmmos.end();

			if (!aInList) {
				deleteAmmos.push_back(ammo);
			}
			textAmmo->content = "Municion: " + to_string(player->ammo);
			textMines->content = "Minas: " + to_string(player->mines);
		}
	}

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender(scrollX) == false 
			|| projectile->vx != projectile->realVx || projectile->vy != projectile->realVy) {
			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}


	for (auto const& enemy : enemigos) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);
				}

				points += 30;
				textPoints->content = "Puntos: " + to_string(points);

			}
		}
	}

	for (auto const& destruible : destruibles) {
		for (auto const& projectile : projectiles) {
			if (destruible->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool dInList = std::find(deleteDestruibles.begin(),
					deleteDestruibles.end(),
					destruible) != deleteDestruibles.end();

				if (!dInList) {
					deleteDestruibles.push_back(destruible);
				}

				points += 10;
				textPoints->content = "Puntos: " + to_string(points);
			}
		}
	}

	for (auto const& mina : minas) {
		for (auto const& enemy : enemigos) {
			if (mina->isOverlap(enemy)) {
				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);
				}

				bool mInList = std::find(deleteMinas.begin(),
					deleteMinas.end(),
					mina) != deleteMinas.end();

				if (!mInList) {
					deleteMinas.push_back(mina);
				}
				points += 50;
				textPoints->content = "Puntos: " + to_string(points);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemigos.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
		delete delEnemy;
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delDestruible : deleteDestruibles) {
		destruibles.remove(delDestruible);
		space->removeStaticActor(delDestruible);
		delete delDestruible;
	}
	deleteDestruibles.clear();

	for (auto const& delMina : deleteMinas) {
		minas.remove(delMina);
		delete delMina;
	}
	deleteMinas.clear();

	for (auto const& delAmmo : deleteAmmos) {
		ammos.remove(delAmmo);
		delete delAmmo;
	}

	deleteAmmos.clear();

	for (auto const& delBonus : deleteBonuses) {
		bonuses.remove(delBonus);
		delete delBonus;
	}

	deleteBonuses.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	calculateScroll();

	background->draw();
	for (auto const& barro : barros) {
		barro->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}
	for (auto const& mine : minas) {
		mine->draw(scrollX, scrollY);
	}
	for (auto const& solido : solidos) {
		solido->draw(scrollX, scrollY);
	}
	for (auto const& destruible : destruibles) {
		destruible->draw(scrollX, scrollY);
	}
	player->draw(scrollX, scrollY);
	for (auto const& enemigo : enemigos) {
 		enemigo->draw(scrollX, scrollY);
	}
	for (auto const& ammo : ammos) {
		ammo->draw(scrollX, scrollY);
	}
	for (auto const& bonus : bonuses) {
		bonus->draw(scrollX, scrollY);
	}
	textPoints->draw();
	textAmmo->draw();
	textMines->draw();

	if (pause) {
		message->draw();
	}

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