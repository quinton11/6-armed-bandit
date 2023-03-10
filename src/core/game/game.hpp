#pragma once

#include "../graphics/graphics.hpp"

class Game
{
private:
    Game();
    ~Game();
    static Game *instance;
    static Graphics *graphics;
    bool isDone;

public:
    static Game *getInstance();
    static void release();

    void Run();
};