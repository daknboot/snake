#ifndef INIT_H
#define INIT_H
#include <SDL2/SDL.h>

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	int width;
	int height;
	int cols;
	int rows;
	int cell_size;
} Game;

typedef enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT } Direction;

typedef struct {
	int length;
	SDL_Rect head;
	SDL_Color color;
	Direction direction;
	SDL_Rect tail[512];
	SDL_bool bot;
} Snake;

int  game_init(Game *game);
void game_cleanup(Game *game);
void start_snake(Game *game, Snake *snake, SDL_Rect *food);
void start_bot(Game *game, Snake *snake, SDL_Rect *food);

#endif
