#pragma once

#include "field.hpp"
#include "ui.hpp"
#include "player.hpp"

struct GameEnded : std::exception {};

class Game
{
    private:
        UI ui;
        Field *field;
        Player *player;

        void tick();
        void update();
    public:
        Game(int pField_size = 15);
        ~Game();

        int start();
};