#include "SDL.h"
#include "list"
#include "string"
#include "sstream"

namespace Util
{
    std::pair<SDL_Texture *, SDL_Texture *>
    getTextPairR(SDL_Renderer *r, std::string nm, SDL_FRect &dest);
    std::string toString(int digit);
    SDL_Texture *getTexture(SDL_Renderer *r, std::string txt, SDL_Color col,SDL_FRect &dest,bool isnum);
    SDL_Texture *getBlockText(SDL_Renderer *r, std::string btxt, SDL_FRect &dest);
}