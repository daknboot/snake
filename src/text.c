#include "text.h"
#include <SDL2/SDL_ttf.h>

static TTF_Font *g_font = NULL;

void text_init(void)
{
	if (TTF_Init() == -1) {
		fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
		return;
	}

	g_font = TTF_OpenFont("assets/fonts/F25_Bank_Printer.ttf", 50);
	if (!g_font) {
		fprintf(stderr, "TTF_OpenFont failed: %s\n", TTF_GetError());
		// you *could* TTF_Quit() here, but only if you know you won’t
		// try again
	}
}

void text_write(Game *game, const char *string, SDL_Color color, int x, int y)
{
	if (!g_font) {
		// Fail silently or log once
		fprintf(stderr, "text_write called without a loaded font\n");
		return;
	}

	SDL_Surface *surface = TTF_RenderText_Solid(g_font, string, color);
	if (!surface) {
		fprintf(stderr, "TTF_RenderText_Solid failed: %s\n",
			TTF_GetError());
		return;
	}

	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(game->renderer, surface);
	if (!texture) {
		fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n",
			SDL_GetError());
		SDL_FreeSurface(surface);
		return;
	}

	// Use x, y as the top-left of the text
	SDL_Rect text_box = {.x = x, .y = y, .w = surface->w, .h = surface->h};

	SDL_FreeSurface(surface);

	SDL_RenderCopy(game->renderer, texture, NULL, &text_box);
	SDL_DestroyTexture(texture);
}

void text_write_centered(Game *game, const char *string, SDL_Color fgcolor,
			 SDL_Color bgcolor, int center_x, int center_y)
{
	if (!g_font)
		return;

	SDL_Surface *surface =
		TTF_RenderText_Shaded(g_font, string, fgcolor, bgcolor);
	if (!surface) {
		fprintf(stderr, "TTF_RenderText_Shaded failed: %s\n",
			TTF_GetError());
		return;
	}

	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(game->renderer, surface);
	if (!texture) {
		fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n",
			SDL_GetError());
		SDL_FreeSurface(surface);
		return;
	}

	SDL_Rect dst = {.x = center_x - surface->w / 2,
			.y = center_y - surface->h / 2,
			.w = surface->w,
			.h = surface->h};

	SDL_FreeSurface(surface);

	SDL_RenderCopy(game->renderer, texture, NULL, &dst);
	SDL_DestroyTexture(texture);
}

void text_quit(void)
{
	if (g_font) {
		TTF_CloseFont(g_font);
		g_font = NULL;
	}
	TTF_Quit();
}
