#pragma once

#include "../graphics/graphics.h"

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