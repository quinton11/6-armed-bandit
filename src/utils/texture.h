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
    static TTF_Font *numfont;

    void initTexture(std::string fname);
    static SDL_Texture *loadTexture(std::string file, SDL_Renderer *r);
    TTF_Font *getFont();
};
