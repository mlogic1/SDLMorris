#include "MorrisSDL/SDLEvent.h"
#include <SDL.h>

namespace CustomEvents
{
	const int SDLEvent_CustomEvent = SDL_RegisterEvents(1);
	const int SDLEvent_CustomEvent2 = SDL_RegisterEvents(1);
}
