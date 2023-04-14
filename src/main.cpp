#include <iostream>
#include "core/game/game.h"

#undef main

int main()
{
    std::cout
        << "K-armed Bandit" << std::endl;
    Game *g = Game::getInstance();

    g->Run();

    // Done
    g->release();
    g = nullptr;

    SDL_Quit();

    return 0;
}