#include "game.hpp"
#include "../screens/home/homescreen.hpp"

Game *Game::instance = nullptr;
Graphics *Game::graphics = nullptr;

Game::Game()
{
    isDone = false;

    graphics = Graphics::getInstance();
    if (!Graphics::isInitialized())
    {
        isDone = true;
    }
}
Game::~Game()
{
    Graphics::release();
    graphics = nullptr;
}

Game *Game::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Game();
    }
    return instance;
}

void Game::release()
{
    delete instance;
    instance = nullptr;
}

void Game::Run()
{
    HomeScreen home = HomeScreen(graphics->windowWidth, graphics->windowHeight);
    while (!isDone)
    {
        if (home.ismounted)
        {
            home.render(graphics->getRenderer());
        }
        else if (!home.ismounted && home.quit)
        {
            isDone = true;
        }
        SDL_RenderPresent(graphics->getRenderer());
    }
}