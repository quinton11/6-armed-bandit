#pragma once
#include "SDL.h"

class Screen
{
public:
    Screen();
    Screen(int w, int h);
    ~Screen();

    int width;
    int height;
    bool quit = false;
    bool ismounted = false;

    void render(SDL_Renderer *r);
    void eventChecker();
};