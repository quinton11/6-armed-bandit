#include "subcontroller.h"
#include "../home/homescreen.h"
#include "../../graphics/graphics.h"

SubController::SubController()
{
}
SubController::~SubController() {}

void SubController::render(SDL_Renderer *r)
{
    while (ismounted)
    {

        SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
        eventChecker();

        SDL_RenderClear(r);

        // draw back button
        renderBackButton(r);

        // draw menus, create or select depending on name
        renderSubScreens(r);

        SDL_RenderPresent(r);
    }
}

bool SubController::mouseinplay(int mx, int my, SDL_FRect r)
{
    return (mx >= r.x) && (my >= r.y) &&
           (mx < r.x + r.w) && (my < r.y + r.h);
}

void SubController::renderSubScreens(SDL_Renderer *r)
{
    if (activeScreen == "create")
    {
        renderTitle(r, "Create Model");
        renderCreateModel(r);
    }
    else if (activeScreen == "select")
    {
        // select
        renderTitle(r, "Select Model");
        renderSelectModel(r);
    }
}

void SubController::setButtons(SDL_Renderer *r)
{
    // create buttons
    if (!setbuttons)
    {
        backButton.rect = {20, 20, 0, 0};
        std::pair<SDL_Texture *, SDL_Texture *> txts = Util::getTextPairR(r, "Back", backButton.rect);
        backButton.text = txts.first;
        backButton.hovertext = txts.second;
        setbuttons = true;
    }
}

void SubController::renderTitle(SDL_Renderer *r, std::string nm)
{
    SDL_FRect titleRect = {0, 0, 0, 0};
    SDL_Texture *titleTxt = Util::getTexture(r, nm, {185, 164, 56}, titleRect, false);

    titleRect.x = (Graphics::windowWidth / 2) - (titleRect.w / 2);
    titleRect.y = 40;

    SDL_RenderCopyF(r, titleTxt, nullptr, &titleRect);
    SDL_DestroyTexture(titleTxt);
}

void SubController::renderBackButton(SDL_Renderer *r)
{
    // set position and textures
    setButtons(r);

    if (backButton.isActive)
    {
        // blit hovertext
        SDL_RenderCopyF(r, backButton.hovertext, nullptr, &backButton.rect);
    }
    else
    {
        SDL_RenderCopyF(r, backButton.text, nullptr, &backButton.rect);
    }

    //  blit texture unto rect
}

void SubController::renderInputScreen(SDL_Renderer *r)
{

    SDL_Surface *temps;
    SDL_Texture *intexture;
    SDL_FRect inputContainer = {(Graphics::windowWidth / 2) - 150, 120, 300, 40};
    SDL_FRect inp = {inputContainer.x + 10, inputContainer.y, 0, 0};

    // render fill container
    SDL_SetRenderDrawColor(r, 185, 164, 56, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &inputContainer);
    // render input on container
    temps = TTF_RenderText_Blended(Texture::font, txtInput.c_str(), {0, 0, 0});
    if (temps)
    {
        // std::cout << "Created Successfully" << std::endl;
        intexture = SDL_CreateTextureFromSurface(r, temps);
        inp.w = temps->w;
        inp.h = temps->h;
        SDL_FreeSurface(temps);
        temps = NULL;

        SDL_RenderCopyF(r, intexture, nullptr, &inp);
        SDL_DestroyTexture(intexture);
    }
}

