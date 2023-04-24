#include <iostream>
#include "../screen.h"

class PauseScreen : Screen
{
public:
    PauseScreen();
    ~PauseScreen();

    static bool ismounted;
    static int mx, my;
    static SDL_Event events;

    static void render(SDL_Renderer *r);
    void eventChecker();
    void drawButtons(SDL_Renderer *r);
};