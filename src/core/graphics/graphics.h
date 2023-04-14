#pragma once

#include "SDL.h"
#include "SDL_ttf.h"


class Graphics
{
public:
    Graphics();
    ~Graphics();

    static const int windowWidth = 800;
    static const int windowHeight = 600;
    static Graphics *getInstance();
    static bool isInitialized();
    static void release();
    SDL_Renderer *getRenderer();

private:
    SDL_Renderer *renderer;
    SDL_Window *win;

    static Graphics *gInstance;
    static bool initialized;
    bool init();
};