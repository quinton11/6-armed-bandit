#include <iostream>
#include "core/game/game.h"

#undef main

int main()
{
    Game *g = Game::getInstance();

    g->Run();

    // Done
    g->release();
    g = nullptr;

    SDL_Quit();

    return 0;
}