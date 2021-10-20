#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "MorrisGame/MorrisGame.h"

int main(int argc, char* argv[])
{
    Morris::MorrisGame* game = new Morris::MorrisGame();

    delete game;
    std::cout << "Hello World!\n";
    return 0;
}