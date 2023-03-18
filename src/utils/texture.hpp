#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "string"

// extern TTF_Font *font;
class Texture
{
    // TTF_Font *font;
public:
    Texture();
    Texture(std::string fname);
    ~Texture();

    static TTF_Font *font;

    void initTexture(std::string fname);
    SDL_Texture *loadTexture(std::string file, SDL_Renderer *r);
    TTF_Font *getFont();
};
