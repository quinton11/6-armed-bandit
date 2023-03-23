#include "env.hpp"
#include "../../utils/time.hpp"

GameMode Env::gMode = GameMode::Demo;
Env::Env() {}
Env::~Env() {}

Env::Env(Agent *ag) : agent(ag)
{
}

void Env::setConfig() {}
void Env::update() {}
void Env::render(SDL_Renderer *r) {}
void Env::init(int sW, int sH, SDL_Renderer *r)
{
   /*  ol = Overlay();
    ol.setStructure(sW, sH, r); */
}

void Env::run(SDL_Renderer *r)
{
    float dt;
    /* ol.ismounted = true;
    ol.render(r); */
    while (!done)
    {
        dt = Time::getDeltaTime();
        // run agent env loop

        /* Steps:
            - Query user for action
            - User chooses action
            - action is performed //animate bandit pressing button?
            - agent receives reward from taking action
            - agent updates its weights or action value estimates(it learns)
            - update environment states
            -render values */

        /* Env states for now include time steps taken and time steps left
            Agent score
            Each action taken subtracts from time step
            If env action state is (receive action) then actions from agent are read
            If env action state is (stall) then agent cannot input any action
            Set env action state based on countdowns, after 2 seconds state changes from stall
            to receive. After action is pressed, action is taken and state changed from receive to stall */
        if (envState == EnvState::Receive)
        {
            // text overlay
            //  run agent event checker
            //  check if action has been taken
            //  if so set envState to stall
            //  agent update action value estimate with reward
        }
        // update env state values
        update();
        // render
        render(r);

        /*
            We can check for a particular state. if receive, then run agent event checker and overlay
            text to prompt agent for action
            If stall don't run agent event checker, run normal render update functions and await countdown
             */
    }
}