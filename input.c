#include "input.h"

Input input;

void update_input(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_KEYDOWN:
			input.keys[event->key.keysym.sym] = true;
			break;
			
		case SDL_KEYUP:
			input.keys[event->key.keysym.sym] = false;
			break;
	}
}