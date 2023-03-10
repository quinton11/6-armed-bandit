#pragma once

#include "string"

#include "../utils/enums.hpp"
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

private:
    void resetActionValues();
    void setActions();
    void updateActionValue(Action a, float reward, int tstep);
    float estimate(float r, float prevR, int ts);
};