#include "gameLoop.h"
#include "SDL.h"

void gameLoop::handleGameLoop(SDL_Window *window)
{
	bool isRunning = true;
	SDL_Event ev;
	SDL_Surface *movingLad = nullptr;
	SDL_Rect xd;

	while (isRunning) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				isRunning = false;
			}
			if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym) {
				case SDLK_w:

				}
			}
			SDL_BlitSurface(movingLad, xd.y, , );
			SDL_UpdateWindowSurface(window);
		}
	}
}

gameLoop::~gameLoop()
{
}
