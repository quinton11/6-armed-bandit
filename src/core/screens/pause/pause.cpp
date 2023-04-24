#include "pause.h"
#include "../home/homescreen.h"

bool PauseScreen::ismounted = false;

PauseScreen::PauseScreen() {}
PauseScreen::~PauseScreen() {}

void PauseScreen::render(SDL_Renderer *r)
{
    while (ismounted)
    {
        // background color
        SDL_SetRenderDrawColor(r, 50, 50, 50, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(r);

        // draw menu
        // resume button
        // new game button
        // quit button
    }
}
void PauseScreen::eventChecker()
{
    // check for quit, mouse motion & press events
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            HomeScreen::quit = true;
            HomeScreen::ismounted = false;
            break;

        case SDL_MOUSEMOTION:
            mx = events.motion.x;
            my = events.motion.y;

        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                // trigger button clicks
            }

        case SDL_KEYDOWN:
            switch (events.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                // exit pause menu if not game over
                ismounted = false;
            }
            break;
        }
    }
    // check for return to game event
    // check for new game event
}

void PauseScreen::drawButtons(SDL_Renderer *r) {}
