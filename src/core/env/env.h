#pragma once
#include "SDL.h"
#include "map"
#include "memory"

#include "../../models/agent.h"
#include "../../utils/enums.h"
#include "../../utils/texture.h"
#include "../screens/overlay/overlay.h"
#include "../screens/home/homescreen.h"
#include "../screens/pause/pause.h"
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
    static AutoAgentMode autoMode;
    static AgentMode agentMode;

    std::map<Action, float> actionValues;
    std::map<std::string, SDL_Texture *> textures;

    void run(SDL_Renderer *r);
    void eventChecker();

private:
    bool loaded = false;
    SDL_Color mainTheme = {185, 164, 56}; // color
    Agent *agent;
    EnvState envState = EnvState::Stall;

    SDL_Event events;
    int mx, my = 0;
    int maxSteps = 5;
    int steps = 0;
    int timerValue;
    bool done = false;
    Overlay ol;
    void setConfig(); // takes in level descriptors and configures according to values
                      // depending on demo or custom or best,configure accordingly
    void addTexture(std::string path, std::string nm);
    void update();
    void render(SDL_Renderer *r);
    void renderScoreTab(SDL_Renderer *r);
    void renderEnvState(SDL_Renderer *r);
    void renderHitButtons(SDL_Renderer *r);
};