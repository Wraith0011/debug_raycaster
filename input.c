#include "input.h"

Input input;

void update_input(SDL_Event* event)
{
	switch (event->type)
	{

		case SDL_KEYDOWN:
			if (event->key.keysym.sym < 0 || event->key.keysym.sym >= NUM_OF_SDL_KEYS)
			{
				break;
			}
			input.keys[event->key.keysym.sym] = true;
			break;
			
		case SDL_KEYUP:
			if (event->key.keysym.sym < 0 || event->key.keysym.sym >= NUM_OF_SDL_KEYS)
			{
				break;
			}
			input.keys[event->key.keysym.sym] = false;
			break;
	}
}