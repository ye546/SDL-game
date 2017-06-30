#pragma once
#include "createWindow.h"
#include "SDL.h"

class gameLoop:public createWindow
{
public:
	
	void handleGameLoop(SDL_Window *window);

	~gameLoop();
};

