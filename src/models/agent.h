#pragma once

#include "SDL.h"
#include <iostream>
#include "string"
#include "../core/screens/home/homescreen.h"

#include "../utils/enums.h"
#include "map"
#include "list"

class Agent
{
public:
    Agent();
    Agent(std::string mName, AgentMode aMode, GameMode gMode);
    std::string modelName;
    AgentMode agentMode;
    GameMode gameMode;
    std::list<Action> actions;
    std::map<Action, float> actionValues;
    std::map<Action, int> actionSteps;
    bool takeAction(const Uint8 *state);
    Action selectedAction;
    bool acted = false;
    void resetActionValues();
    void setActions();
    void updateWeights(float reward, int steps);
    void printWeight();
    void setAgent(AgentMode am, GameMode gm);

private:
    SDL_Event events;
    void updateActionValue(float reward, int steps);
    float estimate(float r, float prevR, float ts);
};