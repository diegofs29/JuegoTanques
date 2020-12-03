#pragma once

// Todas las librerias de SDL y otras utilidades
#include <iostream>
#include <string>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//Clases mias
#include "Layer.h"
class Layer;

// Valores generales
#define WIDTH 1280
#define HEIGHT 720

class Game
{
public:
	Game();
	void loop();
	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador
	bool loopActive; // Juego activo
	Layer* layer;
	Layer* menuLayer;
	Layer* gameLayer;
	TTF_Font* font;

	int const stateForward = 1;
	int const stateBackward = 2;
	int const stateLeft = 3;
	int const stateRight = 4;
	int const stateShooting = 5;
	int const stateDying = 6;
	int const stateDead = 7;
	int const stateIdle = 8;

	int input;
	int const inputKeyboard = 1;
	int const inputMouse = 2;
	int const inputGamePad = 3;
};