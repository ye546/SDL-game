#pragma once
#include <iostream>
#include "SDL.h"
using namespace std;
class renderTexture
{
public:
	SDL_Texture* loadingTexture(string filepath, SDL_Renderer* renderTarget);
};

