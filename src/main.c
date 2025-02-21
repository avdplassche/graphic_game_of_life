#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "cellular.h"

//500 x 500


void    display_table(t_view *v, SDL_Renderer *renderer)
{
    int i = 0;
    int x;
    int y;
    int x_origin;
	int y_origin;

	x = (WIDTH - TABLE_S) / 2;
    x_origin = x;
	y = (HEIGHT - TABLE_S) / 2;
	y_origin = y;
	printf("x : %d\n y : %d\n", x, y);

    if (v->table[i] == 1)
    {
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_FRect rect = {x, y, v->rect_size, v->rect_size};
        SDL_RenderFillRect(renderer, &rect);
    }
    x += v->rect_size;
    i++;
    while (i <= v->len)
    {
		if (v->table[i] == 1)
        {
			SDL_SetRenderDrawColor(renderer, 0, 100, 127, SDL_ALPHA_OPAQUE);
		    SDL_FRect rect = {x, y, v->rect_size, v->rect_size};
		    SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawColor(renderer,  0, 0, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderRect(renderer, &rect);
        }
        x += v->rect_size;
        i++;
        if (i % v->width == 0)
        {
			x = x_origin;
            y += v->rect_size;
        }
    }
	// SDL_FRect rect = {x_origin, y_origin, TABLE_S, TABLE_S};
	// SDL_RenderFillRect(renderer, &rect);
}



int main(int argc, char* argv[]) {
	float	i = 400;
	float	j = 400;
	int 	k = 0;
	SDL_Surface *screen;
    t_view  v;

    if (!SDL_Init(SDL_INIT_VIDEO))
	{
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 Test", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window)
	{
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
	{
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Target 60 FPS (16.67ms per frame)

    bool running = true;
    int frames = 400;

    v = init_game_of_life(argc, argv);



    while (running)
	{
        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event))
		{
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // while(frames--)
        // {
        update_frame(&v);
        display_table(&v, renderer);
        SDL_RenderPresent(renderer);
        usleep(150 * 1000);
        // }


        // Draw a white rectangle
		// SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		// SDL_FRect rect = {i, j, 20.0f, 20.0f};
		// SDL_RenderFillRect(renderer, &rect);

        // Update screen


        // Frame timing control
    }
    free(v.table);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
