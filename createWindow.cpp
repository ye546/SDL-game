#include "createWindow.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "renderTexture.h"
#include "SDL_image.h"
#include "SDL_Mixer.h"// for audio purposes
#include "movement.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define IMG_SIZE 70

//global variables
bool isRunning = true;
bool jumpAllowed = true;
const Uint8 *keystate = nullptr;
SDL_Rect player;
SDL_Event ev;
int number = 0;
int jumpVal = 150;



int createWindow::window()
{
	srand(time(NULL));
	renderTexture textureObj;
	SDL_Window *window1 = nullptr;
	SDL_Texture *character = nullptr;
	SDL_Texture *background = nullptr;
	SDL_Texture *selbie = nullptr;
	SDL_Texture *score = nullptr;
	Mix_Music *emeralds = nullptr;
	Mix_Chunk *deathSpeech = nullptr;
	SDL_Renderer *renderTarget = nullptr;

	SDL_Rect scrolling;
	SDL_Rect scrolling2;
	SDL_Rect selbiexd;
	SDL_Rect scorePlacement;

	//defines w, h, x, y 
	scrolling.w = 1301;
	scrolling.h = 480;
	scrolling.x = 0;
	scrolling.y = 0;

	//defines w, h, x, y 
	scrolling2.w = 1301;
	scrolling2.h = 480;
	scrolling2.x = 1301;
	scrolling2.y = 0;

	//defines w, h, x, y 
	selbiexd.w = 70;
	selbiexd.h = 70;
	selbiexd.x = 650 + rand() % 1000;
	selbiexd.y = 410;

	//defines w, h, x, y 
	player.w = 30;
	player.h = 100;
	player.y = 380;
	player.x = 150;


	//defines w, h, x, y 
	scorePlacement.y = 0;
	scorePlacement.x = 0;
	scorePlacement.w = 100;
	scorePlacement.h = 50;
	
	//initializes SDL_VIDEO and SDL_AUDIO
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window1 = SDL_CreateWindow("worst game in the history of dota", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	character = textureObj.loadingTexture("player.png", renderTarget);
	background = textureObj.loadingTexture("background.png", renderTarget);
	selbie = textureObj.loadingTexture("selbie.png", renderTarget);

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("error4 %s", Mix_GetError());
	}

	//background music

	//deathSpeech = Mix_LoadWAV("deathSpeech");
	emeralds = Mix_LoadMUS("emeralds.mp3");
	Mix_PlayMusic(emeralds, -1);

	//main game loop
	while (isRunning) 
	{
		//handles movement, duh
		movement();
		
		//moves the obstacle and background
		scrolling.x -= 2;
		scrolling2.x -= 2;
		selbiexd.x -= 2;

		//renders all the textures on the screen
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, score, NULL, &scorePlacement);
		SDL_RenderCopy(renderTarget, background, NULL, &scrolling);
		SDL_RenderCopy(renderTarget, background, NULL, &scrolling2);
		SDL_RenderCopy(renderTarget, selbie, NULL, &selbiexd);
		SDL_RenderCopy(renderTarget, character, NULL, &player);
		SDL_RenderPresent(renderTarget);

		collision(player, selbiexd);

		if (!collision(player, selbiexd))
		{
			isRunning = false;
			break;
		}

		//this makes sure the backgrounds move, and once it's out of sight, it resets the .x position.
		if (scrolling.x <= -1301)
		{
			scrolling.x = 1301;
		}
		if (scrolling2.x <= -1301)
		{
			scrolling2.x = 1301;
		}
		if (selbiexd.x < -100)
		{
			selbiexd.x = 650 + rand() % 1000;
		}
	}

	//frees memory on breakpoint of isRunning
	SDL_DestroyWindow(window1);
	SDL_DestroyTexture(character);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(selbie);
	SDL_DestroyRenderer(renderTarget);
	Mix_FreeMusic(emeralds);

	//just precaution
	window1 = nullptr;
	character = nullptr;
	renderTarget = nullptr;
	emeralds = nullptr;

	Mix_Quit();
	SDL_Quit();
	return 0;
}

void createWindow::movement()
{
	SDL_PollEvent(&ev);
	keystate = SDL_GetKeyboardState(NULL);
	
	if (ev.type == SDL_QUIT) 
	{
		isRunning = false;
	}

	if (jumpAllowed)
	{
		if (jumpAllowed)
		{
			if (keystate[SDL_SCANCODE_SPACE])
			{
				number++;
				player.y -= 10;
				if (jumpVal <= 0)
				{
					jumpVal = 5;
				}

				if (number >= 20)
				{
					jumpAllowed = false;
				}
			}
			if (keystate[SDL_SCANCODE_LCTRL])
			{
				player.h = 20;
			}
			else if (!keystate[SDL_SCANCODE_LCTRL])
				player.h = 100;

		}


		//logic
		if (jumpVal > 0)
		{
			if (player.y < 150)
			{
				player.y += 3;
				jumpVal += 1;
			}

		}
		//check gravity regardless of jumping
		if (player.y < 480 - 100)
		{
			player.y += 2;
		}
	}
	/////////////////////////////////////////////

	//checks if the player is on the floor
	if (player.y == 480 - 100)
	{
		//if the player is on the floor we reset the jump function
		jumpAllowed = true;
		number = 0;
	}
	else //if the player is not on the ground, we pull him downwards
	{
		player.y += 1;
	}
	
	//makes sure so the player can't fall through the floor
	if (player.y > 480 - 100)
	{
		player.y = 480 - 100;
	}
}

bool createWindow::collision(SDL_Rect a, SDL_Rect b) 
{
	/* OH WELL THIS SORT OF WORK ._. NEEDS FIRTHER IMPROVMENT GOD DAMNIT */
	
	if (a.x >= b.x && a.x <= (b.x + b.w) || (a.x + a.w) >= b.x && (a.x + a.w) <= (b.x + b.w))
	{
		if (a.y >= b.y && a.y <= (b.y + b.h) || (a.y + a.h) >= b.y && (a.y + a.h) <= (b.y + b.h))
		{
			return false;
		}
		return false;
	}
	return true;
}