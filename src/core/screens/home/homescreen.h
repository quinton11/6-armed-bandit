#pragma once
#include "../screen.h"
#include "../menu/menu.h"

class HomeScreen : public Screen
{
public:
    HomeScreen(int w, int h, SDL_Renderer *r);
    ~HomeScreen();
    void eventChecker();
    void render(SDL_Renderer *r);
    void release();
    int width, height;
    static bool ismounted; // set to static
    static bool quit;
    SDL_Event events;
    SDL_Texture *hometxt;
    int mousex, mousey = 0;

private:
    MenuController mc;
};