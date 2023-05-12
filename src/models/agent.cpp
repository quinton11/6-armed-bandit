#include "agent.h"

Agent::Agent() {}
Agent::Agent(std::string mName, AgentMode aMode, GameMode gMode)
    : modelName(mName), agentMode(aMode), gameMode(gMode) {}

void Agent::setAgent(AgentMode am, GameMode gm, AutoAgentMode agm)
{
    agentMode = am;
    gameMode = gm;
    autoMode = agm;
}

void Agent::updateScore(float update)
{
    score += update;
}
float Agent::getScore()
{
    return score;
}

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
    actions.clear();
    actions.insert(actions.end(), {
                                      Action::One,
                                      Action::Two,
                                      Action::Three,
                                      Action::Four,
                                      Action::Five,
                                      Action::Six,
                                  });
}

void Agent::refresh(AgentMode am, GameMode gm, AutoAgentMode agm)
{
    setAgent(am, gm, agm);
    setActions();
    resetActionValues();

    if (gm == GameMode::Custom || gm == GameMode::Best)
    {
        // updating model weights
        std::list<float> weights = filemanager::playerWeights[filemanager::currentPlayer];
        std::list<float>::iterator weightsIt;
        int idx = 0;
        for (weightsIt = weights.begin(); weightsIt != weights.end(); weightsIt++)
        {
            if (idx == 0)
            {
                actionValues[Action::One] = *weightsIt;
            }
            else if (idx == 1)
            {
                actionValues[Action::Two] = *weightsIt;
            }
            else if (idx == 2)
            {
                actionValues[Action::Three] = *weightsIt;
            }
            else if (idx == 3)
            {
                actionValues[Action::Four] = *weightsIt;
            }
            else if (idx == 4)
            {
                actionValues[Action::Five] = *weightsIt;
            }
            else if (idx == 5)
            {
                actionValues[Action::Six] = *weightsIt;
            }
            idx += 1;
        }
    }

    // score reset
    score = 0;
}

void Agent::printWeight()
{
    for (std::map<Action, float>::iterator av = actionValues.begin(); av != actionValues.end(); av++)
    {
        if (av->first == Action::One)
        {
            std::cout << "Action one: " << av->second << std::endl;
        }
        else if (av->first == Action::Two)
        {
            std::cout << "Action two: " << av->second << std::endl;
        }
        else if (av->first == Action::Three)
        {
            std::cout << "Action three: " << av->second << std::endl;
        }
        else if (av->first == Action::Four)
        {
            std::cout << "Action four: " << av->second << std::endl;
        }
        else if (av->first == Action::Five)
        {
            std::cout << "Action five: " << av->second << std::endl;
        }
        else if (av->first == Action::Six)
        {
            std::cout << "Action six: " << av->second << std::endl;
        }
    }
}

void Agent::updateWeights(float reward, int steps)
{
    if ((gameMode == GameMode::Custom && autoMode == AutoAgentMode::Testing) || gameMode == GameMode::Best)
        return;

    // if manual mode or custom training mode, update weight
    updateActionValue(reward, steps);
}

void Agent::updateActionValue(float reward, int steps)
{
    // update action timestep
    actionSteps[selectedAction] += 1;

    int ts = actionSteps[selectedAction];
    float prevR = actionValues[selectedAction];

    // std::cout << "Action has been selected x" << ts << std::endl;

    // calculate new estimate for action
    float updated = estimate(reward, prevR, steps);

    // update
    actionValues[selectedAction] = updated;
}

float Agent::estimate(float r, float prevV, float ts)
{
    // action value estimate
    float update = prevV + (1.f / ts) * (r - prevV);

    return update;
}

std::list<float> Agent::getWeights()
{
    std::list<float> weights = {
        actionValues[Action::One],
        actionValues[Action::Two],
        actionValues[Action::Three],
        actionValues[Action::Four],
        actionValues[Action::Five],
        actionValues[Action::Six]};

    return weights;
}

void Agent::trainAct(float steps)
{
    // pseudo epsilon greedy
    /* STEPS
        - Get percent of steps left
        - If value is greater than 40%
        - Explore actions by randomly selecting an action
        - Else select best action agent has explored from its weights
     */
    float maxSteps = 5;
    float percent = steps / maxSteps;

    if (percent >= 0.4)
    {
        // explore action

        int randIndex;

        randIndex = rand() % 6; // random index from six choices

        // set selected action
        std::list<Action>::iterator actit = actions.begin();
        std::advance(actit, randIndex);

        selectedAction = *actit;
        return;
    }

    // loop through weights and select maximum
    std::map<Action, float>::iterator best = std::max_element(actionValues.begin(), actionValues.end(), [](const std::pair<Action, float> &a, const std::pair<Action, float> &b) -> bool
                                                              { return a.second < b.second; });
    selectedAction = best->first;
}
void Agent::testAct()
{
    // gredy policy
    /* STEPS - To test what agent knows, we simply select the best action its learnt
        - Select best action using its learned weights
     */
    std::map<Action, float>::iterator best = std::max_element(actionValues.begin(), actionValues.end(), [](const std::pair<Action, float> &a, const std::pair<Action, float> &b) -> bool
                                                              { return a.second < b.second; });
    selectedAction = best->first;
}

bool Agent::takeAction(const Uint8 *state, float steps)
{

    // check agent mode
    if (gameMode == GameMode::Custom)
    {
        // automatic agent

        // randomly select action
        // if training, randoml
        if (autoMode == AutoAgentMode::Training)
        {
            // pseudo epsilon greedy
            // return true
            trainAct(steps);
        }
        if (autoMode == AutoAgentMode::Testing)
        {
            // greedy policy
            // select action with maximum weight(Best Action)
            testAct();
        }
        acted = true;
        return true;
    }

    if (gameMode == GameMode::Best)
    {
        testAct();
        acted = true;
        return true;
    }

    SDL_PumpEvents();

    if (state[SDL_SCANCODE_A])
    {
        selectedAction = Action::One;
        acted = true;
        // action 1
        return true;
    }
    else if (state[SDL_SCANCODE_B])
    {
        // action 2
        selectedAction = Action::Two;
        acted = true;

        return true;
    }
    else if (state[SDL_SCANCODE_C])
    {
        // action 3
        selectedAction = Action::Three;
        acted = true;

        return true;
    }
    else if (state[SDL_SCANCODE_D])
    {
        // action 4
        selectedAction = Action::Four;
        acted = true;

        return true;
    }
    else if (state[SDL_SCANCODE_E])
    {
        // action 5
        selectedAction = Action::Five;
        acted = true;

        return true;
    }
    else if (state[SDL_SCANCODE_F])
    {
        // action 6
        selectedAction = Action::Six;
        acted = true;

        return true;
    }
    return false;
}
