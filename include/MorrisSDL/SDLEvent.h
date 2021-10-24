#pragma once

namespace CustomEvents
{
	extern const int SDLEvent_CustomEvent;
	extern const int SDLEvent_CustomEvent2;
}

// how to use
/*SDL_Event ev;
ev.type = userType;

ev.user.data1 = someArg;

SDL_PushEvent(&ev);*/