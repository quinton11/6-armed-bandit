#include "SDL.h"
#include "time.hpp"

float currenttime = 0;
float previoustime = 0;
float deltatime = 0;

// Time
float Time::initTime()
{
    previoustime = 0.f;
    currenttime = 0.f;
    deltatime = 0.f;
}

float Time::getDeltaTime()
{
    previoustime = currenttime;
    currenttime = SDL_GetTicks();

    deltatime = currenttime - previoustime;

    return deltatime;
}
