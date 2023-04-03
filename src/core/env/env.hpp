#pragma once
#include "SDL.h"
#include "../../models/agent.hpp"
#include "../../utils/enums.hpp"
#include "../screens/overlay/overlay.hpp"
/* This simulates the actual game
Here, the agent receives a "state" from
the environment, produces an action which then gives
the agent a reward and updates the state */
class Env
{
public:
    Env();
    ~Env();

    Env(Agent *ag);
    static GameMode gMode;
    void run(SDL_Renderer *r);
    void eventChecker();

private:
    Agent *agent;
    EnvState envState = EnvState::Stall;
    void setConfig(); // takes in level descriptors and configures according to values
                      // depending on demo or custom or best,configure accordingly
    void update();
    SDL_Event events;
    int mx,my=0;
    void render(SDL_Renderer *r);
    bool done = false;
    Overlay ol;
};