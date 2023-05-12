# **Armed Bandit** 🐱‍👤

## **Motive**
Project is aimed at demonstrating the multi-armed bandit reinforcement learning problem. To briefly explain it, you(the agent) are to maximize your score by selecting the best action out of the available actions. However you have no prior knowledge of which action is the best (unless of course you peek through the code😼).

**Preview**
![Screenshot (218)](https://github.com/quinton11/armed-Bandit/assets/70300837/3b24d7c5-29d1-4de8-9718-a25f585c3442)

*Rules*
- There are 3 game modes.
- Game is episodic, meaning your score is accumulated only in an episode.
- An episode consists of 5 steps, or states.
- The agent has 6 possible buttons to hit.
- A button hit updates the score with the *weight* of the button and updates the *action-weights* of the agent

*Preview-Episode*
![Screenshot (219)](https://github.com/quinton11/armed-Bandit/assets/70300837/6d23c37d-4070-443c-b978-a07f763fd0c1)

*Game Modes*
- Demo: Manual mode, here user directly controls the button hits.
- Custom: User creates a model which plays an episode autonomously.
- Best: Out of all created models, the model with the highest score is selected and run on an episode.

*Autonomous Agents*
- User created models consist of a map of actions to their respective weight values. The set of actions available are: `{A,B,C,D,E,F}`, each having individual weights.
- The model, in training episodes, updates its weights by averaging the rewards it receives on every action. This is the *sample-average* action-value estimating method.
- In testing runs, the model selects actions using a *greedy* policy. It checks its action value map and selects the action with the maximum return its *learnt* on previous episodes.

**Building from source**
- Clone repo and cd into it.
- create a build directory
- g++(@v 7.5.0^) - https://sourceforge.net/projects/mingw-w64/ -(Windows)
- Cmake(@v 3.2^) - https://cmake.org/download/
- For windows x86_64 platforms, run `cmake --preset=default`
- After successfuly creating build system, cd into build directory and run `make`
- run ARMED_BANDIT.exe
