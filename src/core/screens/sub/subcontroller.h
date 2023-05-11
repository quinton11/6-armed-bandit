#pragma once
#include "SDL.h"
#include "string"
#include "iostream"

#include "../../../utils/utils.h"
#include "../../../utils/components.h"
#include "../../../utils/texture.h"
#include "../../filemanager/filemanager.h"

// controls create player and select player screens
class SubController
{

private:
    std::string activeScreen;
    std::string txtInput;
    int lengthInput;

public:
    SubController();
    ~SubController();

    bool ismounted = false;
    bool revertScreen = false;
    bool setbuttons = false;
    int mx, my;
    SDL_Event events;
    Button backButton;

    void render(SDL_Renderer *r);
    bool mouseinplay(int mx, int my, SDL_FRect r);
    void setButtons(SDL_Renderer *r);
    void renderBackButton(SDL_Renderer *r);
    void eventChecker();
    void inButton(bool clicked);
    void setActiveScreen(std::string activescreen);
    void renderTitle(SDL_Renderer *r, std::string nm);
    void renderInputScreen(SDL_Renderer *r);
    void renderSubScreens(SDL_Renderer *r);
    void renderCreateModel(SDL_Renderer *r);
    void renderSelectModel(SDL_Renderer *r);
};