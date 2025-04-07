#include "game.h"

Game game;

Uint32* color_buffer;
SDL_Texture* color_buffer_texture;

void clear_color_buffer();
void draw_color_buffer();
void generate_projection();

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
	color_buffer = (Uint32*)malloc(sizeof(Uint32) * WINDOW_WIDTH * WINDOW_HEIGHT);
	if (color_buffer == NULL) { printf("ERROR: failed to allocate space for the color buffer \n"); exit(1); }
	color_buffer_texture = SDL_CreateTexture(game.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

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
	update_player(game.delta_time);


	//cast_ray(player.rotation_angle, 0);
}

void draw()
{
	// Begin drawing
	SDL_SetRenderDrawColor(game.renderer, 0, 0, 200, 255);
	SDL_RenderClear(game.renderer);

	clear_color_buffer(color_buffer);
	cast_all_rays();
	generate_projection(color_buffer);
	draw_color_buffer(color_buffer);

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
	free(color_buffer);
	SDL_DestroyTexture(color_buffer_texture);
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

void clear_color_buffer()
{
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			color_buffer[(WINDOW_WIDTH * y) + x] = 0xFF000000;
		}
	}
}

void draw_color_buffer()
{
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)WINDOW_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(game.renderer, color_buffer_texture, NULL, NULL);
}

void generate_projection()
{
	for (int x = 0; x < NUM_OF_RAYS; x++)
	{
		float distance_to_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projected_wall_height = TILE_SIZE / rays[x].distance * distance_to_projection_plane;

		int wall_top_pixel = (WINDOW_HEIGHT / 2) - (projected_wall_height / 2);
		int wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (projected_wall_height / 2);
		if (wall_top_pixel < 0)
		{
			wall_top_pixel = 0;
		}
		if (wall_bottom_pixel > WINDOW_HEIGHT)
		{
			wall_bottom_pixel = WINDOW_HEIGHT;
		}

		for (int y = 0; y < wall_top_pixel; y++)
		{
			color_buffer[(WINDOW_WIDTH * y) + x] = 0xFF313131;
		}
		for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
		{
			if (rays[x].was_intersection_vertical == true)
			{
				color_buffer[(WINDOW_WIDTH * y) + x] = 0xFFBBBBBB;
			}
			else
			{
				color_buffer[(WINDOW_WIDTH * y) + x] = 0xFFEEEEEE;
			}
		}
		for (int y = wall_bottom_pixel; y < WINDOW_HEIGHT; y++)
		{
			color_buffer[(WINDOW_WIDTH * y) + x] = 0xFFA0A0A0;
		}
	}
}