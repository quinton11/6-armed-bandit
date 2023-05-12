#pragma once

#include "SDL.h"
#include <iostream>
#include "string"
#include "../core/screens/home/homescreen.h"

#include "../utils/enums.h"
#include "map"
#include "list"
#include "algorithm"

class Agent
{
public:
    Agent();
    Agent(std::string mName, AgentMode aMode, GameMode gMode);
    std::string modelName;
    AgentMode agentMode;
    AutoAgentMode autoMode;
    GameMode gameMode;
    std::list<Action> actions;
    std::map<Action, float> actionValues;
    std::map<Action, int> actionSteps;
    bool takeAction(const Uint8 *state, float steps);
    Action selectedAction;
    bool acted = false;
    void resetActionValues();
    void setActions();
    void updateWeights(float reward, int steps);
    void printWeight();
    void trainAct(float steps);
    void testAct();
    void setAgent(AgentMode am, GameMode gm, AutoAgentMode agm);
    void refresh(AgentMode am, GameMode gm, AutoAgentMode agm);
    void updateScore(float update);
    std::list<float> getWeights();
    float getScore();

private:
    SDL_Event events;
    float score;
    void updateActionValue(float reward, int steps);
    float estimate(float r, float prevR, float ts);
};