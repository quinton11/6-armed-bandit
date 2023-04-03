#include "game.hpp"
#include "../screens/home/homescreen.hpp"
#include "../env/env.hpp"
#include "../../models/agent.hpp"
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
    std::string fontPath = "assets/fonts/AwmuDemo-YzPML.otf";
    Texture txtManager = Texture(fontPath);
    // txtManager.initTexture(fontPath);

    std::cout << "After texture init" << std::endl;

    HomeScreen home = HomeScreen(graphics->windowWidth, graphics->windowHeight, graphics->getRenderer());
    std::cout << "After home screen init" << std::endl;

    // deltatime
    float dt;
    Time::initTime();
    Agent ag = Agent();
    Env env = Env(&ag);
    while (!isDone)
    {
        dt = Time::getDeltaTime();
        if (HomeScreen::ismounted)
        {
            home.render(graphics->getRenderer());
        }
        else if (!HomeScreen::ismounted && HomeScreen::quit)
        {
            isDone = true;
        }
        else
        {

            env.run(graphics->getRenderer());

            SDL_RenderPresent(graphics->getRenderer());
        }
    }
}