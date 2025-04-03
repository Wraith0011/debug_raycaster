#ifndef INPUT_H
#define INPUT_H
#include "global.h"

typedef struct Input
{
	bool keys[NUM_OF_SDL_KEYS];
}Input;
extern Input input;

void update_input(SDL_Event* event);

#endif