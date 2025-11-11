#include "init.h"

int game_init(Game *game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "SDL init failed:%s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	game->window = SDL_CreateWindow(
		"2 Player Snake", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, game->width, game->height, 0);

	if (!game->window) {
		fprintf(stderr, "Window create failed: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	game->renderer = SDL_CreateRenderer(game->window, -1,
					    SDL_RENDERER_ACCELERATED |
						    SDL_RENDERER_PRESENTVSYNC);

	if (!game->renderer) {
		fprintf(stderr, "Renderer create failed: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	return 0;
}

void start_snake(Game *game, Snake *snake, SDL_Rect *food)
{
	const int old_head_x = snake->head.x;
	const int old_head_y = snake->head.y;

	if (snake->length > 0) {
		for (int segment = snake->length - 1; segment > 0; segment--) {
			snake->tail[segment] = snake->tail[segment - 1];

			if (snake->head.x == snake->tail[segment].x &&
			    snake->head.y == snake->tail[segment].y) {
				snake->head.x = game->width / 2;
				snake->head.y = game->height / 2;
				snake->length = 0;
			}
		}
		snake->tail[0].x = old_head_x;
		snake->tail[0].y = old_head_y;
	}

	switch (snake->direction) {
	case DIR_UP:
		snake->head.y -= game->cell_size;
		break;
	case DIR_LEFT:
		snake->head.x -= game->cell_size;
		break;
	case DIR_DOWN:
		snake->head.y += game->cell_size;
		break;
	case DIR_RIGHT:
		snake->head.x += game->cell_size;
		break;
	}

	if (snake->head.x < 0 || snake->head.y < 0 ||
	    snake->head.x > game->width - game->cell_size ||
	    snake->head.y > game->height - game->cell_size) {
		snake->head.x = (game->cols / 2) * game->cell_size;
		snake->head.y = (game->rows / 2) * game->cell_size;
		snake->length = 0;
	}

	if (snake->head.x == food->x && snake->head.y == food->y) {
		food->x = rand() % game->cols * game->cell_size;
		food->y = rand() % game->rows * game->cell_size;

		if (snake->length > 0) {
			snake->tail[snake->length] =
				snake->tail[snake->length - 1];
		} else {
			snake->tail[0].x = old_head_x;
			snake->tail[0].y = old_head_y;
		}
		snake->length++;
	}
}

void game_cleanup(Game *game)
{
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
