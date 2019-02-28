#pragma once

#include "field.hpp"
#include "ui.hpp"

class Game
{
    private:
        UI ui;
        Field* field;

        void tick();
        void update();
    public:
        Game(int pField_size = 15);
        ~Game();
};