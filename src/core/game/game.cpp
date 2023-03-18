#include "game.hpp"
#include "../screens/home/homescreen.hpp"
#include "../../utils/utils.hpp"
#include "../../utils/time.hpp"
#include "../../utils/texture.hpp"
#include "iostream"

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

    // fonts and textures
    std::string fontPath = "assets/fonts/Starjedi.ttf";
    Texture txtManager = Texture(fontPath);
    //txtManager.initTexture(fontPath);

    std::cout << "After texture init" << std::endl;

    HomeScreen home = HomeScreen(graphics->windowWidth, graphics->windowHeight, graphics->getRenderer());
    std::cout << "After home screen init" << std::endl;

    // deltatime
    float dt;
    Time::initTime();
    while (!isDone)
    {
        dt = Time::getDeltaTime();
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