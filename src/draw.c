#include "draw.h"

void draw_rect(SDL_Renderer *renderer, SDL_Color color, int x, int y, int width,
	       int height)
{
	SDL_Rect rect = {x, y, width, height};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void draw_grid(SDL_Renderer *renderer, SDL_Color color, int cols, int rows,
	       int height, int width)
{
	const int cell_size = width / cols;
	SDL_Rect gridLine;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for (int col = 0; col <= cols; col++) {
		gridLine.x = col * cell_size;
		gridLine.y = 0;
		gridLine.w = 1;
		gridLine.h = height;
		SDL_RenderFillRect(renderer, &gridLine);
	}

	for (int row = 0; row <= rows; row++) {
		gridLine.x = 0;
		gridLine.y = row * cell_size;
		gridLine.w = width;
		gridLine.h = 1;
		SDL_RenderFillRect(renderer, &gridLine);
	}
}
