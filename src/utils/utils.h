#include "SDL.h"
#include "list"
#include "string"

namespace Util
{
    std::pair<SDL_Texture *, SDL_Texture *>
    getTextPairR(SDL_Renderer *r, std::string nm, SDL_FRect &dest);
    SDL_Texture *getBlockText(SDL_Renderer *r, std::string btxt, SDL_FRect &dest);
}