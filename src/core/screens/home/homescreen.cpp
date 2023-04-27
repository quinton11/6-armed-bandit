#include "homescreen.h"
// #include "../../../utils/utils.hpp"
#include <iostream>

bool HomeScreen::ismounted = true;
bool HomeScreen::quit = false;
HomeScreen::HomeScreen(int w, int h, SDL_Renderer *r) : width(w), height(h)
{
    mc = MenuController();
    mc.setMenus(width, height, r);
}

HomeScreen::~HomeScreen() {}

void HomeScreen::render(SDL_Renderer *r)
{
    SDL_RenderClear(r);
    /* Check if subscreen is mounted
    If not run event checker for home screen
    render homescreen current menu
    update renderer */
    while (ismounted)
    {
        SDL_SetRenderDrawColor(r, 185, 164, 56, SDL_ALPHA_OPAQUE);
        eventChecker();
        SDL_RenderClear(r);
        // draw menu on screen
        mc.renderMenu(r);

        SDL_RenderPresent(r);
    }
}

void HomeScreen::eventChecker()
{
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            ismounted = false;
            quit = true;
            // SDL_Quit();
            break;

        case SDL_MOUSEMOTION:
            mousex = events.motion.x;
            mousey = events.motion.y;
            mc.inButton(false, mousex, mousey);
        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                // std::cout << "Mouse click event" << std::endl;
                mc.inButton(true, mousex, mousey);
            }
        }
    }
}

void HomeScreen::release() {}