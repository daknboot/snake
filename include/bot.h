#ifndef BOT_H
#define BOT_H
#include "init.h"

SDL_bool collides_with_tail(Snake *snake, int x, int y);

SDL_Point next_cell(Game *game, Snake *snake, Direction direction);

SDL_bool bad_move(Game *game, Snake *snake, Direction direction);

void start_bot(Game *game, Snake *snake, SDL_Rect *food);

#endif
