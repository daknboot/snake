#include "input.h"

void poll_input(Game *game, Snake *player1, Snake *player2)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			game_cleanup(game);
			return;
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				if (player1->direction == DIR_DOWN)
					break;
				player1->direction = DIR_UP;
				break;
			case SDLK_a:
				if (player1->direction == DIR_RIGHT)
					break;
				player1->direction = DIR_LEFT;
				break;
			case SDLK_s:
				if (player1->direction == DIR_UP)
					break;
				player1->direction = DIR_DOWN;
				break;
			case SDLK_d:
				if (player1->direction == DIR_LEFT)
					break;
				player1->direction = DIR_RIGHT;
				break;
			case SDLK_UP:
				if (player2->direction == DIR_DOWN)
					break;
				player2->direction = DIR_UP;
				break;
			case SDLK_LEFT:
				if (player2->direction == DIR_RIGHT)
					break;
				player2->direction = DIR_LEFT;
				break;
			case SDLK_DOWN:
				if (player2->direction == DIR_UP)
					break;
				player2->direction = DIR_DOWN;
				break;
			case SDLK_RIGHT:
				if (player2->direction == DIR_LEFT)
					break;
				player2->direction = DIR_RIGHT;
				break;
			case SDLK_SPACE:
				if (!player1->bot && !player2->bot)
					player2->bot = SDL_TRUE;
				else if (!player1->bot && player2->bot)
					player1->bot = SDL_TRUE;
				else if (player1->bot && player2->bot) {
					player1->bot = SDL_FALSE;
					player2->bot = SDL_FALSE;
				}
				break;
			case SDLK_ESCAPE:
				game_cleanup(game);
				break;
			default:
				break;
			}
		}
	}
}
