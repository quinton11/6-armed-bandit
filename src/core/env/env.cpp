#include "env.h"
#include "../../utils/time.h"
#include "../screens/home/homescreen.h"

#include <iostream>

GameMode Env::gMode = GameMode::Demo;
Env::Env() {}
Env::~Env() {}

Env::Env(Agent *ag) : agent(ag)
{
    actionValues = {
        {Action::One, 1},
        {Action::Two, 5},
        {Action::Three, -3},
        {Action::Four, -5},
        {Action::Five, 8},
        {Action::Six, -6},
    };
}

void Env::setConfig() {}
void Env::update() {}
void Env::render(SDL_Renderer *r)
{
    SDL_RenderClear(r);
    SDL_RenderPresent(r);
}

void Env::eventChecker()
{
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            HomeScreen::quit = true;
            HomeScreen::ismounted = false;
            done = true;

            break;

        case SDL_MOUSEMOTION:
            mx = events.motion.x;
            my = events.motion.y;

        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                // std::cout << "Mouse click event" << std::endl;

                // mc.inButton(true, mousex, mousey);
            }

            // add case for esc to trigger pause menu
        }
    }
}

void Env::run(SDL_Renderer *r)
{
    float dt;
    done = false;

    // agent refresh
    agent->setActions();
    agent->resetActionValues();

    // start initial countdown
    unsigned int tm = SDL_GetTicks();
    EnvState envState = EnvState::Stall;
    int timerValue = 3;
    int steps = 5;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    while (!done)
    {
        if (steps < 1)
        {
            done = true;
            HomeScreen::ismounted = true;
            // instead mount pause screen
        }
        dt = Time::getDeltaTime();

        eventChecker();
        // run agent env loop

        // timer
        if ((tm % 1000 == 0) && (timerValue > 0))
        {
            std::cout << "Countdown: " << timerValue << " Seconds" << std::endl;
            timerValue -= 1;
        }

        // change env state to receive action
        if ((timerValue == 0) && (envState == EnvState::Stall))
        {
            std::cout << "Moving to receive state" << std::endl;
            envState = EnvState::Receive;
        }

        if (envState == EnvState::Receive)
        {

            // text overlay
            //  run agent event checker
            //  check if action has been taken
            //  if so set envState to stall
            //  agent update action value estimate with reward
            // user perform action
            // run agent eventChecker
            bool act = agent->takeAction(state);
            if (act)
            {
                std::cout << "Agent taken action on step: " << steps << std::endl;
                // User took action
                // set envstate to stall
                // set timerValue to 3
                envState = EnvState::Stall;
                timerValue = 3;

                // agent update weight using current selected action
                float reward = actionValues[agent->selectedAction];
                std::cout << "Reward: " << reward << std::endl;
                // update env states, number of steps left, agent score
                agent->updateWeights(reward,maxSteps);

                // agent weight map
                agent->printWeight();

                // update step count
                steps -= 1;
                std::cout << "Entering Stall State" << std::endl;
            }
        }

        /* Steps:
            - Query user for action
            - User chooses action
            - action is performed //animate bandit pressing button?
            - agent receives reward from taking action
            - agent updates its weights or action value estimates(it learns)
            - update environment states
            -render values */

        /* Environment, agent boundary? Where agent's arbitrary control basically ends.
        What can the agent directly control? */

        /* Env states for now include time steps taken and time steps left
            Agent score
            Each action taken subtracts from time step
            If env action state is (receive action) then actions from agent are read
            If env action state is (stall) then agent cannot input any action
            Set env action state based on countdowns, after 2 seconds state changes from stall
            to receive. After action is pressed, action is taken and state changed from receive to stall */
        // update env state values
        update();
        // render
        render(r);

        /*
            We can check for a particular state. if receive, then run agent event checker and overlay
            text to prompt agent for action
            If stall don't run agent event checker, run normal render update functions and await countdown
             */
        tm = SDL_GetTicks();
    }
}