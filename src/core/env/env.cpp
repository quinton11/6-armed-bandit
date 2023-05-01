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

    std::string assetsPath = "assets/textures/";

    // load relevant textures
    addTexture(assetsPath + "statsbar.png", "statsbar");

    // armed Bandit text
    addTexture(assetsPath + "armedBandit.png", "armedBandit");

    // A
    addTexture(assetsPath + "hitA.png", "hitA");
    addTexture(assetsPath + "unhitA.png", "unhitA");

    // B
    addTexture(assetsPath + "hitB.png", "hitB");
    addTexture(assetsPath + "unhitB.png", "unhitB");

    // C
    addTexture(assetsPath + "hitC.png", "hitC");
    addTexture(assetsPath + "unhitC.png", "unhitC");

    // D
    addTexture(assetsPath + "hitD.png", "hitD");
    addTexture(assetsPath + "unhitD.png", "unhitD");

    // E
    addTexture(assetsPath + "hitE.png", "hitE");
    addTexture(assetsPath + "unhitE.png", "unhitE");

    // F
    addTexture(assetsPath + "hitF.png", "hitF");
    addTexture(assetsPath + "unhitF.png", "unhitF");
}

void Env::addTexture(std::string path, std::string nm)
{
    textures.insert(std::pair<std::string, SDL_Texture *>(nm, Texture::loadTexture(path, Graphics::getInstance()->getRenderer())));
}

void Env::setConfig() {}
void Env::update() {}
void Env::render(SDL_Renderer *r)
{
    SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(r);

    // render hit buttons
    // render bandit rect

    renderScoreTab(r);

    renderEnvState(r);

    // render hit buttons and bandit
    renderHitButtons(r);

    SDL_RenderPresent(r);
}

void Env::renderHitButtons(SDL_Renderer *r)
{

    // render all six buttons
    float buttonW = 70;
    float buttonH = 70;
    float ydisplace = Graphics::windowHeight / 2 - 60;
    float xdisplace = 30;

    SDL_SetRenderDrawColor(r, mainTheme.r, mainTheme.g, mainTheme.b, mainTheme.a);

    // button A
    SDL_FRect buttonA = {100, ydisplace, buttonW, buttonH};

    // A texture
    // if acted and action is A
    if (agent->acted && agent->selectedAction == Action::One)
    {
        SDL_RenderCopyF(r, textures["hitA"], nullptr, &buttonA);
    }
    else
    {
        SDL_RenderCopyF(r, textures["unhitA"], nullptr, &buttonA);
    }
    // button B
    SDL_FRect buttonB = {buttonA.x + buttonA.w + xdisplace, ydisplace, buttonW, buttonH};
    // B texture

    if (agent->acted && agent->selectedAction == Action::Two)
    {
        SDL_RenderCopyF(r, textures["hitB"], nullptr, &buttonB);
    }
    else
    {
        SDL_RenderCopyF(r, textures["unhitB"], nullptr, &buttonB);
    }
    // button C
    SDL_FRect buttonC = {buttonB.x + buttonB.w + xdisplace, ydisplace, buttonW, buttonH};
    // C texture

    if (agent->acted && agent->selectedAction == Action::Three)
    {
        SDL_RenderCopyF(r, textures["hitC"], nullptr, &buttonC);
    }
    else
    {
        SDL_RenderCopyF(r, textures["unhitC"], nullptr, &buttonC);
    }

    // button D
    SDL_FRect buttonD = {buttonC.x + buttonC.w + xdisplace, ydisplace, buttonW, buttonH};
    // D texture

    if (agent->acted && agent->selectedAction == Action::Four)
    {
        SDL_RenderCopyF(r, textures["hitD"], nullptr, &buttonD);
    }
    else
    {
        SDL_RenderCopyF(r, textures["unhitD"], nullptr, &buttonD);
    }

    // button E
    SDL_FRect buttonE = {buttonD.x + buttonD.w + xdisplace, ydisplace, buttonW, buttonH};
    // E texture

    if (agent->acted && agent->selectedAction == Action::Five)
    {
        SDL_RenderCopyF(r, textures["hitE"], nullptr, &buttonE);
    }
    else
    {
        SDL_RenderCopyF(r, textures["unhitE"], nullptr, &buttonE);
    }

    // button F
    SDL_FRect buttonF = {buttonE.x + buttonE.w + xdisplace, ydisplace, buttonW, buttonH};
    // F texture

    if (agent->acted && agent->selectedAction == Action::Six)
    {
        SDL_RenderCopyF(r, textures["hitF"], nullptr, &buttonF);
    }
    else
    {
        SDL_RenderCopyF(r, textures["unhitF"], nullptr, &buttonF);
    }

    // armed bandit
    SDL_FRect armedB;
    armedB.x = 10;
    armedB.y = Graphics::windowHeight - 30;
    armedB.w = 100;
    armedB.h = 20;

    SDL_RenderCopyF(r, textures["armedBandit"], nullptr, &armedB);
}

void Env::renderEnvState(SDL_Renderer *r)
{
    // create HIT! and Stall state texts
    float ydisplace = 100;
    if (envState == EnvState::Stall)
    {
        // render countdown
        SDL_FRect countdownRect = {50, ydisplace, 0, 0};
        // create countdown rect
        std::string countdownTxt = Util::toString(timerValue);
        // create countdown texture
        SDL_Texture *countdownTexture = Util::getTexture(r, countdownTxt, mainTheme, countdownRect, true);
        // render texture
        SDL_RenderCopyF(r, countdownTexture, nullptr, &countdownRect);
        SDL_DestroyTexture(countdownTexture);
    }
    else if (envState == EnvState::Receive)
    {
        //  render HIT!
        SDL_FRect hitRect = {Graphics::windowWidth - 150, ydisplace, 0, 0};
        // create HIT rect
        std::string hitTxt = "HIT!";
        // create HIT texture
        SDL_Texture *hitTexture = Util::getTexture(r, hitTxt, mainTheme, hitRect, false);
        // render texture
        SDL_RenderCopyF(r, hitTexture, nullptr, &hitRect);
        SDL_DestroyTexture(hitTexture);
    }
}

