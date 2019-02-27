#pragma once

#include "ui.hpp"

class Game
{
    private:
        int field_size;
        int** field;
        UI ui;

        struct point
        {
            int y;
            int x;
        };

        void tick();
        void update();
    public:
        Game(int pField_size = 15);
        ~Game();
};