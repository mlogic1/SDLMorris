#include <iostream>

#include <MorrisGame/MorrisGame.h>
#include "SDLWindow.h"

int main(int argc, char* argv[])
{
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

    delete morrisWindow;
    return 0;
}