void SubController::eventChecker()
{
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            HomeScreen::quit = true;
            HomeScreen::ismounted = false;
            ismounted = false;

            break;

        case SDL_MOUSEMOTION:
            mx = events.motion.x;
            my = events.motion.y;
            inButton(false);
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                // std::cout << "Mouse click event" << std::endl;
                inButton(true);
            }

            // add case for esc to trigger pause menu
        case SDL_KEYDOWN:
            if (activeScreen == "create")
            {
                switch (events.key.keysym.sym)
                {
                case SDLK_BACKSPACE:
                    // std::cout << "Back Space hit" << std::endl;
                    lengthInput = txtInput.size();
                    ////std::cout << leng << std::endl;

                    if (lengthInput > 0)
                    {
                        txtInput.pop_back();
                    }
                    break;

                case SDLK_RETURN:
                    std::cout << "[Enter] hit" << std::endl;
                    std::cout << txtInput << std::endl;

                    filemanager::createPlayer(txtInput);
                    std::cout << "Created player!" << std::endl;

                    ismounted = false;
                    
                    break;
                }
            }
            else if (activeScreen == "select")
            {
                switch (events.key.keysym.sym)
                {
                case SDLK_RETURN:
                    std::cout << "[Enter] hit" << std::endl;
                    std::cout << "Selected Player: " << selectedPlayer.name << std::endl;
                    ismounted = false;
                }
            }
            break;

        case SDL_TEXTINPUT:
            // std::cout << "Before text input" << std::endl;
            if (activeScreen == "create")
            {
                txtInput += events.text.text;

                // std::cout << "Text Input" << std::endl;
                //  std::cout << textInput << std::endl;
            }
            break;
        }
    }
}

void SubController::inButton(bool clicked)
{
    // loop through buttons
    backButton.isActive = false;
    if (mouseinplay(mx, my, backButton.rect))
    {
        backButton.isActive = true;

        if (clicked)
        {
            ismounted = false;
            revertScreen = true;
        }
    }
    if (activeScreen == "select")
    {
        std::list<Button>::iterator it;
        for (it = playerButtons.begin(); it != playerButtons.end(); it++)
        {
            it->isActive = false;
            if (mouseinplay(mx, my, it->dest))
            {
                it->isActive = true;
                if (clicked)
                {
                    selectedPlayer = *it;
                    playerSelected = true;
                    filemanager::currentPlayer = it->name;
                    filemanager::currentScore = filemanager::playerScores[it->name];
                    break;
                }
            }
        }
    }
}

void SubController::matchPlayerToButtons(SDL_Renderer *r)
{
    // match player to buttons
    // check if length of players list is equal to length of player buttons
    // if not
    if (playerButtons.size() == filemanager::playerScores.size())
    {
        return;
    }

    // sizes are different
    // build buttons
    Button temp;
    std::map<std::string, float>::iterator it;
    std::pair<SDL_Texture *, SDL_Texture *> temppair;
    playerButtons.clear();
    for (it = filemanager::playerScores.begin(); it != filemanager::playerScores.end(); it++)
    {
        temp = Button{it->first, false, false};
        temppair = Util::getTextPairR(r, it->first, temp.dest);
        temp.text = temppair.first;
        temp.hovertext = temppair.second;
        playerButtons.push_back(temp);
    }
}
void SubController::renderPlayers(SDL_Renderer *r)
{
    // render players
    SDL_FRect container = {0, 0, 300, 400};
    container.x = (Graphics::windowWidth / 2) - container.w / 2;
    container.y = 130;

    SDL_SetRenderDrawColor(r, 185, 164, 56, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &container);

    // loop through player buttons and render
    if (playerSelected)
    {
        SDL_SetRenderDrawColor(r, 20, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRectF(r, &(selectedPlayer.dest));
    }

    float yoffset = container.y + 20;
    for (std::list<Button>::iterator it = playerButtons.begin(); it != playerButtons.end(); it++)
    {
        it->rect.w = 180;
        it->rect.h = 20;
        it->rect.x = (container.x + container.w / 2) - (it->rect.w / 2);
        it->rect.y = yoffset;

        it->dest.x = it->rect.x;
        it->dest.y = it->rect.y;

        if (it->isActive)
        {
            SDL_RenderCopyF(r, it->hovertext, nullptr, &(it->dest));
        }
        if (!it->isActive)
        {
            SDL_RenderCopyF(r, it->text, nullptr, &(it->dest));
        }

        yoffset += it->rect.h + 5;
    }
}

void SubController::setActiveScreen(std::string activescreen)
{
    activeScreen = activescreen;
    ismounted = true;
}
void SubController::renderCreateModel(SDL_Renderer *r)
{
    renderInputScreen(r);
}
void SubController::renderSelectModel(SDL_Renderer *r)
{
    matchPlayerToButtons(r);
    renderPlayers(r);
}
