#pragma once

#include "field.hpp"
#include "ui.hpp"
#include "player.hpp"

class Game
{
    private:
        UI ui;
        Field *field;
        Player *player;

        void tick();
        void update();
        void place_food();
    public:
        Game(int pField_size = 15);
        ~Game();
};