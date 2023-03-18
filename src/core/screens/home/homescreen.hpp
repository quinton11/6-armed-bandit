#pragma once
#include "../screen.hpp"
#include "../menu/menu.hpp"

class HomeScreen : public Screen
{
public:
    HomeScreen(int w, int h,SDL_Renderer *r);
    ~HomeScreen();
    void eventChecker();
    void render(SDL_Renderer *r);
    void release();
    int width, height;
    bool ismounted = true;
    bool quit = false;
    SDL_Event events;
    int mousex, mousey = 0;

private:
    MenuController mc;
};