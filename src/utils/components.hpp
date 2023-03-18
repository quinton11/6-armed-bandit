#pragma once
#include "SDL.h"
#include "string"
#include "list"

struct Button
{
    std::string name;
    bool isActive;
    bool isSelected;
    SDL_FRect rect;
    SDL_FRect dest;
    SDL_Texture *text;
    SDL_Texture *hovertext;
};

struct Menu
{
    std::string name;
    std::list<Button*> buttons;
    bool active;
    bool set;
};
