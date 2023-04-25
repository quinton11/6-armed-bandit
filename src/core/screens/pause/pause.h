#include <iostream>
#include "../screen.h"
#include "list"
#include "../../../utils/components.h"
#include "../../../utils/utils.h"
#include "../../graphics/graphics.h"

class PauseScreen : Screen
{
public:
    PauseScreen();
    ~PauseScreen();

    static bool ismounted;
    static bool terminalStep;
    int mx, my;
    SDL_Event events;
    std::list<Button> buttons;

    void render(SDL_Renderer *r);
    void refresh();
    void eventChecker();
    void drawButtons(SDL_Renderer *r);
    bool mouse_in_play(int &x, int &y, SDL_FRect &rect);
    void inButton(bool isClicked);
    Button createButton(SDL_Renderer *r, std::string nm, int sW, int sH);
};