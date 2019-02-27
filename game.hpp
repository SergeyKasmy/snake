#pragma once

#include "ui.hpp"

class Game
{
    private:
        int field_size = 15;
        int** field;
        UI ui;

        void tick();
        void update();
    public:
        Game();
        ~Game();
};