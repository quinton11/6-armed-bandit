#include "SDL.h"
#include "list"
#include "string"
#include "iostream"
#include "utils.h"
#include "texture.h"
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

    surf = TTF_RenderText_Blended(Texture::font, nm.c_str(), {255, 255, 255});
    if (surf == NULL)
    {
        std::cout << "Error in creating surface" << std::endl;
    }

    std::cout << "After blended" << std::endl;

    txt = SDL_CreateTextureFromSurface(r, surf);
    std::cout << "After texture" << std::endl;
    if (txt == NULL)
    {
        std::cout << "Error in creating texture from surface" << std::endl;
    }
    /* std::cout << surf->w << std::endl;
    std::cout << surf->h << std::endl; */
    //(surf->userdata).w

    dest.w = surf->w - 20;
    dest.h = surf->h - 20;
    // SDL_FreeSurface(surf);

    // hover
    std::cout << "Before hover blended" << std::endl;
    surfh = TTF_RenderText_Blended(Texture::font, nm.c_str(), {0, 255, 0});
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

SDL_Texture *Util::getBlockText(SDL_Renderer *r, std::string btxt, SDL_FRect &dest)
{
    SDL_Surface *s;
    SDL_Texture *t;

    std::cout << "Before creating blended wrapped block" << std::endl;
    s = TTF_RenderUTF8_Blended_Wrapped(Texture::font, btxt.c_str(), {255, 255, 255},0);
    if (s == NULL)
    {
        std::cout << "Error in creating surface" << std::endl;
    }
    std::cout << "After creating blended wrapped block" << std::endl;

    t = SDL_CreateTextureFromSurface(r, s);
    if (r == NULL)
    {
        std::cout << "Error in creating texture from surface" << std::endl;
    }

    /* dest.w = s->w - 10;
    dest.h = s->h - 10; */

    SDL_FreeSurface(s);

    return t;
}
