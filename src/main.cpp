#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "MorrisGame/MorrisGame.h"

int main(int argc, char* argv[])
{
    Morris::MorrisGame* game = new Morris::MorrisGame();
    const std::vector<Morris::MorrisMarkerPtr>& markers = game->GetUnplacedMarkers();
    bool one = game->PlaceMarketAtPoint(0, markers[0]);
    bool move = game->MoveMarkerToPoint(1, markers[0]);

    delete game;
    std::cout << "Hello World!\n";
    return 0;
}