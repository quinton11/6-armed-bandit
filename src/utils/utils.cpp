#include "SDL.h"
#include "list"
#include "string"
#include "iostream"
#include "utils.hpp"
#include "texture.hpp"
// #include "SDL_ttf.h"

std::pair<SDL_Texture *, SDL_Texture *>
Util::getTextPairR(SDL_Renderer *r, std::string nm, SDL_FRect &dest)
{
    SDL_Surface *surf;
    SDL_Surface *surfh;

    SDL_Texture *txt;
    SDL_Texture *txth;
    std::pair<SDL_Texture *, SDL_Texture *> res;
    std::cout << "Before blended" << std::endl;

    surf = TTF_RenderText_Blended(Texture::getFont(), nm.c_str(), {255, 255, 255});
    std::cout << "After blended" << std::endl;

    txt = SDL_CreateTextureFromSurface(r, surf);
    std::cout << "After texture" << std::endl;
    /* std::cout << surf->w << std::endl;
    std::cout << surf->h << std::endl; */
    //(surf->userdata).w

    /* dest.w = surf->w - 20;
    dest.h = surf->h - 20; */
    // SDL_FreeSurface(surf);

    // hover
    std::cout << "Before hover blended" << std::endl;
    surfh = TTF_RenderText_Blended(Texture::getFont(), nm.c_str(), {0, 255, 0});
    std::cout << "After hover blended" << std::endl;

    txth = SDL_CreateTextureFromSurface(r, surfh);
    std::cout << "After hover texture" << std::endl;

    SDL_FreeSurface(surf);
    SDL_FreeSurface(surfh);
    std::cout << "After freeing hover texture" << std::endl;

    res = std::pair<SDL_Texture *, SDL_Texture *>(txt, txth);
    std::cout << "Now returning" << std::endl;

    return res;

    // surf = TTF_RenderText_Blended(Te)
}