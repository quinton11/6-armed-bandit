#include "graphics.hpp"

#include "iostream"

Graphics *Graphics::gInstance = nullptr;
bool Graphics::initialized = false;

Graphics::Graphics()
{
    renderer = nullptr;
    initialized = init();
}
Graphics::~Graphics()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(win);
    renderer = nullptr;
}

Graphics *Graphics::getInstance()
{
    if (gInstance == nullptr)
    {
        gInstance = new Graphics();
    }
    return gInstance;
}

bool Graphics::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "SDL Init Error: " << SDL_GetErrorMsg << std::endl;

        return false;
    }

    win = SDL_CreateWindow(
        "Armed Bandit",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        0);

    if (win == nullptr)
    {
        std::cout << "Window Creation Error: " << SDL_GetErrorMsg << std::endl;
        return false;
    }
    //int succ = TTF_Init();
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf Init error" << std::endl;
    }

    renderer = SDL_CreateRenderer(win, -1, 0);
    return true;
}

void Graphics::release()
{
    delete gInstance;
    gInstance = nullptr;
    initialized = false;
}

bool Graphics::isInitialized()
{
    return initialized;
}

SDL_Renderer *Graphics::getRenderer()
{
    return renderer;
}
