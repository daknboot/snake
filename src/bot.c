#include "bot.h"

SDL_bool collides_with_tail(Snake *snake, int x, int y)
{
	for (int segment = 0; segment < snake->length; segment++) {
		if (x == snake->tail[segment].x && y == snake->tail[segment].y)
			return SDL_TRUE;
	}
	return SDL_FALSE;
}

SDL_Point next_cell(Game *game, Snake *snake, Direction direction)
{
	SDL_Point next = {snake->head.x, snake->head.y};

	switch (direction) {
	case DIR_RIGHT:
		next.x += game->cell_size;
		break;
	case DIR_LEFT:
		next.x -= game->cell_size;
		break;
	case DIR_UP:
		next.y -= game->cell_size;
		break;
	case DIR_DOWN:
		next.y += game->cell_size;
		break;
	}
	return next;
}

SDL_bool bad_move(Game *game, Snake *snake, Direction direction)
{
	SDL_Point next = next_cell(game, snake, direction);
	if (next.x < 0 || next.y < 0 ||
	    next.x > game->width - game->cell_size ||
	    next.y > game->height - game->cell_size)
		return SDL_TRUE;
	return collides_with_tail(snake, next.x, next.y);
}

void start_bot(Game *game, Snake *snake, SDL_Rect *food)
{
	if (!snake->bot)
		return;

	int desired_direction = snake->direction;

	if (food->x > snake->head.x)
		desired_direction = DIR_RIGHT;
	else if (food->x < snake->head.x)
		desired_direction = DIR_LEFT;
	else if (food->y > snake->head.y)
		desired_direction = DIR_DOWN;
	else if (food->y < snake->head.y)
		desired_direction = DIR_UP;

	if (!bad_move(game, snake, desired_direction)) {
		snake->direction = desired_direction;
		return;
	}

	int dirs[4] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};

	for (int dir = 0; dir < 4; dir++) {
		if (!bad_move(game, snake, dirs[dir])) {
			snake->direction = dirs[dir];
			return;
		}
	}
}
