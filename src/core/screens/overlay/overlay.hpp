#pragma once
#include "SDL.h"
#include "../../../utils/components.hpp"
/* Called and passed a value to determine which text to render in its window */
/* By default it should have a fixed width and height, the text field showing the information
and the button to close the overlay */
/* It should be callable from anywhere in the game meaning it should have its own
event checker and rendering loop */
class Overlay
{
public:
    Overlay();
    ~Overlay();

    int mx, my = 0; // mouse positions
    float width = 400;
    float height = 380;
    SDL_Event events;
    SDL_FRect container;
    SDL_FRect titleCon;
    SDL_FRect contentCon;
    Button skip;
    bool ismounted = false;
    bool quit = false;

    void render(SDL_Renderer *r);
    void eventChecker();
    void setOverlay(std::string title);
    void setStructure(int sW, int sH,SDL_Renderer* r);

private:
    OverlayInfo demo;
    OverlayInfo custom;
    OverlayInfo best;
    OverlayInfo *current;
    bool mouseinplay(int mx, int my, SDL_FRect r);
    void skipTrigger(bool isClicked);
};