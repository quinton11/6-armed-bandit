#include "pause.h"
#include "../home/homescreen.h"

bool PauseScreen::ismounted = false;
bool PauseScreen::terminalStep = false;

PauseScreen::PauseScreen() {}
PauseScreen::~PauseScreen() {}

void PauseScreen::refresh()
{
    terminalStep = false;
}
void PauseScreen::render(SDL_Renderer *r)
{
    while (ismounted)
    {
        // background color
        SDL_SetRenderDrawColor(r, 50, 50, 50, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(r);

        eventChecker();
        drawButtons(r);

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
            inButton(false);
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                // trigger button clicks
                inButton(true);
            }
            break;

        case SDL_KEYDOWN:
            switch (events.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                // exit pause menu if not game over
                ismounted = false;
                std::cout << "Unmounting pause screen" << std::endl;
            }
            break;
        }
    }
    // check for return to game event
    // check for new game event
}

void PauseScreen::drawButtons(SDL_Renderer *r)
{
    // create buttons if not exist
    // add to list of buttons
    // loop through buttons to render them
    // if gameOver, exclude resume button

    int size = buttons.size();
    SDL_FRect midCon;
    midCon.w = 300;
    midCon.h = 150;
    midCon.x = (Graphics::windowWidth / 2) - (midCon.w / 2);
    midCon.y = (Graphics::windowHeight / 2) - (midCon.h / 2);

    if (size == 0)
    {
        // create buttons
        float yoff = midCon.y + 20;
        Button btempr;
        Button btempng;
        Button btempq;
        btempr = createButton(r, "Resume", Graphics::windowWidth, Graphics::windowHeight);
        btempng = createButton(r, "New Game", Graphics::windowWidth, Graphics::windowHeight);
        btempq = createButton(r, "quit", Graphics::windowWidth, Graphics::windowHeight);

        // buttons position
        btempr.dest.x = (midCon.x + midCon.w / 2) - (btempr.dest.w / 2);
        btempr.dest.y = yoff;

        yoff += btempr.dest.h + 5;

        btempng.dest.x = (midCon.x + midCon.w / 2) - (btempng.dest.w / 2);
        btempng.dest.y = yoff;

        yoff += btempng.dest.h + 5;

        btempq.dest.x = (midCon.x + midCon.w / 2) - (btempq.dest.w / 2);
        btempq.dest.y = yoff;

        buttons.push_back(btempr);
        buttons.push_back(btempng);
        buttons.push_back(btempq);
    }

    SDL_SetRenderDrawColor(r, 180, 0, 180, 255);
    SDL_RenderFillRectF(r, &midCon);

    for (std::list<Button>::iterator it = buttons.begin(); it != buttons.end();)
    {
        if (terminalStep)
        {
            if (it->name == "Resume")
            {
                it++;
            }
        }

        if (it->isActive)
        {
            SDL_RenderCopyF(r, it->hovertext, nullptr, &(it->dest));
            it++;
        }
        else
        {
            SDL_RenderCopyF(r, it->text, nullptr, &(it->dest));
            it++;
        }
    }
    SDL_RenderPresent(r);
}

bool PauseScreen::mouse_in_play(int &x, int &y, SDL_FRect &rect)
{
    return (x >= rect.x) && (y >= rect.y) &&
           (x < rect.x + rect.w) && (y < rect.y + rect.h);
}

void PauseScreen::inButton(bool isClicked)
{
    std::list<Button>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); it++)
    {
        it->isActive = false;
        if (mouse_in_play(mx, my, it->dest))
        {
            it->isActive = true;
            if (isClicked)
            {
                // std::cout << it->name << " was clicked" << std::endl;
                if (it->name == "Resume")
                {
                    ismounted = false;
                }
                if (it->name == "quit")
                {
                    ismounted = false;
                    HomeScreen::ismounted = false;
                    HomeScreen::quit = true;
                }
                if (it->name == "New Game")
                {
                    ismounted = false;
                    HomeScreen::ismounted = true;
                }
            }
            return;
        }
    }
}

Button PauseScreen::createButton(SDL_Renderer *r, std::string nm, int sW, int sH)
{
    Button temp = {nm, false, false};
    std::pair<SDL_Texture *, SDL_Texture *> res = Util::getTextPairR(r, nm, temp.dest);
    temp.text = res.first;
    temp.hovertext = res.second;
    return temp;
    // create textures
}
