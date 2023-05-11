#include "game.h"
#include "../screens/home/homescreen.h"
#include "../env/env.h"
#include "../../models/agent.h"
#include "../../utils/utils.h"
#include "../../utils/time.h"
#include "../../utils/texture.h"
#include "iostream"
#include "../filemanager/filemanager.h"

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

    // init file
    filemanager::init();
    // read
    filemanager::readFile();
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
    std::string fontPath = "assets/fonts/";
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
            // update file with scores
            filemanager::writeToFile();
        }
        else
        {

            env.run(graphics->getRenderer());

            SDL_RenderPresent(graphics->getRenderer());
        }
    }
}