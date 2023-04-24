#pragma once
#include "SDL.h"
#include "map"

#include "../../models/agent.h"
#include "../../utils/enums.h"
#include "../screens/overlay/overlay.h"
#include "../screens/home/homescreen.h"
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
    std::map<Action, float> actionValues;

private:
    Agent *agent;
    EnvState envState = EnvState::Stall;
    void setConfig(); // takes in level descriptors and configures according to values
                      // depending on demo or custom or best,configure accordingly
    void update();
    SDL_Event events;
    int mx, my = 0;
    int maxSteps = 5;
    void render(SDL_Renderer *r);
    bool done = false;
    Overlay ol;
};