#include "SDL.h"
#include "list"
#include "string"
//#include "SDL_ttf.h"

namespace Util
{
    std::pair<SDL_Texture *, SDL_Texture *>
    getTextPairR(SDL_Renderer *r, std::string nm, SDL_FRect &dest)
    {
        SDL_Surface *surf;
        SDL_Texture *txt;
        SDL_Texture *txth;
        std::pair<SDL_Texture *, SDL_Texture *> res;

        // surf = TTF_RenderText_Blended(Te)
    }
}