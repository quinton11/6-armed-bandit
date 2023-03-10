#include "agent.hpp"

Agent::Agent() {}
Agent::Agent(std::string mName, AgentMode aMode, GameMode gMode)
    : modelName(mName), agentMode(aMode), gameMode(gMode) {}

void Agent::resetActionValues()
{
    actionValues.clear();
    actionSteps.clear();

    //
    // actionValues.insert(actionValues.end(), {{Action::One, 0.0}});
    actionValues = {
        {Action::One, 0},
        {Action::Two, 0},
        {Action::Three, 0},
        {Action::Four, 0},
        {Action::Five, 0},
        {Action::Six, 0}};

    actionSteps = {
        {Action::One, 0},
        {Action::Two, 0},
        {Action::Three, 0},
        {Action::Four, 0},
        {Action::Five, 0},
        {Action::Six, 0}};
}
void Agent::setActions()
{
    actions.insert(actions.end(), {
                                      Action::One,
                                      Action::Two,
                                      Action::Three,
                                      Action::Four,
                                      Action::Five,
                                      Action::Six,
                                  });
}

void Agent::updateActionValue(Action a, float reward, int tstep)
{
    // update action timestep
    actionSteps[a] += tstep;

    int ts = actionSteps[a];
    float prevR = actionValues[a];

    // calculate new estimate for action
    float updated = estimate(reward, prevR, ts);

    // update
    actionValues[a] = updated;
}

float Agent::estimate(float r, float prevV, int ts)
{
    // action value estimate
    float update = prevV + (1 / ts) * (r - prevV);

    return update;
}
