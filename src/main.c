#include "draw.h"
#include "init.h"
#include "input.h"
#include "text.h"

int main(int argc, char **argv)
{
	int max_score = 10;
	float game_speed_mult = 1.0;
	Game game = {.window = NULL,
		     .renderer = NULL,
		     .width = 1600,
		     .height = 900,
		     .cols = 32,
		     .rows = 18,
		     .cell_size = game.width / game.cols};

	if (argc > 1) {
		if (strcmp(argv[1], "--help") || strcmp(argv[1], "-h")) {
			printf("Usage: ./snake [max_score] "
			       "[resolution_multiplier] [speed_multiplier]\n");
			printf("Press [SPACE] for 2 bots, press again for no "
			       "bots, press again for 1 bot");
			return 0;
		}
		max_score = atoi(argv[1]);
		if (argc > 2) {
			game.cols *= atoi(argv[2]);
			game.rows *= atoi(argv[2]);
		}

		if (argc > 3) {
			game_speed_mult = atof(argv[3]);
		}
	}

	if (game_init(&game)) {
		game_cleanup(&game);
		exit(1);
	}

	int game_speed_ms = 100 * game_speed_mult;
	srand(SDL_GetTicks());
	text_init();

	SDL_Color white = {255, 255, 255, 255};
	SDL_Color black = {25, 25, 25, 255};
	SDL_Color red = {255, 25, 25, 255};
	SDL_Color green = {25, 255, 25, 255};
	SDL_Color blue = {25, 25, 255, 255};

	Snake player1 = {.length = 0,
			 .head.x = (game.cols / 2) * game.cell_size,
			 .head.y = (game.rows / 2) * game.cell_size,
			 .color = green,
			 .direction = DIR_LEFT};

	Snake player2 = {.length = 0,
			 .head.x = (game.cols / 2) * game.cell_size,
			 .head.y = (game.rows / 2) * game.cell_size,
			 .color = blue,
			 .direction = DIR_RIGHT,
			 .bot = SDL_TRUE};

	SDL_Rect food = {.x = rand() % game.cols * game.cell_size,
			 .y = rand() % game.rows * game.cell_size,
			 .h = game.cell_size,
			 .w = game.cell_size};

	draw_rect(game.renderer, red, food.x, food.y, game.cell_size,
		  game.cell_size);

	//			vvv rendering vvv

	while (game.window && game.renderer) {
		poll_input(&game, &player1, &player2);
		start_snake(&game, &player1, &food);
		start_snake(&game, &player2, &food);
		start_bot(&game, &player2, &food);
		start_bot(&game, &player1, &food);

		SDL_SetRenderDrawColor(game.renderer, black.r, black.g, black.b,
				       black.a);
		SDL_RenderClear(game.renderer);

		draw_rect(game.renderer, red, food.x, food.y, game.cell_size,
			  game.cell_size);
		draw_rect(game.renderer, green, player1.head.x, player1.head.y,
			  game.cell_size, game.cell_size);
		draw_rect(game.renderer, player2.color, player2.head.x,
			  player2.head.y, game.cell_size, game.cell_size);

		for (int segment = 0; segment < player1.length; segment++)
			draw_rect(game.renderer, player1.color,
				  player1.tail[segment].x,
				  player1.tail[segment].y, game.cell_size,
				  game.cell_size);
		for (int segment = 0; segment < player2.length; segment++)
			draw_rect(game.renderer, player2.color,
				  player2.tail[segment].x,
				  player2.tail[segment].y, game.cell_size,
				  game.cell_size);

		draw_grid(game.renderer, white, game.cols, game.rows,
			  game.height, game.width);

		if (player1.length == max_score) {
			draw_rect(game.renderer, black, 0, 0, game.width,
				  game.height);
			char winner[32];
			snprintf(winner, sizeof(winner), "Player 1 wins!");
			text_write_centered(&game, winner, player1.color, black,
					    game.width / 2, game.height / 2);
			SDL_RenderPresent(game.renderer);
			SDL_Delay(5000);
			game_cleanup(&game);
			text_quit();
			exit(EXIT_SUCCESS);
		}

		if (player2.length == max_score) {
			draw_rect(game.renderer, black, 0, 0, game.width,
				  game.height);
			char winner[32];
			snprintf(winner, sizeof(winner), "Player 2 wins!");
			text_write_centered(&game, winner, player2.color, black,
					    game.width / 2, game.height / 2);
			SDL_RenderPresent(game.renderer);
			SDL_Delay(5000);
			game_cleanup(&game);
			text_quit();
			exit(EXIT_SUCCESS);
		}

		char player1score[32];
		snprintf(player1score, sizeof(player1score), "%d",
			 player1.length);

		char player2score[32];
		snprintf(player2score, sizeof(player2score), "%d",
			 player2.length);

		text_write_centered(&game, player1score, green, black,
				    game.width / 4, 1.5 * game.cell_size);

		text_write_centered(&game, player2score, blue, black,
				    game.width / 4 * 3, 1.5 * game.cell_size);

		SDL_RenderPresent(game.renderer);
		SDL_Delay(game_speed_ms);
	}

	//			^^^ rendering ^^^
	text_quit();
	game_cleanup(&game);
	return 0;
}
