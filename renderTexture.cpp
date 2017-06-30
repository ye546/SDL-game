#include "renderTexture.h"
#include "SDL_image.h"
#include "SDL.h"
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

SDL_Texture *renderTexture::loadingTexture(string filepath, SDL_Renderer* renderTarget)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filepath.c_str());
	if (surface == nullptr) {
		printf("error1 %s", SDL_GetError());
	}
	else{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == nullptr) {
			printf("error2 %s", SDL_GetError());
		}	
	}
	SDL_FreeSurface(surface);
	return texture;
}