void Env::renderScoreTab(SDL_Renderer *r)
{
    // render Tab container
    SDL_FRect container;
    container.x = 0;
    container.y = 0;
    container.h = 80;
    container.w = Graphics::windowWidth;

    SDL_RenderCopyF(r, textures["statsbar"], nullptr, &container);

    // create rendertab textures and blit onto screen
    // textures with their texts

    float xdisplace = 20;
    // steps
    SDL_FRect stepRect;
    stepRect.x = container.x + 30;
    stepRect.y = container.y + 15;
    std::string stepText = "Steps";
    SDL_Texture *stepTexture = Util::getTexture(r, stepText, {0, 0, 0}, stepRect, false);

    SDL_FRect stepValRect;
    stepValRect.x = stepRect.x + 10 + stepRect.w;
    stepValRect.y = container.y + 15;

    std::string stepVal = ": " + Util::toString(steps) + "/" + Util::toString(maxSteps);
    SDL_Texture *stepValTexture = Util::getTexture(r, stepVal, {0, 0, 0}, stepValRect, true);

    // divider
    SDL_FRect divider = {stepValRect.x + stepValRect.w + xdisplace, 5, 2, 70};

    // agent mode
    SDL_FRect agentModeRect;
    agentModeRect.x = divider.x + divider.w + xdisplace;
    agentModeRect.y = container.y + 15;
    std::string agmode = "Auto";
    if (agent->agentMode == AgentMode::Manual)
        agmode = "Manual";

    std::string agentModeTxt = "Agent: " + agmode;
    SDL_Texture *agentModeTexture = Util::getTexture(r, agentModeTxt, {0, 0, 0}, agentModeRect, false);

    // divider
    SDL_FRect dividerAg = {agentModeRect.x + agentModeRect.w + xdisplace, 5, 2, 70};

    // env mode
    SDL_FRect envModeRect;
    envModeRect.x = dividerAg.x + dividerAg.w + xdisplace;
    envModeRect.y = container.y + 15;
    std::string egmode = "Demo";
    if (gMode == GameMode::Best)
    {
        egmode = "Best";
    }
    else if (gMode == GameMode::Custom)
    {
        egmode = "Custom";
    }
    std::string gameModeTxt = "Game: " + egmode;
    SDL_Texture *gameModeTexture = Util::getTexture(r, gameModeTxt, {0, 0, 0}, envModeRect, false);

    // score

    // divider
    SDL_FRect dividerSc = {envModeRect.x + envModeRect.w + xdisplace, 5, 2, 70};

    SDL_FRect scoreValRect;
    scoreValRect.x = dividerSc.x + dividerSc.w + xdisplace;
    scoreValRect.y = container.y + 15;

    std::string scoreVal = "Score";
    SDL_Texture *scoreValTexture = Util::getTexture(r, scoreVal, {0, 0, 0}, scoreValRect, false);

    // load static textures once
    if (!loaded)
    {
        std::string stepText = "Steps";
        // SDL_Texture *stepTexture = Util::getTexture(r, stepText, {0, 0, 0}, stepRect, false);
        textures.insert(std::pair<std::string, SDL_Texture *>(stepText, Util::getTexture(r, stepText, {0, 0, 0}, stepRect, false)));

        std::string scoreVal = "Score";
        // SDL_Texture *scoreValTexture = Util::getTexture(r, scoreVal, {0, 0, 0}, scoreValRect, false);
        textures.insert(std::pair<std::string, SDL_Texture *>(scoreVal, Util::getTexture(r, scoreVal, {0, 0, 0}, scoreValRect, false)));

        loaded = true;
    }
    SDL_RenderCopyF(r, stepTexture, nullptr, &stepRect);
    SDL_RenderCopyF(r, stepValTexture, nullptr, &stepValRect);

    SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &divider);

    SDL_RenderCopyF(r, agentModeTexture, nullptr, &agentModeRect);

    SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &dividerAg);

    SDL_RenderCopyF(r, gameModeTexture, nullptr, &envModeRect);

    SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &dividerSc);

    SDL_RenderCopyF(r, scoreValTexture, nullptr, &scoreValRect);

    // free textures when done
    SDL_DestroyTexture(stepTexture);
    SDL_DestroyTexture(stepValTexture);
    SDL_DestroyTexture(agentModeTexture);
    SDL_DestroyTexture(gameModeTexture);
    SDL_DestroyTexture(scoreValTexture);
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
        case SDL_KEYDOWN:
            if (events.key.keysym.sym == SDLK_ESCAPE)
            {
                PauseScreen::ismounted = true;
            }
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

    // pause screen
    PauseScreen pScreen = PauseScreen();
    pScreen.refresh();

    // start initial countdown
    unsigned int tm = SDL_GetTicks();
    envState = EnvState::Stall;
    timerValue = 3;
    steps = 5;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    while (!done)
    {
        // New Game || quit check
        if (HomeScreen::ismounted || HomeScreen::quit)
        {
            break;
        }

        // terminal step check
        if (steps < 1)
        {
            done = true;
            PauseScreen::terminalStep = true;
            PauseScreen::ismounted = true;
        }

        // pause screen
        pScreen.render(r);

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
            agent->acted = false;
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
                agent->updateWeights(reward, maxSteps);

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