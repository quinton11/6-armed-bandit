#include "game.hpp"

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
    while (!isDone)
    {
        // Graphics::renderer
        SDL_RenderPresent(graphics->getRenderer());
    }
}