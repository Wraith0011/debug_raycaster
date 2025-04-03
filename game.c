#include "game.h"

Game game;

int init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("ERROR: failed to initialize SDL \n");
		return 1;
	}
	game.window = SDL_CreateWindow("Raycaster Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (game.window == NULL)
	{
		printf("ERROR: failed to create an SDL window \n");
		return 1;
	}
	game.renderer = SDL_CreateRenderer(game.window, -1, 0);
	if (game.renderer == NULL)
	{
		printf("ERROR: failed to create an SDL renderer \n");
		return 1;
	}

	// Initialize game
	game.prev_frame_time = 0;

	init_player();

	// return 0 on success
	return 0;
}

void perform_timestep()
{
	Uint32 time_to_wait = (Uint32)TARGET_FRAME_TIME - (SDL_GetTicks() - game.prev_frame_time);
	if (time_to_wait > 0 && time_to_wait <= TARGET_FRAME_TIME)
	{
		SDL_Delay(time_to_wait);
	}
	game.delta_time = (SDL_GetTicks() - game.prev_frame_time) / 1000.0f;
	game.prev_frame_time = SDL_GetTicks();
}

void process_events()
{
	// poll events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// handle quit
		if (event.type == SDL_QUIT)
		{
			game.is_running = false;
		}

		// get pressed keys with input manager
		update_input(&event);
	}
}

void update()
{
	cast_all_rays();
	update_player(game.delta_time);
}

void draw()
{
	// Begin drawing
	SDL_SetRenderDrawColor(game.renderer, 0, 0, 200, 255);
	SDL_RenderClear(game.renderer);
	
	draw_minimap(game.renderer);
	draw_rays_on_minimap(game.renderer);
	draw_player_on_minimap(game.renderer);

	SDL_SetRenderDrawColor(game.renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine
	(
		game.renderer,
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR,
		MINIMAP_SCALE_FACTOR * player.x + cos(player.rotation_angle) * 10,
		MINIMAP_SCALE_FACTOR * player.y + sin(player.rotation_angle) * 10
	);

	// End drawing
	SDL_RenderPresent(game.renderer);
}

void shutdown()
{
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
	SDL_Quit();
}


// Game loop
int SDL_main(int argc, char* argv[])
{
	if (init() == 0) { game.is_running = true; }
	else { game.is_running = false; }

	while (game.is_running)
	{
		perform_timestep();
		process_events();
		update();
		draw();
	}

	shutdown();
	return 0;
}