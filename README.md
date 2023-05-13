# **Armed Bandit** 🐱‍👤

## **Motive**
Project is aimed at demonstrating the multi-armed bandit reinforcement learning problem. To briefly explain it, you(the agent) are to maximize your score by selecting the best action out of the available actions. However you have no prior knowledge of which action is the best (unless of course you peek through the code😼).

**Preview**
![Screenshot (220)](https://github.com/quinton11/armed-Bandit/assets/70300837/05f8b224-db31-4288-adc7-c396680bec3a)

*Rules*
- There are 3 game modes.
- Game is episodic, meaning your score is accumulated only in an episode.
- An episode consists of 5 steps, or states.
- The agent has 6 possible buttons to hit.
- A button hit updates the score with the *weight* of the button and updates the *action-weights* of the agent

*Preview-Episode[Receive State]*
![Screenshot (219)](https://github.com/quinton11/armed-Bandit/assets/70300837/6d23c37d-4070-443c-b978-a07f763fd0c1)

*Game Modes*
- Demo: Manual mode, here user directly controls the button hits.
- Custom: User creates a model which plays an episode autonomously.
- Best: Out of all created models, the model with the highest score is selected and run on an episode.

*Autonomous Agents*
- User created models consist of a map of actions to their respective weight values. The set of actions available are: `{A,B,C,D,E,F}`, each having individual weights.
- The model, in training episodes, updates its weights by averaging the rewards it receives on every action. This is the *sample-average* action-value estimating method.
- In testing runs, the model selects actions using a *greedy* policy. It checks its action value map and selects the action with the maximum return its *learnt* on previous episodes.
- Model weights along with the score are stored in "playerweights.txt" in the executable directory. Format is `[model_name]  [score,...weights]`. Example: `Thors   23,0.2,0.4,3.9,1,0.5,2`

**Building from source**
- Clone repo and cd into it.
- create a build directory
- g++(@v 7.5.0^) - https://sourceforge.net/projects/mingw-w64/ -(Windows)
- Cmake(@v 3.2^) - https://cmake.org/download/
- For windows x86_64 platforms, run `cmake --preset=default`
- After successfuly creating build system, cd into build directory and run `make`
- run ARMED_BANDIT.exe
