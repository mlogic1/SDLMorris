#include <iostream>

#include <MorrisGame/MorrisGame.h>
#include "SDLWindow.h"

int main(int argc, char* argv[])
{
    /*Morris::MorrisGame* game = new Morris::MorrisGame();
    const std::vector<Morris::MorrisMarkerPtr>& markers = game->GetUnplacedMarkers();
    bool one = game->PlaceMarketAtPoint(0, markers[0]);
    bool move = game->MoveMarkerToPoint(1, markers[0]);
    */

    SDLWindow* morrisWindow = nullptr;
    try
    {
        morrisWindow = new SDLWindow();
    }
    catch (std::string& error)
    {
        std::cout << error << std::endl;
        return -1;
    }

    while (morrisWindow->IsRunning())
    {
        morrisWindow->Update();
    }

    // delete game;
    std::cout << "Hello World!\n";

    delete morrisWindow;
    return 0;
}