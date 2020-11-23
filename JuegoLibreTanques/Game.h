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
	Layer* gameLayer;
};