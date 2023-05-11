#include "texture.h"
#include "iostream"

//
TTF_Font *Texture::font = nullptr;
TTF_Font *Texture::numfont = nullptr;

Texture::Texture() {}
Texture::Texture(std::string fname)
{
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(flags) && flags))
    {
        std::cout << "SDL_Image could not be initialized, SDL_Image Error: "
                  << IMG_GetError << std::endl;
    }

    font = TTF_OpenFont((fname + "AwmuDemo-YzPML.ttf").c_str(), 25);
    numfont = TTF_OpenFont((fname + "Starjedi.ttf").c_str(), 25);
    if (font == NULL)
    {
        std::cout << "Error loading font" << TTF_GetError() << std::endl;
    }
    if (numfont == NULL)
    {
        std::cout << "Error loading num font" << TTF_GetError() << std::endl;
    }
}

Texture::~Texture() {}
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
    font = TTF_OpenFont(fname.c_str(), 35);
    if (font == NULL)
    {
        std::cout << "Error loading font" << TTF_GetError() << std::endl;
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
