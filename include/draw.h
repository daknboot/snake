#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>

void draw_rect(SDL_Renderer *renderer, SDL_Color color, int x, int y, int width,
	       int height);

void draw_grid(SDL_Renderer *renderer, SDL_Color color, int cols, int rows,
	       int height, int width);

#endif
