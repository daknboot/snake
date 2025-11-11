#ifndef TEXT_H
#define TEXT_H

#include "init.h"

void text_init(void);

void text_write(Game *game, const char *string, SDL_Color color, int x, int y);

void text_write_centered(Game *game, const char *string, SDL_Color fgcolor,
			 SDL_Color bgcolor, int center_x, int center_y);

void text_quit(void);

#endif
