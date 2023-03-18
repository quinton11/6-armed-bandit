#include "texture.hpp"
#include "iostream"

//
TTF_Font *font = nullptr;

// textures
void Texture::initTexture(std::string fname)
{
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(flags) && flags))
    {
        std::cout << "SDL_Image could not be initialized, SDL_Image Error: "
                  << IMG_GetError << std::endl;
    }
    std::cout << fname.c_str() << std::endl;
    TTF_Font *sfont = TTF_OpenFont(fname.c_str(), 25);
    if (sfont == NULL)
    {
        std::cout << "Error loading font" << std::endl;
    }
}

SDL_Texture *Texture::loadTexture(std::string file, SDL_Renderer *r)
{
    SDL_Texture *txt = nullptr;
    SDL_Surface *imgSurface = IMG_Load(file.c_str());

    if (imgSurface == NULL)
        std::cout << "Unable to load image "
                  << file.c_str() << " SDL Image ERROR: "
                  << IMG_GetError() << std::endl;
    else
    {
        txt = SDL_CreateTextureFromSurface(r, imgSurface);
        SDL_FreeSurface(imgSurface);
    }
    return txt;
}

TTF_Font *Texture::getFont()
{
    return font;
}
