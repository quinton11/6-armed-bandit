#include "agent.h"

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

bool Agent::takeAction(const Uint8 *state)
{

    SDL_PumpEvents();

    if (state[SDL_SCANCODE_A])
    {
        std::cout << "A" << std::endl;
        // action 1
        return true;
    }
    else if (state[SDL_SCANCODE_S])
    {
        std::cout << "S" << std::endl;
        // action 2
        return true;
    }
    else if (state[SDL_SCANCODE_D])
    {
        std::cout << "D" << std::endl;
        // action 3
        return true;
    }
    else if (state[SDL_SCANCODE_F])
    {
        std::cout << "F" << std::endl;
        // action 4
        return true;
    }
    else if (state[SDL_SCANCODE_G])
    {
        std::cout << "G" << std::endl;
        // action 4
        return true;
    }
    else if (state[SDL_SCANCODE_H])
    {
        std::cout << "H" << std::endl;
        // action 4
        return true;
    }

    /* while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_KEYDOWN:
            std::cout << "Key down" << std::endl;

            if (events.key.keysym.sym == SDLK_a)
            {
                std::cout << "A" << std::endl;
                // action 1
                return true;
            }
            else if (events.key.keysym.sym == SDLK_s)
            {
                std::cout << "S" << std::endl;
                // action 2
                return true;
            }
            else if (events.key.keysym.sym == SDLK_d)
            {
                std::cout << "D" << std::endl;
                // action 3
                return true;
            }
            else if (events.key.keysym.sym == SDLK_f)
            {
                std::cout << "F" << std::endl;
                // action 4
                return true;
            }
            else if (events.key.keysym.sym == SDLK_g)
            {
                std::cout << "G" << std::endl;
                // action 5
                return true;
            }
            else if (events.key.keysym.sym == SDLK_h)
            {
                std::cout << "H" << std::endl;
                // action 6
                return true;
            }

            // add case for esc to trigger pause menu
        }
    } */
    return false;
}
